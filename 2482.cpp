#include<stdio.h>
#define MOD 1000000003
int N;
int K;

int dp[1000][1000];
int main(){
        scanf("%d %d",&N, &K);
        for(int i=0; i<N; i++){
                dp[i][0] = 1;
        }

        for(int i=1; i<K; i++){
                for(int j=N-2*i-1; j>=1; j--){
                        dp[j][i] = (dp[j+1][i] + dp[j+2][i-1])%MOD;
                }
        }

        int ANS = dp[1][K-1];
        for(int i=1; i<N; i++){
                ANS = (ANS+dp[i][K-1])%MOD;
        }
        printf("%d\n",ANS);
}

