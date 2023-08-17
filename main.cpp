#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include"windows.h"
#define white 0
#define green 2
using namespace std;

string name, final;

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

void Input() {
	Color(white);
	cout << "Enter names separated by spaces or line breaks, ending with \"end\" :\n";
	while (cin >> name) {
		if (name == "end") {
			break;
		}
		ans.push_back(name);
	}
}

void Extract() {
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	cout << "\nExtracting...\n\n";
	Color(green);
	for (int i = 1; i <= 48; i++) {
		cout << ans[rnd() % ans.size()] << '\r';
		Sleep(100);
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
	Extract();
	Output();
	return 0;
}
