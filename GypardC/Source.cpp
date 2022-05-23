#include "Header.h"

int Right_Handle;
int Left_Handle;

JOY_SHOCK_STATE j1JSS, j2JSS;
IMU_STATE j1IS, j2IS;

int threads_state[10] = {0};
bool running = false;
int btn_prev_state[18] = {0};
int btn_current_state[18] = {0}; // 4 + | 7 rstick | 9 r | 11 rt | 12 b | 13 a | 14 y | 15 x | 16 home

unsigned char bindings[18] = {0x31, 0x33, 0x32, 0x34, 0x51, 0x43, 0x10, 0x46, 0, 0x47, 0, 0, 0x11, 0x20, 0x52, 0x45, VK_ESCAPE, 0x09};

HANDLE btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btn10;
HANDLE* handle_right_arr[10] = {&btn1, &btn2, &btn3, &btn4, &btn5, &btn6, &btn7, &btn8, &btn9, &btn10};
HANDLE stickR, stickL, triggerR, triggerL, btns, chckState;

void init_cons() {
	int a = JslConnectDevices();
	a = JslConnectDevices();
	while(a != 2) {
		a = JslConnectDevices();
		Sleep(SLEEPING_TICK);
	}
	int *deviceHandleArray = (int *)malloc(a * sizeof(int));
	JslGetConnectedDeviceHandles(deviceHandleArray, a);
	j1JSS = JslGetSimpleState(deviceHandleArray[0]);
	while ((j1JSS.stickLX != -1 && j1JSS.stickLY != -1) || (j1JSS.stickRX != -1 && j1JSS.stickRY != 1)) {
		j1JSS = JslGetSimpleState(deviceHandleArray[0]);
		if(j1JSS.stickLX == -1 && j1JSS.stickLY == -1) {
			Right_Handle = deviceHandleArray[0];
			Left_Handle = deviceHandleArray[1];
			break;
		}
		else if(j1JSS.stickRX == -1 && j1JSS.stickRY == -1) {
			Left_Handle = deviceHandleArray[0];
			Right_Handle = deviceHandleArray[1];
			break;
		}
		Sleep(SLEEPING_TICK);
	}
	j1JSS = JslGetSimpleState(Left_Handle);
	j2JSS = JslGetSimpleState(Right_Handle);
	running = true;
	init_threads();
}

void init_threads() {
	stickR = CreateThread(NULL, 0, stick, (void*)&Right_Handle, 0, NULL);
    stickL = CreateThread(NULL, 0, stick, (void*)&Left_Handle, 0, NULL);
    triggerR = CreateThread(NULL, 0, triggers, (void*)&Right_Handle, 0, NULL);
    triggerL = CreateThread(NULL, 0, triggers, (void*)&Left_Handle, 0, NULL);
	btns = CreateThread(NULL, 0, button_inputs, NULL, 0, NULL);
    //chckState = CreateThread(NULL, 0, check_state, NULL, 0, NULL);
}

DWORD WINAPI triggers(LPVOID handle) {
	if (*(int *)handle == Right_Handle) {
		POINT p;
		while (running) {
			if (j2JSS.rTrigger == 1) {
				GetCursorPos(&p);
				mouse_event(MOUSEEVENTF_LEFTDOWN, p.x, p.y, 0, 0);
				while (j2JSS.rTrigger == 1) {
					Sleep(DEFAULT_TICK);
				}
				GetCursorPos(&p);
				mouse_event(MOUSEEVENTF_LEFTUP, p.x, p.y, 0, 0);
			}
			Sleep(DEFAULT_TICK);
		}
	}
	else {
		j2IS = JslGetIMUState(Right_Handle);
        while (running) {
			while(j1JSS.lTrigger == 1) {
				j2IS = JslGetIMUState(Right_Handle);
				mouse_event(MOUSEEVENTF_MOVE, round(j2IS.gyroY / 8), round(j2IS.gyroX / 8), 0, 0);
				Sleep(DEFAULT_TICK);
			}
			Sleep(WAITING_TICK);
		}
	}
	return 0;
}

DWORD WINAPI stick(LPVOID handle) {
	if (*((int *)handle) == Right_Handle) {
        j2JSS = JslGetSimpleState(Right_Handle);
		while (running) {
            j2JSS = JslGetSimpleState(Right_Handle);
			if (j2JSS.stickRX > 0.001 || j2JSS.stickRX < -0.001 || j2JSS.stickRY > 0.001 || j2JSS.stickRY < -0.001) {
				float temp = 10;
				while (j2JSS.stickRX > 0.001 || j2JSS.stickRX < -0.001 || j2JSS.stickRY > 0.001 || j2JSS.stickRY < -0.001) {
                    j2JSS = JslGetSimpleState(Right_Handle);
					mouse_event(MOUSEEVENTF_MOVE, round(j2JSS.stickRX * temp), round(-j2JSS.stickRY * temp), 0, 0);
					Sleep(DEFAULT_TICK);
					temp += 0.15;
				}
			}
			Sleep(DEFAULT_TICK);
		}
	}	
	else {
		j1JSS = JslGetSimpleState(Left_Handle);
		int xState = 0;
		int yState = 0;
		while(running) {
			j1JSS = JslGetSimpleState(Left_Handle);
			while(j1JSS.stickLX > 0.08 || j1JSS.stickLX < -0.08 || j1JSS.stickLY > 0.08 || j1JSS.stickLY < -0.08) {
				j1JSS = JslGetSimpleState(Left_Handle);
				if(j1JSS.stickLX >= 0.08 && (xState == 0 || xState == -1)) {
					if(xState == -1) {
						keybd_event(0x41, 0x41, KEYEVENTF_KEYUP, 0);
					}
					xState = 1;
					keybd_event(0x44, 0x44, 0, 0);
				}
				else if(j1JSS.stickLX <= -0.08 && (xState == 0 || xState == 1)) {
					if(xState == 1) {
						keybd_event(0x44, 0x44, KEYEVENTF_KEYUP, 0);
					}
					xState = -1;
					keybd_event(0x41, 0x41, 0, 0);
				}
				else if((j1JSS.stickLX > -0.08 && j1JSS.stickLX < 0.08) && (xState == 1 || xState == -1)) {
					if(xState == -1) {
						keybd_event(0x41, 0x41, KEYEVENTF_KEYUP, 0);
					}
					else if(xState == 1) {
						keybd_event(0x44, 0x44, KEYEVENTF_KEYUP, 0);
					}
					xState = 0;
				}

				if(j1JSS.stickLY >= 0.08 && (yState == 0 || yState == -1)) {
					if(yState == -1) {
						keybd_event(0x53, 0x53, KEYEVENTF_KEYUP, 0);
					}
					yState = 1;
					keybd_event(0x57, 0x57, 0, 0);
				}
				else if(j1JSS.stickLY <= -0.08 && (yState == 0 || yState == 1)) {
					if(yState == 1) {
						keybd_event(0x57, 0x57, KEYEVENTF_KEYUP, 0);
					}
					yState = -1;
					keybd_event(0x53, 0x53, 0, 0);
				}
				else if((j1JSS.stickLY > -0.08 && j1JSS.stickLY < 0.08) && (yState == 1 || yState == -1)) {
					if(yState == -1) {
						keybd_event(0x53, 0x53, KEYEVENTF_KEYUP, 0);
					}
					else if(yState == 1) {
						keybd_event(0x57, 0x57, KEYEVENTF_KEYUP, 0);
					}
					yState = 0;
				}
				Sleep(DEFAULT_TICK);
			}
			Sleep(WAITING_TICK);
		}
	}
	return 0;
	// TODO: leftCon
}

DWORD WINAPI button_inputs(LPVOID nthn) {
	while(running) {
		get_buttons(j1JSS.buttons, j2JSS.buttons);
		for(int i = 0; i < 18; i++) {
			if((btn_current_state[i] - btn_prev_state[i] > 0) && i != 11 && i != 10) {
				for(int j = 0; j < 10; j++) {
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
	if (num != 8){
		keybd_event(bindings[num], bindings[num], 0, 0);
		while(btn_current_state[num] != 0 && running) {
			Sleep(100);
		}
		keybd_event(bindings[num], bindings[num], KEYEVENTF_KEYUP, 0);
	}
	else {
		POINT p;
		GetCursorPos(&p);
		mouse_event(MOUSEEVENTF_RIGHTDOWN, p.x, p.y, 0, 0);
		while(btn_current_state[8] == 1 && running) {
			Sleep(100);
		}
		GetCursorPos(&p);
		mouse_event(MOUSEEVENTF_RIGHTUP, p.x, p.y, 0, 0);
	}
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
		b[counter] = (num2 % 2);
		counter++;
        k *= 10;
        num2 /= 2;
	}
	for(int i = 0; i < 18; i++) {
		if(b[i] == 1) {
            a[i] = 1;
		}
        btn_current_state[i] = a[i];
	}
}

DWORD WINAPI check_state(LPVOID nthn) {
	while(true) {
		if(JslConnectDevices() < 2) {
			for(int i = 0; i < 10; i++){
				if(threads_state[i] == 1) {
					TerminateThread(handle_right_arr[i], NULL);
					threads_state[i] = 0;
				}
			}
			TerminateThread(stickR, NULL);
			TerminateThread(stickL, NULL);
			TerminateThread(triggerR, NULL);
			TerminateThread(triggerL, NULL);
			TerminateThread(btns, NULL);
			init_cons();
		}
		Sleep(SLEEPING_TICK);
	}
}

void terminate_program() {
	threads_state[10] = {0};
	btn_prev_state[18] = {0};
	btn_current_state[18] = {0};
	Right_Handle = -1;
	Left_Handle = -1;
	running = false;
}