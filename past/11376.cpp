#include<stdio.h>
#include<vector>
#include<string.h>

using namespace std;
vector<int> arr[1001];
int N,M;

int match[1001];

char visited[1001];
int dfs(int cur){
	
	if(visited[cur]==2) return 0;
	visited[cur] ++;
	for(auto itr = arr[cur].begin(); itr != arr[cur].end(); ++itr){
		if(!match[*itr] || dfs(match[*itr])){
			match[*itr] = cur;
			return 1;
		}
	}	
	return 0;
}
int main(){
	scanf("%d %d",&N,&M);
	int a,tmp;
	for(int i=1;i<=N;i++){
		scanf("%d",&a);
		while(a--){
			scanf("%d", &tmp);
			arr[i].push_back(tmp);
		}
	}
	
	for(int i=1;i<=N;i++){
		for(int j=0;j<2;j++){
			memset(visited,0,N);
			dfs(i);
		}
	}
	int ans = 0;
	for(int i=1;i<=M;i++){
		if(match[i])
			 ans++;
	}
	printf("%d",ans);
}
