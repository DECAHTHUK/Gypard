#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define HAVE_STRUCT_TIMESPEC
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

#include "JoyShockLibrary.h"

#include "Header.h"

int Right_Handle;
int Left_Handle;

JOY_SHOCK_STATE j1JSS, j2JSS;
IMU_STATE j1IS, j2IS;
MOTION_STATE j1MS, j2MS;

int handlesR_state_arr[5] = {0};
int handlesL_state_arr[5] = {0};

int right_joy_prev_state[17] = {0};
int right_joy_current_state[17] = {0}; // 4 + | 7 rstick | 9 r | 11 rt | 12 b | 13 a | 14 y | 15 x | 16 home

typedef struct {
	int Num;
	int Handle;
}Num_Handle;

void init_cons() {
	int a = JslConnectDevices();
	int *deviceHandleArray = (int *)malloc(a * sizeof(int));
	JslGetConnectedDeviceHandles(deviceHandleArray, a);
	Right_Handle = deviceHandleArray[0];
	j1JSS = JslGetSimpleState(deviceHandleArray[0]);
	init_threads();
}

void init_threads() {
	HANDLE stickR, test1, btns, stickL;
	stickR = CreateThread(NULL, 0, stick, (void*)&Right_Handle, 0, NULL);
    test1 = CreateThread(NULL, 0, test, NULL, 0, NULL);
	btns = CreateThread(NULL, 0, button_inputs, (void*)&Right_Handle, 0, NULL);
}

DWORD WINAPI test(LPVOID shit) {
	while (true) {
		j1JSS = JslGetSimpleState(0);
		if (j1JSS.rTrigger == 1) {
			POINT p;
			GetCursorPos(&p);
			mouse_event(MOUSEEVENTF_LEFTDOWN, p.x, p.y, 0, 0);
			while (j1JSS.rTrigger == 1) {
				j1JSS = JslGetSimpleState(0);
                Sleep(WAITING_TICK);
			}
			GetCursorPos(&p);
			mouse_event(MOUSEEVENTF_LEFTUP, p.x, p.y, 0, 0);
		}
		Sleep(WAITING_TICK);
	}
	return 0;
}

DWORD WINAPI stick(LPVOID handle) {
	if (*((int *)handle) == Right_Handle) {
		POINT pr;
		GetCursorPos(&pr);
		float StickX = pr.x;
		float StickY = pr.y;
        j1JSS = JslGetSimpleState(*((int *)handle));
		while (true) {
            j1JSS = JslGetSimpleState(*((int *)handle));
			if (j1JSS.stickRX != 0 || j1JSS.stickRY > 0.001) {
				float temp = 5;
				while (j1JSS.stickRX != 0 || j1JSS.stickRY > 0.001) {
                    j1JSS = JslGetSimpleState(*((int *)handle));
					StickX += j1JSS.stickRX * temp;
					StickY -= (j1JSS.stickRY + 0.000488) * temp;
					SetCursorPos(StickX, StickY);
					Sleep(DEFAULT_TICK);
					temp += 0.15;
				}
			} else {
				GetCursorPos(&pr);
				StickX = pr.x;
				StickY = pr.y;
			}
			Sleep(DEFAULT_TICK);
		}
	}
	return 0;
	// TODO: leftCon
}

DWORD WINAPI button_inputs(LPVOID handle) {
	if (*((int *)handle) == Right_Handle) {
		HANDLE btn11, btn21, btn31, btn41, btn51;
        HANDLE* handle_right_arr[5] = {&btn11, &btn21, &btn31, &btn41, &btn51};
		while(true) {
			get_buttons(j1JSS.buttons);
			for(int i = 0; i < 17; i++) {
				if((right_joy_current_state[i] - right_joy_prev_state[i] > 0) && i != 11) {
					for(int j = 0; j < 5; j++) {
						if(handlesR_state_arr[j] == 0) {
							handlesR_state_arr[j] = 1;
							Num_Handle now;
							now.Num = i;
							now.Handle = j;
							*handle_right_arr[j] = CreateThread(NULL, 0, handle_button_right, (void*)&now, 0, NULL);
							break;
						}
					}
				}
			}
			for(int i = 0; i < 17; i++) {
				right_joy_prev_state[i] = right_joy_current_state[i];
			}
			Sleep(WAITING_TICK);
		}
	}
	else if(*((int*)handle) == Left_Handle) {

	}
	else {
		return NULL;
	}
	return 0;
}


DWORD WINAPI handle_button_right(LPVOID num_handle) {
	Num_Handle it = *(Num_Handle*)num_handle;
	int num = it.Num;
	switch (num) {
		case 4: // +
            
			break;
		case 7: // rstick
			keybd_event(0x46, 0x46, 0, 0);
			while(right_joy_current_state[7] != 0) {
				Sleep(100);
			}
			keybd_event(0x46, 0x46, KEYEVENTF_KEYUP, 0);
			break;
		case 9: // r
			keybd_event(0x20, 0x20, 0, 0); 
			while(right_joy_current_state[9] == 1) {
				Sleep(100);
			}
			keybd_event(0x20, 0x20, KEYEVENTF_KEYUP, 0);
			break;
		case 11: // rt

			break;
		case 12: // b
			keybd_event(0x11, 0x11, 0, 0);
			while(right_joy_current_state[12] == 1) {
				Sleep(100);
			}
			keybd_event(0x11, 0x11, KEYEVENTF_KEYUP, 0);
			break;
		case 13: // a
			
			break;
		case 14: // y
			
			break;
		case 15: // x
			
			break;
		case 16: // home
			
			break;
	}
	handlesR_state_arr[it.Handle] = 0;
	return 0;
}

void get_buttons(int num) {
    int k = 1;
	int counter = 0;
    while (num > 0)
    {
        right_joy_current_state[counter] = (num % 2);
		counter++;
        k *= 10;
        num /= 2;
    }
	for(int i = counter; i < 17; i++) {
		right_joy_current_state[i] = 0;
	}
}

//int check_run_btn(int btnId, int handle) {
//	if(handle == Right_Handle) {
//		switch(btnId) { // 16 + | 128 rstick | 512 r | 2048 rt | 4096 b | 8192 a | 16384 y | 32768 x | 65536 home
//			case 16:
//				if(right_joy_button_state[0] == 0) {
//					right_joy_button_state[0] = 1;
//					return 0;
//				}
//				else {
//					return -1;
//				}
//				break;
//			case 128:
//				if(right_joy_button_state[1] == 0) {
//					right_joy_button_state[1] = 1;
//					return 1;
//				}
//				else {
//					return -1;
//				}
//				break;
//			case 512:
//				if(right_joy_button_state[2] == 0) {
//					right_joy_button_state[2] = 1;
//					return 2;
//				}
//				else {
//					return -1;
//				}
//				break;
//			case 2048:
//				if(right_joy_button_state[3] == 0) {
//					right_joy_button_state[3] = 1;
//					return 3;
//				}
//				else {
//					return -1;
//				}
//				break;
//			case 4096:
//				if(right_joy_button_state[4] == 0) {
//					right_joy_button_state[4] = 1;
//					return 4;
//				}
//				else {
//					return -1;
//				}
//				break;
//			case 8192:
//				if(right_joy_button_state[5] == 0) {
//					right_joy_button_state[5] = 1;
//					return 5;
//				}
//				else {
//					return -1;
//				}
//				break;
//			case 16384:
//				if(right_joy_button_state[6] == 0) {
//					right_joy_button_state[6] = 1;
//					return 6;
//				}
//				else {
//					return -1;
//				}
//				break;
//			case 32768:
//				if(right_joy_button_state[7] == 0) {
//					right_joy_button_state[7] = 1;
//					return 7;
//				}
//				else {
//					return -1;
//				}
//				break;
//			case 65536:
//				if(right_joy_button_state[8] == 0) {
//					right_joy_button_state[8] = 1;
//					return 8;
//				}
//				else {
//					return -1;
//				}
//				break;
//			default:
//				return NULL;
//		}
//	}
//}