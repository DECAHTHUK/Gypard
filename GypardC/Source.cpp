#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "JoyShockLibrary.h"
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

extern "C" __declspec(dllexport) void InitCons();

void InitCons() { 
	int a = JslConnectDevices();
    int* deviceHandleArray = (int*)malloc(a * sizeof(int));
    JslGetConnectedDeviceHandles(deviceHandleArray, a);
    
}