#include<stdio.h>
#include<vector>
using namespace std;
typedef long long int ll;

ll dp[100001];
ll psum[100001];
pair<ll, ll> deck[100001], deck2[100001];
ll front, rear, front2, rear2;
ll N, K;
ll ANS;

int main(){
	scanf("%lld %lld",&N, &K);

	ll in;	
	for(ll i=0; i<N; i++){
		scanf("%lld",&in);

		if(i)
			psum[i] = psum[i-1] + in;
		else
			psum[i] = in;
	}	

	deck[rear++] = make_pair(-1, 0);
	deck2[rear2++] = make_pair(-1, 0);

	for(ll i=0; i<=N; i++){
		while(deck[front].first < i-K)
			front++;
		
		while(deck2[front2].first < i-K)
			front2++;
		
		dp[i] = deck[front].second + psum[i];
		ll tmp = deck2[front2].second + psum[i];

		if(dp[i] < tmp) dp[i] = tmp;

		if(ANS < dp[i]) ANS = dp[i];
		ll push_val = dp[i-1] - psum[i];
		while(rear > front && deck[rear-1].second < push_val)
			rear --;

		ll push_val2 = dp[i-2] - psum[i];
		while(rear2 > front2 && deck2[rear2-1].second < push_val2)
			rear2--;

		deck[rear++] = make_pair(i, push_val);
		deck2[rear2++] = make_pair(i, push_val2);

//		for(ll j=front; j<rear; j++) printf("%d %d, ",deck[j].first, deck[j].second);
//		printf("\n");
	}
	printf("%lld\n",ANS);
}
