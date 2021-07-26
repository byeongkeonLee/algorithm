#include<stdio.h>
#include<vector>

using namespace std;

vector<int> graph[100000];
vector<int> graph_back[100000];

vector<int> stack;
char visited[100000];
char visited_back[100000];

int mapping[100000], mapping_id;
int ingress[100000];
void dfs(int cur){
	for(auto itr = graph[cur].begin(); itr != graph[cur].end(); itr++){
		if(!visited[*itr]){
			visited[*itr] = 1;
			dfs(*itr);
			stack.push_back(*itr);
		}
	}
}
void dfs_back(int cur){
	for(auto itr = graph_back[cur].begin(); itr != graph_back[cur].end(); itr++){
		if(!visited_back[*itr]){
			visited_back[*itr] = 1;
			mapping[*itr] = mapping_id;
			dfs_back(*itr);
		}
	}
}
int main(){
	int testcase;
	scanf("%d", &testcase);

	while(testcase--){
		int n, m;
		scanf("%d %d",&n,&m);

		stack.clear();
		mapping_id = -1;
		for(int i=0; i<n; i++){
			graph[i].clear();
			graph_back[i].clear();
			visited[i] = 0;
			visited_back[i] = 0;
			mapping[i] = 0;
			ingress[i] = 0;
		}
	
		int a,b;
		for(int i=0; i<m; i++){
			scanf("%d %d",&a, &b);
			graph[a].push_back(b);
			graph_back[b].push_back(a);
		}

		for(int i=0; i<n; i++){
			if(visited[i]==0){
				visited[i] = 1;
				dfs(i);
				stack.push_back(i);
			}
		}
		
		do{
			int cur = stack.back();
			stack.pop_back();
			if(!visited_back[cur]){
				mapping[cur] = ++mapping_id;
				visited_back[cur] = 1;
				dfs_back(cur);
			}
		}while(!stack.empty());

		for(int i=0; i<n; i++){
			for(auto itr = graph[i].begin(); itr != graph[i].end(); ++itr){
				if(mapping[i] != mapping[*itr]){
					ingress[mapping[*itr]] ++;
				}
			}
		}
		int ans_id = -1;
		for(int i=0; i<=mapping_id; i++){
			if(ingress[i] == 0){
				if(ans_id != -1){
					printf("Confused\n");
					goto END;
				}
				ans_id = i;
			}
		}
		for(int i=0; i<n; i++){
			if(mapping[i] == ans_id){
				printf("%d\n",i);
			}
		}
		
END:
		if(testcase>0)
			printf("\n");
	}

}
