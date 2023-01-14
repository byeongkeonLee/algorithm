#include<stdio.h>
#include<vector>

typedef long long int ll;
using namespace std;

pair<ll, ll> deck[100001];
int front, rear;
ll dp[100001];
ll ANS;

int main(){
	int N, D;

	scanf("%d %d",&N, &D);

	int a;
	scanf("%d ",&a);
	dp[0] = a;
	deck[rear++] = make_pair(0, dp[0]);
	ANS = a;

	for(int i=1; i<N; i++){
		scanf("%d ", &a);
		while(deck[front].first < i-D){
			front ++;
		}

		dp[i] = a + deck[front].second;
		dp[i] = dp[i] > a ? dp[i] : a;
		if(ANS < dp[i]) ANS = dp[i];

		while(rear > front && deck[rear-1].second < dp[i]){
			rear--;
		}
		deck[rear++] = make_pair(i, dp[i]);
//		printf("[%d %d %d]\n", i, dp[i], a);
	}
	printf("%lld\n",ANS);
}
