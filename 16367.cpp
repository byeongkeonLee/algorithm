#include<stdio.h>
#include<vector>
#define B 10000
#define MAXB 20000

using namespace std;

vector<int> graph[20001];

char visited[20001];
char finished[20001];

vector<int> stack;

int mapping[20001], mappingID;
int dfsID[20001], dfsn;

int min(int a, int b){return  a > b? b : a;}
int dfs(int cur){
	visited[cur] = 1;
	int ret = ++dfsn;
	dfsID[cur] = ret;
	stack.push_back(cur);
	for(auto itr = graph[cur].begin(); itr != graph[cur].end(); itr++){
		if(!visited[*itr]){
			ret = min(ret, dfs(*itr));
		}else if(!finished[*itr]){
			ret = min(ret, dfsID[*itr]);
		}
	}

	if(ret == dfsID[cur]){
		++mappingID;
		int back;
		do{
			back = stack.back();
			finished[back] = 1;
			mapping[back] = mappingID;
			stack.pop_back();
		}while(back != cur);

	}
	return ret;
}
int main(){
	int K, N;
	scanf("%d %d",&K,&N);

	int na,nb,nc;
	char ca,cb,cc;
	for(int i=0; i<N; i++){
		scanf("%d %c %d %c %d %c\n",&na,&ca,&nb,&cb,&nc,&cc);
		na--; nb--; nc--;
		na = ca=='R'? na+B : na;
		nb = cb=='R'? nb+B : nb;
		nc = cc=='R'? nc+B : nc;

		graph[(na+B)%MAXB].push_back(nb);
		graph[(na+B)%MAXB].push_back(nc);
		graph[(nb+B)%MAXB].push_back(na);
		graph[(nb+B)%MAXB].push_back(nc);
		graph[(nc+B)%MAXB].push_back(na);
		graph[(nc+B)%MAXB].push_back(nb);
	}

	for(int i=0; i<K; i++){
		if(!finished[i]){
			dfs(i);
		}
		if(!finished[i+B]){
			dfs(i+B);
		}
	}
	for(int i=0; i<K; i++){
		if(mapping[i] == mapping[i+B]){
			printf("-1");
			return 0;
		}
	}
	for(int i=0; i<K; i++){
		if(mapping[i] < mapping[i+B]){
			printf("B");
		}else
			printf("R");
	}
}
