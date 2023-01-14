#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;

int arr[51][3];
int N;

vector<int> graph[51];
int back[51];
char visited[51];
int dfs(int node){
	if(visited[node]) return 0;
	visited[node] = 1;

	int size = graph[node].size();
	for(int i=0; i<size; i++){
		int next = graph[node][i];
		if(!back[next] || back[next] != node && dfs(back[next])){
			back[next] = node;
			return 1;
		}
	}
//	printf("return 0\n");
	return 0;
}
int main(){
	scanf("%d",&N);

	for(int i=1; i<=N; i++)
		scanf("%d %d %d",&arr[i][0], &arr[i][1], &arr[i][2]);

	for(int i=1; i<=N; i++){
		for(int j=1; j<=N; j++){
			if(i==j) continue;
			if(arr[i][0] == arr[j][0] && arr[i][1] == arr[j][1] && arr[i][2] == arr[j][2]){
				graph[i>j? j:i].push_back(i>j? i: j);
				continue;
			}
			if(arr[i][0] >= arr[j][0] && arr[i][1] >= arr[j][1] && arr[i][2] >= arr[j][2])
				graph[i].push_back(j);	
		}
	}	
	int Ans = 0;
	for(int i=1; i<=N; i++){
		memset(visited, 0, N+1);
		dfs(i);
		memset(visited, 0, N+1);
		dfs(i);
	}
	for(int i=1; i<=N; i++){
		if(back[i]) Ans++;
	}
	printf("%d\n",N-Ans);
}
