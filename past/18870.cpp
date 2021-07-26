#include<stdio.h>
#include<algorithm>

using namespace std;
int N;
struct Entry{
	int num;
	int idx;
};
struct Entry entry[1000000];
int ans[1000000];
bool compare(struct Entry a, struct Entry b){
	return a.num < b.num;
}
int main(){
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		scanf("%d",&entry[i].num);
		entry[i].idx = i;
	}
	sort(entry, entry+N, compare);
	int pos = -1, prev=-2147483648;
	for(int i=0;i<N;i++){
		if(prev != entry[i].num){
			pos += 1;
			prev = entry[i].num;	
		}
		ans[entry[i].idx] = pos;
	}
	for(int i=0;i<N;i++)
		printf("%d ",ans[i]);
}
