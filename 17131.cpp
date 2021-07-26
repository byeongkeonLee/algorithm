#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#define IMAX 2147483647
#define MOD 1000000007
using namespace std;

int N;
typedef struct vec{
		int x,y;
}Vec;
Vec arr[200000];

bool cmpX(const Vec& a, const Vec& b){
		return a.x < b.x;
}
bool cmpY(const Vec& a, const Vec& b){
		return a.y > b.y;
}
void compress(){
		sort(arr, arr+N, cmpX);
		int prev = IMAX, rank=-1;
		for(int i=0;i<N;i++){
				if(prev != arr[i].x) rank++;
				prev = arr[i].x;
				arr[i].x = rank;
		}
		sort(arr, arr+N, cmpY);
}
class Tree{
		public:
				int node[800000];

				void Insert(int cur, int left, int right, int index, int val){
						if(left==right){
								node[cur] += val;
								return;
						}
						int mid = (left+right)/2;
						if(index <= mid) Insert(cur*2, left, mid, index, val);
						else Insert(cur*2+1, mid+1, right, index, val);
						node[cur] = node[cur*2]+node[cur*2+1];
				}
				long Search(int cur, int left, int right, int start, int end){
						if(left>end || right < start) return 0;
						if(left <= start && right >= end) return node[cur];
						int mid = (start+end)/2;
						long sum = 0;
						if(left<=mid) sum += Search(cur*2, left, right, start, mid);
						if(right>mid) sum += Search(cur*2+1, left, right, mid+1, end);
						return sum;
				}
};

Tree* t = new Tree();
vector<int> batch_y;

long batch_process(){
		long ret = 0;
		for(auto itr = batch_y.begin(); itr != batch_y.end(); itr++){
				ret = (ret + t->Search(1, 0, *itr-1, 0, N-1)*t->Search(1, *itr+1, N-1, 0, N-1))%MOD;
		}
		for(auto itr = batch_y.begin(); itr != batch_y.end(); itr++){
				t->Insert(1, 0, N-1, *itr, 1);
		}
		return ret;
}
int main(){
		scanf("%d",&N);
		for(int i=0;i<N;i++){
				scanf("%d %d",&arr[i].x, &arr[i].y);
		}
		compress();
		long ans=0;
		int past_y=IMAX;
		for(int i=0;i<N;i++){
				if(past_y != arr[i].y){
						if(i>0){
							ans = (ans+batch_process())%MOD;
						}
						batch_y.clear();
						past_y = arr[i].y;
				}
				batch_y.push_back(arr[i].x);
		}

		ans = (ans+batch_process())%MOD;
		printf("%ld\n",ans);
		return 0;
}

