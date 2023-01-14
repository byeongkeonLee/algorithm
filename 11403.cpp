#include<stdio.h>


int N;
int arr[100][100];

int main(){
	scanf("%d",&N);
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			scanf("%d ",&arr[i][j]);
		}
	}	
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			for(int k=0; k<N; k++){
				arr[j][k] = arr[j][k] | (arr[j][i] & arr[i][k]);
			}
		}
	}
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
}
