#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "cursor.h"

void hidecursor()
{
	HANDLE hCons;
	CONSOLE_CURSOR_INFO cci;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	cci.dwSize = 1;
	cci.bVisible = 0;
	SetConsoleCursorInfo(hCons, &cci);
}
void gotoxy(int column, int row)
{
	HANDLE hCons;
	COORD crd;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	crd.X = (short)column;
	crd.Y = (short)row;
	SetConsoleCursorPosition(hCons, crd);
}