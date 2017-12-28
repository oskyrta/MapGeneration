////////////////////////////////////////////
// Include
#include "utils.h"
#include "vec2.h"
#include <Windows.h>

////////////////////////////////////////////
// Funtions
bool IsKeyDown(int virtualKeyCode)
{
	short keyState = GetAsyncKeyState(virtualKeyCode);
	return ((keyState & 0x8000) > 0);
}

int GetRandomInt(int min, int max)
{
	return ( min + rand() % (max - min + 1) );
}

float GetRandomFloat(float min, float max)
{
	return ( min + (max - min) * (rand()%101 / 100.0) );
}