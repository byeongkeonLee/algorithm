#include<stdio.h>
#include<vector>

using namespace std;
int N,M;
char visited[10001][10001];
vector<int> arr[10001];
int ans[10001];
int dfs(int head, int cur){
	int sum = 0;
	for(auto itr = arr[cur].begin(); itr != arr[cur].end(); itr++){
		if(!visited[head][*itr]){
			visited[head][*itr] = 1;
			sum += dfs(head, *itr);
		}
	}
	return sum+1;
}


int main(){
	scanf("%d %d",&N,&M);
	int a,b;
	for(int i=0;i<M;i++){
		scanf("%d %d",&a,&b);
		arr[b].push_back(a);
	}
	int max = -1;
	for(int i=1;i<=N;i++){
		visited[i][i] = 1;
		ans[i] = dfs(i,i);
		if(max < ans[i]) max = ans[i];
	}
	for(int i=1;i<=N;i++){
		if(ans[i] == max) printf("%d ",i);
	}
}
