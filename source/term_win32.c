/*
	Win32 implementation for term_* functions
	Uses the win32 api (windows.h)
*/
#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#define STRICT
#include <windows.h>
#include "term.h"

void term_blink(int enable) {
	CONSOLE_CURSOR_INFO info;
	info.bVisible = enable;
	info.dwSize = enable ? 100 : 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void term_clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;
	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
}

void term_goto(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

TermSize term_size() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	TermSize t;
	t.cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	t.rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return t;
}