#include<stdio.h>

int main(){
	int N = 200000/3;

	for(int i=0; i<N; i++){
		printf("%d %d\n",299999, 300000-i);
		printf("%d %d\n",300001, 300000-i);
		printf("%d %d\n",300000, 299999-i);
	}

}
