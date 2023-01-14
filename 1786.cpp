#include<stdio.h>
#include<string.h>
#include<vector>
char str[1000005];
char p[1000005];

int get_p[1000005];
using namespace std;
int main(){
	fgets(str, 1000004, stdin);
	fgets(p, 1000004, stdin);
	int str_len = strlen(str);
	if(str[str_len-1] == '\n') str_len--;

	int p_len = strlen(p);
	if(p[p_len-1] == '\n') p_len --;

	int j=0;
	for(int i=1; i<p_len; i++){
		while(p[i] != p[j] && j >0){
			j = get_p[j-1];
		}
		if(p[i] == p[j]){
			get_p[i] = ++j;
		}
	}
	j=0;
	vector<int> answer;
	for(int i=0; i<str_len; i++){
		
		while(str[i] != p[j] && j>0){
			j = get_p[j-1];
		}
		if(str[i] == p[j]){
			if(j == p_len-1){
				answer.push_back(i-p_len+1);
				j = get_p[j];
			}else{
				j++;
			}
		}
	}
	printf("%d\n",answer.size());
	for(auto itr = answer.begin(); itr != answer.end(); itr++){
		printf("%d\n",*itr+1);
	}
}
