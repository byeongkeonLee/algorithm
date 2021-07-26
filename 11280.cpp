#include<stdio.h>
#include<vector>

using namespace std;

vector<int> graph[20000];


char visited[20000];
char finished[20000];
int dfsn[20000];
vector<int> stack;

int dfsid;
int mapping[20000], mappingId;
int min(int a,int b){
	return a > b? b : a;
}
int dfs(int cur){
	stack.push_back(cur);
	visited[cur] = 1;
	dfsn[cur] = ++dfsid;
	int ret = dfsn[cur];
	for(auto itr = graph[cur].begin(); itr != graph[cur].end(); ++itr){
		if(!visited[*itr])
			ret = min(ret, dfs(*itr));
		else if(!finished[*itr])
			ret = min(ret, dfsn[*itr]);
	}
	if(ret == dfsn[cur]){
		int back;
		mappingId++;
		do{
			back = stack.back();
			stack.pop_back();
			finished[back] = 1;
			mapping[back] = mappingId;
		}while(back != cur);
	}

	return ret;
}

int main(){
	int n,m;
	scanf("%d %d",&n,&m);

	int a,b;

	for(int i=0; i<m;i++){
		scanf("%d %d",&a,&b);

		a = a<0? -a : 10000+a;
		b = b<0? -b : 10000+b;
		a--;
		b--;
		graph[(a+10000)%20000].push_back(b);
		graph[(b+10000)%20000].push_back(a);
	}

	for(int i=0; i<n;i++){
		if(!finished[i]){
			dfs(i);
		}
	}
	for(int i=0; i<n;i++){
		if(mapping[i] == mapping[10000+i]){
			printf("0\n");
			return 0;
		}
	}
	printf("1\n");
	return 0;
}
