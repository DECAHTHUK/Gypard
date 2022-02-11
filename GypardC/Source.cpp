#include "Header.h"

int Right_Handle;
int Left_Handle;

JOY_SHOCK_STATE j1JSS, j2JSS;
IMU_STATE j1IS, j2IS;

int threads_state[10] = {0};

int btn_prev_state[18] = {0};
int btn_current_state[18] = {0}; // 4 + | 7 rstick | 9 r | 11 rt | 12 b | 13 a | 14 y | 15 x | 16 home

unsigned char bindings[18] = {0x31, 0x33, 0x32, 0x34, 0x51, 0x43, 0x10, 0x46, 0x02, 0x47, 0, 0, 0x11, 0x20, 0x52, 0x45, VK_ESCAPE, 0x09};


void init_cons() {
	int a = JslConnectDevices();
	int *deviceHandleArray = (int *)malloc(a * sizeof(int));
	JslGetConnectedDeviceHandles(deviceHandleArray, a);
	Right_Handle = deviceHandleArray[0];
	j1JSS = JslGetSimpleState(deviceHandleArray[0]);
	init_threads();
}

void init_threads() { 
	HANDLE stickR, stickL, triggerR, triggerL, btns;
	stickR = CreateThread(NULL, 0, stick, (void*)&Right_Handle, 0, NULL);
    stickL = CreateThread(NULL, 0, stick, (void*)&Left_Handle, 0, NULL);
    triggerR = CreateThread(NULL, 0, triggers, (void*)&Right_Handle, 0, NULL);
    triggerL = CreateThread(NULL, 0, triggers, (void*)&Left_Handle, 0, NULL);
	btns = CreateThread(NULL, 0, button_inputs, NULL, 0, NULL);
}

DWORD WINAPI triggers(LPVOID handle) {
	if (*(int *)handle == Right_Handle) {
		while (true) {
			j1JSS = JslGetSimpleState(0);
			if (j1JSS.rTrigger == 1) {
				POINT p;
				GetCursorPos(&p);
				mouse_event(MOUSEEVENTF_LEFTDOWN, p.x, p.y, 0, 0);
				while (j1JSS.rTrigger == 1) {
					j1JSS = JslGetSimpleState(0);
					Sleep(DEFAULT_TICK);
				}
				GetCursorPos(&p);
				mouse_event(MOUSEEVENTF_LEFTUP, p.x, p.y, 0, 0);
			}
			Sleep(DEFAULT_TICK);
		}
	}
	else {
		j2IS = JslGetIMUState(0);
        while (true) {
			while(btn_current_state[10] == 1) {
				j2IS = JslGetIMUState(0);
				mouse_event(MOUSEEVENTF_MOVE, round(j2IS.gyroY / 10), round(j2IS.gyroX / 10), 0, 0);
				Sleep(DEFAULT_TICK);
			}
			Sleep(WAITING_TICK);
		}
	}
	return 0;
}

DWORD WINAPI stick(LPVOID handle) {
	if (*((int *)handle) == Right_Handle) {
        j1JSS = JslGetSimpleState(*((int *)handle));
		while (true) {
            j1JSS = JslGetSimpleState(*((int *)handle));
			j2JSS = JslGetSimpleState(1);
			if (j1JSS.stickRX != 0 || j1JSS.stickRY > 0.001) {
				float temp = 10;
				while (j1JSS.stickRX != 0 || j1JSS.stickRY > 0.001) {
                    j1JSS = JslGetSimpleState(*((int *)handle));
					mouse_event(MOUSEEVENTF_MOVE, round(j1JSS.stickRX * temp), round(-j1JSS.stickRY * temp), 0, 0);
					Sleep(DEFAULT_TICK);
					temp += 0.15;
				}
			}
			Sleep(DEFAULT_TICK);
		}
	}
	else {

	}
	return 0;
	// TODO: leftCon
}

DWORD WINAPI button_inputs(LPVOID nthn) {
	HANDLE btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btn10;
    HANDLE* handle_right_arr[10] = {&btn1, &btn2, &btn3, &btn4, &btn5, &btn6, &btn7, &btn8, &btn9, &btn10};
	while(true) {
		get_buttons(j1JSS.buttons, j2JSS.buttons);
		for(int i = 0; i < 17; i++) {
			if((btn_current_state[i] - btn_prev_state[i] > 0) && i != 11 && i != 12) {
				for(int j = 0; j < 5; j++) {
					if(threads_state[j] == 0) {
						threads_state[j] = 1;
						Num_Handle now;
						now.Num = i;
						now.Handle = j;
						*handle_right_arr[j] = CreateThread(NULL, 0, handle_button, (void*)&now, 0, NULL);
						break;
					}
				}
			}
		}
		for(int i = 0; i < 18; i++) {
			btn_prev_state[i] = btn_current_state[i];
		}
		Sleep(WAITING_TICK);
	}
	return 0;
}

DWORD WINAPI handle_button(LPVOID num_handle) {
	Num_Handle it = *(Num_Handle*)num_handle;
	int num = it.Num;
	keybd_event(bindings[num], bindings[num], 0, 0);
	while(btn_current_state[num] != 0) {
		Sleep(100);
	}
	keybd_event(bindings[num], bindings[num], KEYEVENTF_KEYUP, 0);
	threads_state[it.Handle] = 0;
	return 0;
}

void get_buttons(int num1, int num2) {
    int k = 1;
	int counter = 0;
    int a[18] = {0};
    while (num1 > 0)
    {
        a[counter] = (num1 % 2);
		counter++;
        k *= 10;
        num1 /= 2;
    }
    int b[18] = {0};
	k = 1;
	counter = 0;
	while (num2 > 0) {
		b[counter] = (num1 % 2);
		counter++;
        k *= 10;
        num1 /= 2;
	}
	for(int i = 0; i < 18; i++) {
		if(b[i] == 1) {
            a[i] = 1;
		}
        btn_current_state[i] = a[i];
	}
}