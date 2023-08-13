#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include"windows.h"
using namespace std;

string name;

vector<string> ans;

int main() {
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	cout<<"Enter names separated by spaces or line breaks, ending with \"end\" :\n"; 
	while(cin>>name){
		if(name=="end") break;
		ans.push_back(name);
	}
	cout << '\n';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << ans[rnd() % ans.size()] << '\n';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return 0;
}
