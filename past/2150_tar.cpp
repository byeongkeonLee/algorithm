#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;



vector<int> graph[10000];
vector<int> stack;

char visited[10000];
char finished[10000];
int dfsn[10000];

vector<int> ANS[10000];
int cnt;
int id;

int min(int a, int b){
	return a > b ? b : a;
}
int dfs(int cur){
		dfsn[cur] = id++;
		int ret = dfsn[cur];
		for(auto itr = graph[cur].begin(); itr != graph[cur].end(); itr++){
				if(visited[*itr] == 0){
						visited[*itr] = 1;
						stack.push_back(*itr);
						ret = min(ret, dfs(*itr));
				}else{
						if(!finished[*itr]){
								ret = min(ret, dfsn[*itr]);
						}
				}
		}
		if(dfsn[cur] == ret){
				int back;
				do{
						back = stack.back();
						stack.pop_back();
						finished[back] = 1;
						ANS[cnt].push_back(back);
				}while(back != cur);
				cnt++;
		}
		return dfsn[cur] = ret;
}

bool cmp(vector<int> a, vector<int> b){
	return a[0] < b[0];
}
int main(){
		int N, M;
		scanf("%d %d",&N,&M);

		int a, b;
		for(int i=0; i<M; i++){
				scanf("%d %d",&a, &b);
				a--;b--;
				graph[a].push_back(b);
		}

		for(int i=0; i<N; i++){
				if(!finished[i]){
						visited[i] = 1;
						stack.push_back(i);
						dfs(i);
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
