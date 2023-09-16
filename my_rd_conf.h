#ifndef _MY_RD_CONF_
#define _MY_RD_CONF_

#include<bits/stdc++.h>

#include"my_console.h"

using namespace std;

map<string, map<string, string>> rd_conf(string conf_file_path) {
	map<string, map<string, string>> conf;
	freopen(conf_file_path.c_str(), "r", stdin);
	cin.clear();
	string table_head;
	cin >> table_head;
	if (table_head[0] != '[' || table_head[table_head.size() - 1] != ']') {
		cerr << "Wrong table head format! in \"" << conf_file_path << "\"\n";
		exit(1);
	}
loop0:
	table_head = table_head.substr(1, table_head.size() - 2);
	string info;
	while (cin >> info) {
		string info_key, info_value;
		if (info[0] == '[' && info[info.size() - 1] == ']') {
			goto loop0;
		}
		int equal_pos = info.find("=");
		if (equal_pos <= 0 || equal_pos >= (int)info.size() - 1) {
			cerr << "Wrong config format! in \"" << conf_file_path << "\"\n";
			exit(1);
		}
		info_key = info.substr(0, equal_pos);
		info_value = info.substr(equal_pos + 1, info.size() - equal_pos - 1);
		conf[table_head][info_key] = info_value;
	}
	freopen("CON", "r", stdin);
	cin.clear();
	return conf;
}

void upd_conf(string conf_file_path, string table_head, string upd_key, string upd_value) {
	map<string, map<string, string>> conf = rd_conf(conf_file_path);
	conf[table_head][upd_key] = upd_value;
	freopen(conf_file_path.c_str(), "w", stdout);
	cout.clear();
	for (auto &[head, infos] : conf) {
		cout << '[' << table_head << "]\n";
		for (auto [info_key, info_value] : infos) {
			cout << info_key << '=' << info_value << '\n';
		}
	}
	freopen("CON", "w", stdout);
	cout.clear();
}

#endif
