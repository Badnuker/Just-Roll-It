#ifndef _MY_CONSOLE_H_
#define _MY_CONSOLE_H_

#include<bits/stdc++.h>

#include"windows.h"

void SetConsoleColor(int color) {
	switch (color) {
		case 0:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			break;
		case 2:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			break;
	}
}

void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

std::pair<short, short> GetCursorPosition() {
	CONSOLE_SCREEN_BUFFER_INFO cursor_info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	return {cursor_info.dwCursorPosition.X, cursor_info.dwCursorPosition.Y};
}

void SetCursorPosition(short x, short y) {
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#endif
