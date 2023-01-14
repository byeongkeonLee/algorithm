#include<stdio.h>
#define MAX 360000
int N;
int s[MAX*2];
int p[MAX];
int pi[MAX];
int main(){
	int a;
	scanf("%d",&N);
	for(int i=0; i<N; i++){
		scanf("%d",&a);
		s[a+MAX] = s[a] = 1;
	}
	for(int i=0; i<N; i++){
		scanf("%d",&a);
		p[a] = 1;
	}

	int i=1, j=0;
	pi[0] = 0;
	for(; i<MAX; i++){
		while(p[i] != p[j] && j>0){
			j = pi[j-1];
		}
		if(p[i] == p[j])
			pi[i] = ++j;
	}

	j=0;
	for(i=0; i<MAX*2; i++){
		while(s[i] != p[j] && j>0){
			j = pi[j-1];
		}
		if(s[i] == p[j]){
			j++;
			if(j==MAX){
				printf("possible\n");
				return 0;
			}
		}
	}
	printf("impossible\n");
	return 0;
}
