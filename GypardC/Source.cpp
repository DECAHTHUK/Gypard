#include <stdio.h>

extern "C" __declspec(dllexport) int Lol();

int Lol() {
  return 3;
}