#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

class ptr{
	public:
	int idx;
	int s;
	int d;
	ptr(int idx_, int s_, int d_): idx(idx_), s(s_),d(d_){};
};
bool cmp(const ptr* a, const ptr* b){
	return a->s < b->s;
}
vector<ptr*> arr;

int main(){
	int N;
	scanf("%d", &N);

	int a,b;
	int d;
	for(int i=0; i<N; i++){
		scanf("%d %d",&a,&b);
		arr.push_back(new ptr(i, a, b));
	}
	sort(arr.begin(), arr.end(), cmp);
	for(int i=0; i<arr.size(); i++){
		printf("[%d %d]",arr[i]->s, arr[i]->d);
	}
	scanf("%d",&d);

}

