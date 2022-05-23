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

extern "C" __declspec(dllexport) void terminate_program();

void terminate_program();

DWORD WINAPI stick(LPVOID handle);

DWORD WINAPI triggers(LPVOID handle);

DWORD WINAPI button_inputs(LPVOID handle);

DWORD WINAPI handle_button(LPVOID num);

DWORD WINAPI check_state(LPVOID nthn);

void init_threads();

void install_config(); //read conf from file

void get_buttons(int num1, int num2);

typedef struct {
	int Num;
	int Handle;
}Num_Handle;

#define DEFAULT_TICK 10
#define WAITING_TICK 30
#define SLEEPING_TICK 300