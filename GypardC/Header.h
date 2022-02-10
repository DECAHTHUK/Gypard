#pragma once

extern "C" __declspec(dllexport) void init_cons();

void init_cons();

DWORD WINAPI stick(LPVOID handle);

DWORD WINAPI test(LPVOID shit);

DWORD WINAPI button_inputs(LPVOID handle);

DWORD WINAPI handle_button_right(LPVOID num);

void init_threads();

//int check_run_btn(int btnId, int handle);

void install_config(); //read conf from file

void get_buttons(int num);

#define DEFAULT_TICK 3
#define WAITING_TICK 10