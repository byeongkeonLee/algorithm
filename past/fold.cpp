#include<stdio.h>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
int N;

vector<int> arr[2], ANS;

char visited[50];
int match[50];
char not_prime[2001];
char flag;

void prime(){
		int i=2;
		not_prime[1] = 1;
		not_prime[i] = 0;
		while(i<=2000){
				for(int j=i*2; j<=2000;j+=i)
						not_prime[j] = 1;
				do{
						i++;
				}while(i<=2000 && not_prime[i]);	
		}
}

int dfs(int cur){
		if(visited[cur]) return 0;
		visited[cur] = 1;
		for(int i=0;i<arr[1].size();i++){
				if(not_prime[arr[0][cur] + arr[1][i]]) continue;
				if(match[i]==-1 || dfs(match[i])){
						match[i] = cur;
						if(match[i]==-1){
								match[i]=cur;
								return 1;
						}
						return 1;
				}	
		}
		return 0;
}

int main(){
		int a;
		scanf("%d",&N);
		prime();
		int result;
		for(int i=0;i<N;i++){
				scanf("%d",&a);
				match[i] = -1;
				if(a%2==0){
						arr[flag].push_back(a);
				}else{
						if(i==0) flag = 1;
						arr[flag^1].push_back(a);
				}
		}
		if(arr[0].size() != arr[1].size()){
				printf("-1"); return 0;
		}
		for(int i=0;i<arr[1].size(); i++){
				if(not_prime[arr[0][0]+arr[1][i]]) continue;
				memset(match, -1, arr[1].size()*sizeof(int));
				match[i] = 0;
				result = 1;
				for(int j=1;j<arr[0].size() && result; j++){
						memset(visited,0,arr[0].size());
						visited[0] = 1;
						result = dfs(j);
				}

				for(int i=0;i<arr[1].size();i++){
						printf("<%d+%d>",arr[0][match[i]], arr[1][i]);
				}
				printf("\n");
				if(result) ANS.push_back(arr[1][i]);
		}
		if(ANS.empty()){
				printf("-1");
				return 0;
		}
		sort(ANS.begin(), ANS.end());
		for(auto itr = ANS.begin(); itr != ANS.end(); ++itr){
				printf("%d ",*itr);
		}
		return 0;
}
