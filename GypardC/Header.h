#pragma once

#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define HAVE_STRUCT_TIMESPEC
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

#include "JoyShockLibrary.h"

extern "C" __declspec(dllexport) void init_cons();

void init_cons();

DWORD WINAPI stick(LPVOID handle);

DWORD WINAPI triggers(LPVOID handle);

DWORD WINAPI button_inputs(LPVOID handle);

DWORD WINAPI handle_button(LPVOID num);

void init_threads();

void install_config(); //read conf from file

void get_buttons(int num1, int num2);

typedef struct {
	int Num;
	int Handle;
}Num_Handle;

#define DEFAULT_TICK 10
#define WAITING_TICK 50