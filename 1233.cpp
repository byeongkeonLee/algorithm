#include<stdio.h>

int arr[81];

int main(){
	int s1, s2, s3;
	scanf("%d %d %d",&s1, &s2, &s3);

	for(int i=1; i<=s1; i++){
		for(int j=1; j<=s2; j++){
			for(int k=1; k<=s3; k++){
				arr[i+j+k]+=1;
			}
		}
	}
	int min =0, idx =0;

	for(int i=0; i<81; i++){
		if(min < arr[i]){
			min = arr[i];
			idx = i;
		}
	}
	printf("%d\n",idx);
}
