#include<stdio.h>
#define INF 100000000
int N;
int arr[1000][3];
int Rdp[1001][3];
int Gdp[1001][3];
int Bdp[1001][3];

int min(int a, int b){
	return a > b? b : a;
}
int main(){
	scanf("%d",&N);
	for(int i=0; i<N; i++){
		scanf("%d %d %d",&arr[i][0], &arr[i][1], &arr[i][2]);
		Rdp[i][0] = Rdp[i][1] = Rdp[i][2] = INF;
		Gdp[i][0] = Gdp[i][1] = Gdp[i][2] = INF;
		Bdp[i][0] = Bdp[i][1] = Bdp[i][2] = INF;
	}

	Rdp[0][0] = arr[0][0];
	Gdp[0][1] = arr[0][1];
	Bdp[0][2] = arr[0][2];
	int tmp;
	for(int i=1; i<N; i++){
		for(int j=0; j<3; j++){
			tmp = min(Gdp[i-1][j], Bdp[i-1][j])+arr[i][0];
			if(Rdp[i][j] > tmp) Rdp[i][j] = tmp;
		}
		for(int j=0; j<3; j++){
			tmp = min(Rdp[i-1][j], Bdp[i-1][j])+arr[i][1];
			if(Gdp[i][j] > tmp) Gdp[i][j] = tmp;
		}
		for(int j=0; j<3; j++){
			tmp = min(Rdp[i-1][j], Gdp[i-1][j])+arr[i][2];
			if(Bdp[i][j] > tmp) Bdp[i][j] = tmp;
		}
	}
	int tmpR = min(Rdp[N-1][1], Rdp[N-1][2]);	
	int tmpG = min(Gdp[N-1][0], Gdp[N-1][2]);	
	int tmpB = min(Bdp[N-1][0], Bdp[N-1][1]);	
/*
	for(int i=0; i<N; i++){
		for(int j=0; j<3; j++){
			printf("R(%d %3d)\t", j, Rdp[i][j]==INF? -1 : Rdp[i][j]);
		}
		for(int j=0; j<3; j++){
			printf("G(%d %3d)\t", j, Gdp[i][j]==INF? -1 : Gdp[i][j]);
		}
		for(int j=0; j<3; j++){
			printf("B(%d %3d)\t", j, Bdp[i][j]==INF? -1 : Bdp[i][j]);
		}
		printf("\n");
	}*/
	printf("%d\n",min(min(tmpR, tmpG), tmpB));
}
