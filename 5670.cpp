#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;


class Trie{
	public:

	Trie* t[27];
	int finish = 0;
	bool branch = false;
	Trie(){
		for(int i=0; i<27; i++){
			t[i] = nullptr;
		}
	};
	~Trie(){
		for(int i=0; i<27; i++){
			if(t[i] != nullptr){
				delete t[i];
			}
		}
//		printf("~Trie\n");
	}
	void Insert(char* s){
		char cur = s[0]-'a';
		if(s[0] == '\0')
			cur = 26;
		
		if(t[cur] == nullptr){
			t[cur] = new Trie();
		}
		
		if(cur < 26)
			t[cur]->Insert(s+1);
	}

	int Lookup(int val){
		int duplicate = 0;

		for(int i=0; i<27; i++){
			if(t[i] != nullptr){
				duplicate ++;
			}
		}

		int sum = 0;
		for(int i=0; i<27; i++){
			if(t[i] != nullptr){
				sum += t[i]->Lookup(val + (duplicate > 1 && i != 26? 1 : 0));
			}
		}
		if(duplicate == 0){
			return val;
		}
		return sum;
	}
};

int main(){
	int N;
	char s[81];
	while(scanf("%d\n",&N) != -1){
		Trie *t = new Trie();
		for(int i=0; i<N; i++){
			scanf("%s\n",s);
			t->Insert(s);
		}
		t->Insert((char*) "");
		int ret = t->Lookup(0);
		printf("%.2lf\n", (double)ret/N);
		delete t;
	}
}
