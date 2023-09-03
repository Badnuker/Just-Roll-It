#ifndef _MY_RD_CONF_
#define _MY_RD_CONF_

#include<bits/stdc++.h>

#include"my_console.h"

using namespace std;

map<string, map<string, string>> conf;

void rd_conf(string conf_file) {
	conf[conf_file].clear();
	freopen(conf_file.c_str(), "r", stdin);
	cin.clear();
	string head;
	cin >> head;
	head = head.substr(1, head.size() - 2);
	string info;
	while (cin >> info) {
		string info_key, info_value;
		int equal_pos = info.find("=");
		if (equal_pos <= 0 || equal_pos >= (int)info.size() - 1) {
			cerr << "Wrong config file format! in the file \"" << conf_file << "\"";
			exit(1);
		} else {
			info_key = info.substr(0, equal_pos);
			info_value = info.substr(equal_pos + 1, info.size() - equal_pos - 1);
			conf[conf_file][info_key] = info_value;
		}
	}
	freopen("CON", "r", stdin);
	cin.clear();
}

void upd_conf(string conf_file, string head, string upd_key, string upd_value) {
	conf[conf_file][upd_key] = upd_value;
	freopen(conf_file.c_str(), "w", stdout);
	cout.clear();
	cout << '[' << head << "]\n";
	for (auto [info_key, info_value] : conf[conf_file]) {
		cout << info_key << '=' << info_value << '\n';
	}
	freopen("CON", "w", stdout);
	cout.clear();
}

#endif
