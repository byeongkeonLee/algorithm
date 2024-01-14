#include<stdio.h>

const int logbound = 19;
int lca[200001][logbound];

int main(){
    int m, q;
    scanf("%d ", &m);

    for(int i=1; i<=m; i++){
        scanf("%d ", &lca[i][0]);
    }

    for(int i=1; i<logbound; i++){
        for(int j=0; j<=m; j++){
            lca[j][i] = lca[lca[j][i-1]][i-1];
        }
    }

    scanf("%d", &q);
    for(int _q=0; _q<q; _q++){
        int n,x, unit=0;
        scanf("%d %d\n", &n, &x);
        while(n > 0){
            if(n%2){
                x = lca[x][unit];
            }
            n >>= 1;
            unit ++;
        }
        printf("%d\n", x);
    }
}