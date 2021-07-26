#include<stdio.h>
#include<algorithm>
using namespace std;

int N;

class Point{
	public:
	int val;
	int idx;
	int y1;
	int y2;

	bool operator<(Point a) const{
		return this->val < a.val;
	}
};
class Y{
	public:
	int val;
	int idx;

	bool operator<(Y a) const{
		return this->val < a.val;
	}
};

Point x[400002];
Y y[400002];


long long int arr[1600000];
long long int sum[1600000];
class Tree{
	public:
	Tree(){
		for(int i=0;i<N*8;i++){
			arr[i] = 0;
			sum[i] = 0;
		}
		
	}
	void update(int left, int right, int start, int end, int k, int val){
		int mid = (start+end)/2;
		int ret = 0;
		if(start >=left && end <= right){
			   	arr[k] += val;
		}else{
			if(left<=mid) update(left, right, start, mid, k*2, val);
			if(right>mid) update(left, right, mid+1, end, k*2+1, val);
		}

		if(arr[k]){
			sum[k] = y[end+1].val - y[start].val;
		}else{
			if(start==end) sum[k] = 0;
			else sum[k] = sum[k*2] + sum[k*2+1];
		}
	}
/*	int print(){
		for(int i=0;i<4*N;i++){
			printf("(%d) %d %d\n",i,arr[i],sum[i]);
		}
		printf("\n");
	}*/
};
int main(){
	long long int ANS = 0;
	scanf("%d",&N);
	for(int i=0; i<N;i++){
		int a = 2*i, b = 2*i+1;
		scanf("%d %d %d %d",&x[a].val, &x[b].val, &y[a].val, &y[b].val);
		x[a].idx = y[a].idx = a;
		x[b].idx = y[b].idx = b;
	}
	sort(y,y+2*N);

	for(int i=0;i<2*N;i++){
		int arr_idx = y[i].idx / 2;
		if(y[i].idx %2==0){
			x[arr_idx*2].y1 = i;
			x[arr_idx*2+1].y1 = i;
		}else{
			x[arr_idx*2].y2 = i;
			x[arr_idx*2+1].y2 = i;
		}
	}

	sort(x,x+2*N);
	for(int i=0;i<2*N;i++){
	}

	Tree *t = new Tree();
	for(int i=0;i<2*N;i++){
//		printf("[%d: %d %d(%d) %d(%d)]\n",i, x[i].val, x[i].y1, y[x[i].y1].val,  x[i].y2, y[x[i].y2].val); fflush(stdout);
		if(i>0){
			ANS += sum[1] * (x[i].val - x[i-1].val);
		}
		if(x[i].idx % 2 ==0){ //start
			t->update(x[i].y1, x[i].y2-1, 0, 2*N-1,1, 1);
		}else{//end
			t->update(x[i].y1, x[i].y2-1, 0, 2*N-1,1, -1);
		}
		
	}
	printf("%lld\n",ANS);
}
