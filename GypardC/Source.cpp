#define CRT_SECURE_NO_WARNINGS
#include "JoyShockLibrary.h"
#include <stdio.h>
#define HAVE_STRUCT_TIMESPEC
#include <conio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <windows.h>

int RightHandle;
int LeftHandle;
JOY_SHOCK_STATE j1JSS, j2JSS;
IMU_STATE j1IS, j2IS;
MOTION_STATE j1MS, j2MS;

extern "C" __declspec(dllexport) void Stick(int handle);
void Stick(int handle) {
	POINT p;
	GetCursorPos(&p);
	float StickX = p.x;
	float StickY = p.y;
	if (handle == LeftHandle) {
		j1JSS = JslGetSimpleState(handle);
		while (true) {
			j1JSS = JslGetSimpleState(handle);
			if (j1JSS.stickRX != 0 || j1JSS.stickRY > 0.001) {
				float temp = 5;
				while (j1JSS.stickRX != 0 || j1JSS.stickRY > 0.001) {
					j1JSS = JslGetSimpleState(handle);
					StickX += j1JSS.stickRX * temp;
					StickY -= (j1JSS.stickRY + 0.000488) * temp;
					SetCursorPos(StickX, StickY);
					Sleep(2);
					temp += 0.15;
				}
			} else {
				GetCursorPos(&p);
				StickX = p.x;
				StickY = p.y;
			}
			Sleep(2);
		}
	}
}

extern "C" __declspec(dllexport) void InitCons();

void InitCons() {
  int a = JslConnectDevices();
  int *deviceHandleArray = (int *)malloc(a * sizeof(int));
  JslGetConnectedDeviceHandles(deviceHandleArray, a);
  LeftHandle = deviceHandleArray[0];
  Stick(deviceHandleArray[0]);
}
