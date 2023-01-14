#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int main(){
	int N = 10;

	printf("%d\n",N);
	for(int i=0; i<N; i++){
		printf("%d",rand()%10);
	}printf("\n");
	for(int i=0; i<N; i++){
		printf("%d",rand()%10);
	}
}
