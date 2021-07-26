#include<stdio.h>
#include<vector>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
vector<int> arr[500];
vector<int> acc;
queue<int> next_;
vector<int> ans;
int inNode[500];

int main(){
	int T;
	scanf("%d",&T);

	while(T--){
		int N, tmp;
		scanf("%d",&N);

		//clear
		memset(inNode, 0, N*sizeof(int));
		acc.clear();
		while(!next_.empty())
			next_.pop();
		ans.clear();
		for(int i=0;i<N;i++){
			arr[i].clear();
		}

		for(int i=0;i<N;i++){
			scanf("%d",&tmp);
			tmp--;
			for(auto itr = acc.begin(); itr != acc.end(); ++itr){
				arr[*itr].push_back(tmp);
			}
			acc.push_back(tmp);
		}
		int M, a,b;
		scanf("%d",&M);
		for(int i=0;i<M;i++){
			scanf("%d %d",&a,&b);
			a--;b--;
			auto itr= find(arr[a].begin(), arr[a].end(), b);
			if(itr != arr[a].end()){
				arr[a].erase(itr);
				arr[b].push_back(a);
			}else{
				auto itr= find(arr[b].begin(), arr[b].end(), a);
				arr[b].erase(itr);
				arr[a].push_back(b);
			}
		}
		for(int i=0;i<N;i++){
			for(auto itr = arr[i].begin(); itr != arr[i].end(); ++itr){
				inNode[*itr]++;
			}
		}
		for(int i=0;i<N;i++){
			if(inNode[i]==0){
				next_.push(i);
			}
		}
		char flag = false;
		while(1){
			if(ans.size() == N){
				flag = true;
				break;
			}
			if(next_.size()==0){
				printf("IMPOSSIBLE\n");
				break;
			}
			if(next_.size()>1){
				printf("?\n");
				break;
			}
			int cur = next_.front();
			ans.push_back(cur);
			next_.pop();
			for(auto itr = arr[cur].begin(); itr != arr[cur].end(); ++itr){
				inNode[*itr]--;
				if(inNode[*itr] == 0){
					next_.push(*itr);
				}
			}
		}
		if(flag){
			for(auto itr = ans.begin(); itr != ans.end(); ++itr){
				printf("%d ",*itr+1);
			}
			printf("\n");
		}
	}
}
