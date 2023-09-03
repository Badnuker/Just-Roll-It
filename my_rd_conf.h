#ifndef _MY_RD_CONF_
#define _MY_RD_CONF_

#include<bits/stdc++.h>

#include"my_console.h"

using namespace std;

map<string, map<string, string>> conf;

void rd_conf(string conf_file_name) {
	conf.clear();
	freopen(conf_file_name.c_str(), "r", stdin);
	string head;
	cin >> head;
	head = head.substr(1, head.size() - 2);
	string info;
	while (cin >> info) {
		string info_key, info_value;
		int equal_pos = info.find("=");
		if (equal_pos <= 0 || equal_pos >= (int)info.size() - 1) {
			cerr << "Wrong config file format! in the file \"" << conf_file_name << "\"";
			exit(1);
		} else {
			info_key = info.substr(0, equal_pos);
			info_value = info.substr(equal_pos + 1, info.size() - equal_pos - 1);
			conf[head][info_key] = info_value;
		}
	}
	cin.clear();
}

#endif
