#include<bits/stdc++.h>

#include"windows.h"
#include"my_console.h"
#include"my_rd_conf.h"

#define WHITE 0
#define GREEN 2

using namespace std;

int default_name_list_count;
string input_name, final_name, empty_string, horizontal_rule;

map<string, map<string, string>> configs;
vector<vector<string>> default_name_lists = {{}};
vector<string> input_names;

void Init() {
	configs = rd_conf("config.ini");
	string default_count = configs["default"]["default_count"];
	for (int i = 0; i < (int)default_count.size(); i++) {
		if (!isdigit(default_count[i])) {
			cerr << "Wrong config format! in the table \"default\"\n";
			exit(1);
		}
	}
	default_name_list_count = atoi(default_count.c_str());
	for (int i = 1; i <= default_name_list_count; i++) {
		vector<string> default_name_list;
		string default_name_list_file = "default/default_" + to_string(i) + ".list", name;
		freopen(default_name_list_file.c_str(), "r", stdin);
		cin.clear();
		while (cin >> name) {
			default_name_list.push_back(name);
		}
		default_name_lists.push_back(default_name_list);
	}
	freopen("CON", "r", stdin);
	cin.clear();
	SetConsoleColor(WHITE);
}

void LoadingScreen() {
	SetConsoleTitleA("Loading...");
	Init();
	SetConsoleTitleA("Just-Row-it! By Badnuker");
}

void Input() {
	int max_len = 0;
loop1:
	if (default_name_list_count == 0) {
		cout << "There is no default name list.\n";
	} else {
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
				goto loop1;
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
				goto loop1;
			}
			int default_name_list_id = atoi(input_default_name_list_id);
			if (default_name_list_id > default_name_list_count) {
				cout << "\nInvalid input.\n\n";
				delete input_default_name_list_id;
				goto loop1;
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
loop2:
	cout << "\nSave them as default name list " << default_name_list_count + 1 << "?[y/n]: ";
	string opt;
	cin >> opt;
	if (opt == "Y" || opt == "1" || opt == "true") {
		opt = "y";
	}
	if (opt == "N" || opt == "0" || opt == "false") {
		opt = "n";
	}
	if (opt != "y" && opt != "n") {
		cout << "\nInvalid input.\n";
		goto loop2;
	}
	if (opt == "y") {
		upd_conf("config.ini", "default", "default_count", to_string(++default_name_list_count));
		string new_default_file = "default/default_" + to_string(default_name_list_count) + ".list";
		freopen(new_default_file.c_str(), "w", stdout);
		cout.clear();
		for (string name : input_names) {
			cout << name << '\n';
		}
		freopen("CON", "w", stdout);
		cout.clear();
		cout << "\nDone!\n";
	}
	for (int i = 0; i <= max_len; i++) {
		empty_string = ' ' + empty_string;
	}
}

void Extract() {
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	HideCursor();
	cout << "\nExtracting...\n\n\n";
	SetConsoleColor(GREEN);
	for (int i = 1; i <= 50; i++) {
		cout << input_names[rnd() % input_names.size()] << '\r';
		Sleep(150);
		cout << empty_string << '\r';
	}
	SetConsoleColor(WHITE);
	final_name = input_names[rnd() % input_names.size()];
	for (int i = 0; i <= (int)final_name.size(); i++) {
		horizontal_rule = '-' + horizontal_rule;
	}
}

void Output() {
	SetCursorPosition(GetCursorPosition().first, GetCursorPosition().second - 1);
	cout << horizontal_rule << '\n';
	SetConsoleColor(GREEN);
	cout << final_name << '\n';
	SetConsoleColor(WHITE);
	cout << horizontal_rule << '\n';
	system("pause");
	cout.clear();
}

int main() {
	LoadingScreen();
	Input();
	Extract();
	Output();
	return 0;
}

