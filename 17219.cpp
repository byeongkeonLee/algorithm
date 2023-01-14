#include<stdio.h>
#include<map>
#include<iostream>

using namespace std;

int main(){
	int N,M;
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N >> M;
	std::map<string, string> m;

	string key, value;
	for(int i=0; i<N; i++){
		cin >> key >> value;
		m.insert(make_pair(key, value));
	}
	for(int i=0; i<M; i++){
		cin >> key;
		cout << m.find(key)->second << '\n';
	}
}
