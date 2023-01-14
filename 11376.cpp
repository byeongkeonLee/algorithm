#include<stdio.h>
#include<string.h>

int arr[1001][1000];
int cnt[1001];

int b_match[1001];
char visited[1001];

int n,m;
int dfs(int cur){
	int nxt;
	if(visited[cur]) return 0;
	visited[cur]=1;
	for(int i=0;i<cnt[cur];i++){
		nxt = arr[cur][i];
		//printf("[%d %d %d]\n",cur, i, nxt);
		if((!b_match[nxt] || b_match[nxt] != cur && dfs(b_match[nxt]))){
			b_match[nxt] = cur;
			return 1;
		}
	}
	return 0;
}
int main(){
	int a;
	int ans=0;
	scanf("%d %d",&n,&m);
	
	for(int i=1;i<=n;i++){
		scanf("%d",&cnt[i]);
		for(int j=0;j<cnt[i];j++){
			scanf("%d",&arr[i][j]);
		}
	}
	
	for(int i=1;i<=n;i++){
		memset(visited,0,(m+1));
		if(dfs(i)) ans++;
		memset(visited,0,(m+1));
		if(dfs(i)) ans++;
	}
	printf("%d",ans);
}
