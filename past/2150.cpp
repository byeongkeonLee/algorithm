#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
int V,E;

vector<int> foward[10000];
vector<int> backward[10000];

vector<int> stack;
char foward_v[10000];
char backward_v[10000];

vector<int> ANS[10000];

int dfs(int cur, vector<int> *arr, char *visited, int cnt){
	for(auto itr = arr[cur].begin(); itr != arr[cur].end(); itr++){
		int next = *itr;
		if(visited[next]==0){
			visited[next] = 1;
			if(cnt!=-1){
				ANS[cnt].push_back(next);
			}
			dfs(next, arr, visited, cnt);
			if(cnt==-1){
				stack.push_back(next);
			}
		}
	}
}

bool cmp(const vector<int> a, const vector<int> b){
	return a[0] < b[0];
}
int main(){
	scanf("%d %d",&V, &E);

	int a, b;
	for(int i=0;i<E;i++){
		scanf("%d %d",&a,&b);
		a--;b--;
		foward[a].push_back(b);
		backward[b].push_back(a);
	}

	for(int i=0; i<V; i++){
		if(foward_v[i]==0){
			foward_v[i] = 1;
			dfs(i, foward, foward_v, -1);
			stack.push_back(i);
		}
	}

	int cnt = 0;
	while(!stack.empty()){
		int cur = stack.back();
		stack.pop_back();
		if(backward_v[cur] == 0){
			backward_v[cur] = 1;
			ANS[cnt].push_back(cur);
			dfs(cur, backward, backward_v, cnt);
			cnt++;
		}
	}
	for(int i=0; i<cnt; i++){
		sort(ANS[i].begin(), ANS[i].end());
	}
	sort(ANS, ANS+cnt, cmp);
	printf("%d\n",cnt);
	for(int i=0; i<cnt; i++){
		for(int j=0; j<ANS[i].size(); j++){
			printf("%d ", ANS[i][j]+1);
		}
		printf("-1\n");
	}
}
