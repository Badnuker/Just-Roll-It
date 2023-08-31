#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include"windows.h"
#define white 0
#define green 2
using namespace std;

string input_name, final_name, empty_string;

int maxLen;

vector<string> input_names;

void Color(int color) {
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

pair<short, short> GetCursorPosition() {
	CONSOLE_SCREEN_BUFFER_INFO cursor_info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	return {cursor_info.dwCursorPosition.X, cursor_info.dwCursorPosition.Y};
}

void SetCursorPosition(short x, short y) {
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void LoadingScreen() {
	SetConsoleTitleA("Loading...");
	Color(white);
	SetConsoleTitleA("Just-Row-it! By Badnuker");
}

void Input() {
	cout << "Enter names separated by spaces or line breaks, ending with \"end\" :\n";
	while (cin >> input_name) {
		maxLen = max(maxLen, (int)input_name.size());
		if (input_name == "end") {
			break;
		}
		input_names.push_back(input_name);
	}
	for (int i = 0; i <= maxLen; i++) {
		empty_string = ' ' + empty_string;
	}
}

void Extract() {
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	cout << "\nExtracting...\n\n\n";
	Color(green);
	for (int i = 1; i <= 50; i++) {
		cout << input_names[rnd() % input_names.size()] << '\r';
		Sleep(150);
		cout << empty_string << '\r';
	}
	Color(white);
	final_name = input_names[rnd() % input_names.size()];
}

void Output() {
	SetCursorPosition(GetCursorPosition().first, GetCursorPosition().second - 1);
	cout << "----------\n";
	Color(green);
	cout << final_name << '\n';
	Color(white);
	cout << "----------\n";
}

int main() {
	LoadingScreen();
	Input();
	HideCursor();
	Extract();
	Output();
	system("pause");
	return 0;
}

