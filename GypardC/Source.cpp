#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define HAVE_STRUCT_TIMESPEC
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

#include "JoyShockLibrary.h"

#include "Header.h"

int RightHandle;
int LeftHandle;
JOY_SHOCK_STATE j1JSS, j2JSS;
IMU_STATE j1IS, j2IS;
MOTION_STATE j1MS, j2MS;

void init_cons() {
	int a = JslConnectDevices();
	int *deviceHandleArray = (int *)malloc(a * sizeof(int));
	JslGetConnectedDeviceHandles(deviceHandleArray, a);
	RightHandle = deviceHandleArray[0];
	j1JSS = JslGetSimpleState(deviceHandleArray[0]);
	HANDLE htread, uh;
	DWORD ThreadID, lelel;
	htread = CreateThread(NULL, 0, stick, (void*)&deviceHandleArray[0], 0, &ThreadID);
    uh = CreateThread(NULL, 0, test, NULL, 0, &lelel);
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
	POINT p;
	GetCursorPos(&p);
	float StickX = p.x;
	float StickY = p.y;
	if (*((int *)handle) == RightHandle) {
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
				GetCursorPos(&p);
				StickX = p.x;
				StickY = p.y;
			}
			Sleep(DEFAULT_TICK);
		}
	}
	return 0;
	// TODO: leftCon
}

void button_inputs(int handle) {
	if (handle == RightHandle) {
		j1JSS = JslGetSimpleState(handle);
        int btnId = JslGetButtons(handle);
	}
}

