#include<stdio.h>


int arr[100000];
class Tree{
	long long int node[1<<20];

	public:
	void Init(int cur, int left, int right){
		if(left==right){
			node[cur] = arr[left];
			return;
		}
		int mid = (left+right)/2;
		Init(cur*2,left,mid);
	   	Init(cur*2+1,mid+1,right);
	}

	void RangeSum(int cur, int left, int right, int start, int end, int val){
		if(start >= left && end <= right){
			node[cur] += val;
			return;
		}
		int mid = (start+end)/2;
		if(left<=mid) RangeSum(cur*2, left, right, start, mid, val);
		if(right>mid) RangeSum(cur*2+1, left, right, mid+1, end, val);
	}

	long long int Search(int cur, int left, int right, int index){
		if(left == right){
			return node[cur];
		}
		int mid = (left+right)/2;
		if(index <= mid) return Search(cur*2, left, mid, index) + node[cur];
		if(index > mid) return Search(cur*2+1, mid+1, right, index) + node[cur];
	}
};


int main(){
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%d",&arr[i]);
	}
	int M;
	scanf("%d",&M);
	Tree *t = new Tree();
	t->Init(1, 0, N-1);
	for(int i=0; i<M; i++){
		int q,a,b,c;
		scanf("%d",&q);
		if(q==1){
			scanf("%d %d %d",&a,&b,&c);
			a--;b--;
			t->RangeSum(1, a, b, 0, N-1, c);
		}else{
			scanf("%d",&a);
			a--;
			printf("%lld\n",t->Search(1, 0, N-1, a));
		}
	}
	return 0;
}
