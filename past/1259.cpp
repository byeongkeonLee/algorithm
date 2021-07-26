#include<stdio.h>

int main(){
	char s[6];
	while(1){
		scanf("%s\n",s);
		if(s[0]=='0') break;
		int len = 0;
		while(s[len++]!=0);
		int i,j;
		for(i=0,j=len-2; i<=j; i++,j--){
			printf("[%c %c]\n",s[i],s[j]);
			if(s[i] !=s[j]) break;
		}
		if(i<=j) printf("no\n");
		else printf("yes\n");
	}
}
