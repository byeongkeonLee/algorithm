#include <iostream>
#include <algorithm>
#include <stack>
#include <memory.h>
#include <queue>
using namespace std;
int n;
long long k;
string s[16];
long long v[16];
long long pw10[51]; long long memo[1 << 16][101]; int sz[51]; long long dp(int bit, int num) { if(bit==(1<<n)-1){ return !num; } if(memo[bit][num]!=-1){ return memo[bit][num]; } memo[bit][num]=0; for(int i=0; i<n; i++){ if(!(bit&(1<<i))){ memo[bit][num]+=dp(bit|(1<<i), (num*pw10[sz[i]]+v[i])%k); } } return memo[bit][num]; } long long gcd(long long a, long long b) { return b==0 ? a : gcd(b, a%b); } int main() { ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); cin >> n; memset(memo, -1, sizeof(memo)); for(int i=0; i<n; i++){ cin >> s[i]; sz[i]=s[i].size(); } cin >> k; for(int i=0; i<n; i++){ for(int j=0; j<sz[i]; j++){ v[i]=(v[i]*10+s[i][j]-'0')%k; } } pw10[0]=1%k; for(int i=1; i<=50; i++){ pw10[i]=(pw10[i-1]*10)%k; } long long a=dp(0, 0), b=1; for(int i=2; i<=n; i++){ b*=i; } long long g=gcd(a, b); cout << a/g << "/" << b/g << "\n"; return 0; }

