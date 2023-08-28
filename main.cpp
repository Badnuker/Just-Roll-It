#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include"windows.h"
#define white 0
#define green 2
using namespace std;

string name, final, emptyString;

int maxLen;

vector<string> ans;

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


void Input() {
	Color(white);
	cout << "Enter names separated by spaces or line breaks, ending with \"end\" :\n";
	while (cin >> name) {
		maxLen = max(maxLen, (int)name.size());
		if (name == "end") {
			break;
		}
		ans.push_back(name);
	}
	for (int i = 0; i <= maxLen; i++) {
		emptyString = ' ' + emptyString;
	}
}

void Extract() {
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	cout << "\nExtracting...\n\n";
	Color(green);
	for (int i = 1; i <= 50; i++) {
		cout << ans[rnd() % ans.size()] << '\r';
		Sleep(150);
		cout << emptyString << '\r';
	}
	Color(white);
	final = ans[rnd() % ans.size()];
}

void Output() {
	cout << "----------\n";
	Color(green);
	cout << final << '\n';
	Color(white);
	cout << "----------\n";
}

int main() {
	Input();
	HideCursor();
	Extract();
	Output();
	system("pause");
	return 0;
}
