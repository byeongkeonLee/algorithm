#include<stdio.h>
#define MAX 200000


class Tree{
	public:
	int last;
	int ptr[100001];
	int node[800000];
	Tree(int n){
		last = n;
		for(int i=0; i<n; i++){
			ptr[i] = n-i-1;
		}
	}
	int Init(int cur, int left, int right){
		if(left==right){
			return node[cur] = left<last ? 1 : 0;
		}
		int mid = (left+right)/2;
		return node[cur] = Init(cur*2, left, mid) + Init(cur*2+1,mid+1, right);
	}

	void Update(int cur, int idx, int val, int left, int right){
//		printf("[%d %d %d %d %d]\n",cur,idx,val,left,right);fflush(stdout);
		if(left==right){
			node[cur] = val;
			return;
		}
		int mid = (left+right)/2;
		if(idx <= mid) Update(cur*2, idx, val, left, mid);
		else Update(cur*2+1, idx, val, mid+1, right);
		node[cur] = node[cur*2] + node[cur*2+1];
	}

	int Search(int cur, int left, int right, int start, int end){
		if(left > end || right < start) return 0;
		if(left <= start && right >= end){
//		printf("[%d %d %d %d %d = %d]\n",cur,left,right,start,end, node[cur]);fflush(stdout);
			return node[cur];
		}
		int mid = (start+end)/2;
		return Search(cur*2, left, right, start, mid) + Search(cur*2+1, left, right, mid+1, end);
	}
	void Print(){
		printf("\nprint\n");
		for(int i=0; i<20; i++){
			printf("%d ",node[i]);
		}
		printf("\n");
	}
};

int main(){

	int T;
	scanf("%d", &T);

	while(T--){
		int n, m;
		scanf("%d %d",&n,&m);
		Tree t(n);
		t.Init(1, 0, MAX);
		int a;
		for(int i=0; i<m; i++){
			scanf("%d",&a);
			a--;
			printf("%d",t.Search(1, t.ptr[a]+1, MAX, 0, MAX)); 
			t.Update(1, t.ptr[a], 0, 0, MAX);
			t.Update(1, t.ptr[a] = ++t.last, 1, 0, MAX);
			if(i<m-1) printf(" ");
		}
		printf("\n");
	}
}
