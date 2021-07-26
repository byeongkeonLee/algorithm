#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;

int N,M;
vector<int> arr[10001];
vector<int> arr_back[10001];
char visited[10001];
char element[10001][10001];
vector<int> element_vec[10001];

void vector_combine(int cur, int child){
	for(auto itr = element_vec[child].begin(); itr != element_vec[child].end(); ++itr){
		if(!element[cur][*itr]){
			element_vec[cur].push_back(*itr);
			element[cur][*itr] = 1;
		}
	}	
}
int dfs(int cur){
	int sum = 0;
	for(vector<int>::iterator itr = arr[cur].begin(); itr != arr[cur].end(); ++itr){
		if(!visited[*itr]){
			visited[*itr] = 1;
			dfs(*itr);
		}else{
			vector_combine(cur, *itr);
		}
	}
	if(!element[cur][cur]){
		element[cur][cur] = 1;
		element_vec[cur].push_back(cur);
	}
	return 0;
}

int main(){
	scanf("%d %d",&N,&M);
	int a,b;
	for(int i=0;i<M;i++){
		scanf("%d %d",&a,&b);
		arr[b].push_back(a);
	}
	
	for(int i=1;i<=N;i++){
		if(!visited[i]){
			visited[i] = 1;
			dfs(i);
		}
	}
	int size[10001], max = -1;
	for(int i=1; i<=N; i++){
		size[i] = element_vec[i].size();
		if(max < size[i]) max = size[i];
	}
	for(int i=1; i<=N; i++){
		if(max == size[i]) printf("%d ",i);
	}
/*
	for(int i=1; i<=N;i++){
		printf("%d %d : ",i,element_vec[i].size());
		for(int j=0;j<element_vec[i].size();j++){
			printf("%d ",element_vec[i][j]);
		}
		printf("\n");
	}
*/
	
}
