#include<stdio.h>
#include<queue>
#include<vector>
using namespace std;

pair<int, int> v[5000000];
int front, rear;

int main(){
	int N, L;

	scanf("%d %d",&N, &L);

	int a;
	for(int i=0; i<N; i++){
		scanf("%d ",&a);
	
//		for(int j = front; j<rear; j++){
//			printf("[%d %d]",v[j].first, v[j].second);
//		}	
		while(rear > front && v[rear-1].second > a){
			rear--;
		}
		v[rear++] = make_pair(i, a);
		
		if(v[front].first <= i-L){
			front++;
		}
		printf("%d ",v[front].second);
	}
}
