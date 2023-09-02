#include<bits/stdc++.h>

#include"windows.h"
#include"my_console.h"

#define white 0
#define green 2

using namespace std;

int default_name_list_count;
string input_name, final_name, empty_string, horizontal_rule;

vector<vector<string>> default_name_lists = {{}};
vector<string> input_names;

void Init() {
	freopen("default/default.conf", "r", stdin);
	cin >> default_name_list_count;
	cin.clear();
	for (int i = 1; i <= default_name_list_count; i++) {
		vector<string> default_name_list;
		string default_name_list_file = "default/default_" + to_string(i) + ".list", name;
		freopen(default_name_list_file.c_str(), "r", stdin);
		while (cin >> name) {
			default_name_list.push_back(name);
		}
		default_name_lists.push_back(default_name_list);
		cin.clear();
	}
	SetConsoleColor(white);
}

void LoadingScreen() {
	SetConsoleTitleA("Loading...");
	Init();
	SetConsoleTitleA("Just-Row-it! By Badnuker");
}

void Input() {
	int max_len = 0;
	freopen("CON", "r", stdin);
	if (default_name_list_count == 0) {
		cout << "There is no default name list.\n";
	} else {
	loop:
		if (default_name_list_count == 1) {
			cout << "There is 1 default name list. Use it?[y/n]: ";
			string opt;
			cin >> opt;
			if (opt == "Y" || opt == "1" || opt == "true") {
				opt = "y";
			}
			if (opt == "N" || opt == "0" || opt == "false") {
				opt = "n";
			}
			if (opt != "y" && opt != "n") {
				cout << "\nInvalid input.\n\n";
				goto loop;
			}
			if (opt == "y") {
				for (string name : default_name_lists[1]) {
					max_len = max(max_len, (int)name.size());
					input_names.push_back(name);
				}
				for (int i = 0; i <= max_len; i++) {
					empty_string = ' ' + empty_string;
				}
				return;
			}
		} else {
			cout << "There are " << default_name_list_count << " default name lists. Use one of them?[0/1/2/...]: ";
			char* input_default_name_list_id = new char[0];
			cin >> input_default_name_list_id;
			bool islegal = 1;
			for (int i = 0; i < (int)strlen(input_default_name_list_id); i++) {
				if (!isdigit(input_default_name_list_id[i])) {
					islegal = 0;
					break;
				}
			}
			if (!islegal) {
				cout << "\nInvalid input.\n\n";
				delete input_default_name_list_id;
				goto loop;
			}
			int default_name_list_id = atoi(input_default_name_list_id);
			if (default_name_list_id > default_name_list_count) {
				cout << "\nInvalid input.\n\n";
				delete input_default_name_list_id;
				goto loop;
			}
			if (default_name_list_id) {
				for (string name : default_name_lists[default_name_list_id]) {
					max_len = max(max_len, (int)name.size());
					input_names.push_back(name);
				}
				for (int i = 0; i <= max_len; i++) {
					empty_string = ' ' + empty_string;
				}
				return;
			}
		}
	}
	cout << "\nEnter names separated by spaces or line breaks, ending with \"end\" :\n";
	while (cin >> input_name) {
		max_len = max(max_len, (int)input_name.size());
		if (input_name == "end") {
			break;
		}
		input_names.push_back(input_name);
	}
	for (int i = 0; i <= max_len; i++) {
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

