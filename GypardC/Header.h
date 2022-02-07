#pragma once

DWORD WINAPI stick(LPVOID handle);

DWORD WINAPI test(LPVOID shit);

extern "C" __declspec(dllexport) void init_cons();

void init_cons();

void install_config(); //read conf from file

void read_gyro(int handle);

void button_inputs(int handle); // 5 per joycon

void read_accelerometer(int handle);// for now idk what to do wit it

#define DEFAULT_TICK 3
#define WAITING_TICK 10