#include<stdio.h>
#define INTMAX 100001
#define INTMIN -1
using namespace std;

int arr[100000];

int min(int a, int b){
	return a>b? b:a;
}
int max(int a, int b){
	return a>b? a:b;
}
class Tree{
	int node[400000];

	public:
	
	int Init(int cur, int left, int right, int (*func)(int,int)){
		if(left==right){
			return node[cur] = arr[left];
		}
		int mid = (left+right)/2;
		return node[cur] = func(Init(cur*2, left, mid, func), Init(cur*2+1, mid+1, right, func));
	}

	int Search(int cur, int left, int right, int start, int end, int (*func)(int,int)){
		if(start >= left && end <= right){
			return node[cur];
		}
		int mid = (start+end)/2;
		int ret1 = -1, ret2 = -1;
		if(left<=mid) ret1 = Search(cur*2, left, right, start, mid, func);
		if(right>mid) ret2 = Search(cur*2+1, left, right, mid+1, end, func);

		if(ret1 == -1) return ret2;
		else if(ret2 == -1) return ret1;
		else return func(ret1, ret2);
	}

	void Update(int cur, int left, int right, int index, int value, int (*func)(int,int)){
		if(left==right){
			node[cur] = value;
			return;
		}
		int mid = (left+right)/2;
		if(index <= mid) Update(cur*2, left, mid, index, value, func);
		if(index > mid) Update(cur*2+1, mid+1, right, index, value, func);

		node[cur] = func(node[cur*2], node[cur*2+1]);
	}
};

int main(){
	int Testcase;
	scanf("%d",&Testcase);
	while(Testcase--){
		int N,K;
		scanf("%d %d",&N,&K);

		for(int i=0;i<N;i++){
			arr[i] = i;
		}

		Tree* t_min = new Tree();
		Tree* t_max = new Tree();

		t_min->Init(1, 0, N-1, min);
		t_max->Init(1, 0, N-1, max);

		int q,a,b;
		for(int i=0;i<K;i++){
			scanf("%d %d %d",&q,&a,&b);
			if(q==0){
				t_min->Update(1, 0, N-1, a, arr[b], min);
				t_min->Update(1, 0, N-1, b, arr[a], min);
				t_max->Update(1, 0, N-1, a, arr[b], max);
				t_max->Update(1, 0, N-1, b, arr[a], max);				
   
				int tmp = arr[a];
				arr[a] = arr[b];
				arr[b] = tmp;
			}else{
				int ret_min = t_min->Search(1, a, b, 0, N-1, min);
				int ret_max = t_max->Search(1, a, b, 0, N-1, max);

				if(ret_min==a && ret_max==b) printf("YES\n");
				else printf("NO\n");
			}
		}
	}
}  
