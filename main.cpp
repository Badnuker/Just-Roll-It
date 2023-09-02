#include<bits/stdc++.h>

#include"windows.h"
#include"my_console.h"

#define white 0
#define green 2

using namespace std;

int maxLen;
string input_name, final_name, empty_string, horizontal_rule;

vector<string> input_names;

void LoadingScreen() {
	SetConsoleTitleA("Loading...");
	SetConsoleColor(white);
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
	HideCursor();
	cout << "\nExtracting...\n\n\n";
	SetConsoleColor(green);
	for (int i = 1; i <= 50; i++) {
		cout << input_names[rnd() % input_names.size()] << '\r';
		Sleep(150);
		cout << empty_string << '\r';
	}
	SetConsoleColor(white);
	final_name = input_names[rnd() % input_names.size()];
	for (int i = 0; i < (int)final_name.size(); i++) {
		horizontal_rule = '-' + horizontal_rule;
	}
}

void Output() {
	SetCursorPosition(GetCursorPosition().first, GetCursorPosition().second - 1);
	cout << horizontal_rule << '\n';
	SetConsoleColor(green);
	cout << final_name << '\n';
	SetConsoleColor(white);
	cout << horizontal_rule << '\n';
}

int main() {
	LoadingScreen();
	Input();
	Extract();
	Output();
	system("pause");
	return 0;
}

