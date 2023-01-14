#include<stdio.h>
#include<string.h>

char s[1000002];
int pi[1000002];
int main(){
	int n;
	scanf("%d\n",&n);
	for(int i=0; i<n; i++){
		scanf("%c",&s[i]);
	}

	for(int i=1, j=0; i<n; i++){
		while(s[i] != s[j] && j>0)
			j = pi[j-1];
		if(s[i] == s[j])
			pi[i] = ++j;
	}
	printf("%d\n",n-pi[n-1]);
	/*
	for(int i=0; i<n; i++){
		printf("[%d %d]\n",i,pi[i]);
	}*/
}
