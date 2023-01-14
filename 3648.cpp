#include<stdio.h>
#include<vector>
using namespace std;

int n,m;

vector<int> graph[2000];

char visited[2000];
char finished[2000];
char mapping[2000];
char mappingId;

int dfsn[2000];
int dfsId=0;
vector<int> stack;
int min(int a, int b){
	return a < b? a : b;
}
int dfs(int cur){
	dfsId++;
	int ret = dfsId;
	dfsn[cur] = dfsId;
	visited[cur] = 1;
	stack.push_back(cur);
	for(auto itr = graph[cur].begin(); itr != graph[cur].end(); ++itr){
		if(!visited[*itr]){
			ret = min(ret, dfs(*itr));
		}else if(!finished[*itr]){
			ret = min(ret, dfsn[*itr]);
		}
	}
	if(ret == dfsn[cur]){
		mappingId++;
		int back;
		do{
			back = stack.back();
			finished[back] = 1;
			mapping[back] = mappingId;
			stack.pop_back();
		}while(back != cur);
	}
	return dfsn[cur] = ret;
}
int main(){

	while(1){
		if(scanf("%d %d",&n,&m)==-1){
			return 0;
		}
		stack.clear();
		dfsId = 0;
		mappingId = 0;
		for(int i=0; i<2000; i++){
			graph[i].clear();
			mapping[i] = 0;
			dfsn[i] = 0;
			visited[i] = 0;
			finished[i] = 0;
		}
		int a,b;
		graph[0].push_back(1000);
		for(int i=0; i<m; i++){
			scanf("%d %d\n",&a,&b);
			a = a < 0? -a : a+1000;
			b = b < 0? -b : b+1000;
			a--;b--;
			printf("[%d->%d %d->%d]\n", a<1000? a+1000: a-1000,b, b<1000? b+1000: b-1000,a);
			graph[a<1000? a+1000: a-1000].push_back(b);
			graph[b<1000? b+1000: b-1000].push_back(a);
		}

		for(int i=0; i<n; i++){
			if(!finished[i]){
				dfs(i);
			}
		}
		char flag = true;
		for(int i=0; i<n; i++){
			if(mapping[i] == mapping[i+1000]){
				flag = false;
				break;
			}
		}
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
}
