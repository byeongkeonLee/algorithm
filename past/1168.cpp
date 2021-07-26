#include<stdio.h>
#define IMAX 2000000
using namespace std;

int arr[100000];
class Tree{
	int node[1<<18];

	public:
	int Init(int cur, int left, int right){
		if(left==right){
			return node[cur] = arr[left];
		}
		int mid = (left+right)/2;
		return node[cur] = Init(cur*2, left, mid) + Init(cur*2+1, mid+1, right);
	}	

	int Delete(int cur, int left, int right, int rank){
		if(left==right){
			node[cur] -= 1;
			return left;
		}
		int mid = (left+right)/2;
		int ret = 0;
		if(rank <= node[cur*2]) ret = Delete(cur*2, left, mid, rank);
		else ret = Delete(cur*2+1, mid+1, right, rank-node[cur*2]);
		node[cur] = node[cur*2] + node[cur*2+1];
		return ret;
	}
};
int main(){
	int N, K;
	scanf("%d %d",&N, &K);

	for(int i=0;i<N;i++){
		arr[i] = 1;
	}
	Tree *t = new Tree();
	t->Init(1, 0, N-1);

	int rank = K;

	printf("<");
	for(int i=0;i<N;i++){
		printf("%d",t->Delete(1, 0, N-1, rank)+1);

		if(i<N-1){
			rank = (rank+K-2)%(N-i-1)+1;
			printf(", ");
		}
	}
	printf(">");
}
