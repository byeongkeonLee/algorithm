#include<stdio.h>
#define INTMAX 1000000001

int N, M;
int arr[100000];

int min(int a, int b){
	return a > b? b : a;
}
int max(int a, int b){
	return a > b? a : b;
}
class Tree{
	int node[400000];
	public:
	Tree(int init_val){
		for(int i=0;i<N*4;i++){
			node[i] = init_val;
		}
	}
	int Init(int cur, int *arr, int left, int right, int (*func)(int,int)){
		if(left==right){
			node[cur] = arr[left];
			return node[cur];
		}
		int mid = (left+right)/2;
		return node[cur] = func(Init(cur*2,arr,left,mid,func), Init(cur*2+1,arr,mid+1,right,func));
	}
	int Search(int cur, int left, int right, int start, int end, int (*func)(int,int), int init_val){
		if(left > end || right < start) return init_val;
		if(start>=left && end <= right){
			return node[cur];
		}
		int mid = (start+end)/2;
		return func(Search(cur*2, left, right, start, mid, func, init_val), Search(cur*2+1, left, right, mid+1, end, func, init_val));
	}
	void print(){
		for(int i=0;i<40;i++){
			printf("[%d %d]",i,node[i]);
		}
		printf("\n");
	}
};

int main(){
	scanf("%d %d",&N,&M);
	for(int i=0;i<N;i++){
		scanf("%d",&arr[i]);
	}
	Tree *t_max = new Tree(0);
	Tree *t_min = new Tree(INTMAX);
	t_max->Init(1,arr,0,N-1, max);
	t_min->Init(1,arr,0,N-1, min);

	int a,b;
	t_max->print();
	t_min->print();
	for(int i=0; i<M;i++){
		scanf("%d %d",&a,&b);
		printf("%d %d\n",t_min->Search(1,a-1,b-1,0,N-1,min,INTMAX), t_max->Search(1,a-1,b-1,0,N-1,max,0));
	}
}
