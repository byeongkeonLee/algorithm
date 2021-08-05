#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	int N = 15;

	printf("%d\n",N);
	for(int i=0; i<N; i++){
		for(int j=0; j<50; j++){
			printf("%c",rand()%10+'0');
		}
		printf("\n");
	}
	printf("97");
}
