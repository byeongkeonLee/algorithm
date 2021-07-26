#include<stdio.h>
#include<algorithm>
#include<string.h>
#define IMAX 2147483647

using namespace std;
int T;
int n;

typedef struct Invec{
        int x,y,index;
}InVec;
InVec input[75000];

bool cmpY(const InVec& a, const InVec& b){
        return a.y > b.y;
}

typedef struct vec{
        int x,y;
}Vec;
bool cmp(const Vec &a, const Vec &b){
        return a.x < b.x || a.x == b.x && a.y < b.y;
}
Vec arr[75000];

void compress(){

        sort(input, input+n, cmpY);
        int rank = -1, prev = IMAX;
        for(int i=0; i<n ; i++){
                if(prev != input[i].y) rank++;
                arr[input[i].index].y = rank;
                arr[input[i].index].x = input[i].x;
                prev = input[i].y;
        }
        sort(arr, arr+n, cmp);
}

class Tree{
        public:
        int node[200000];

        void Insert(int cur, int left, int right, int index, int val){
			if(left==right){
				node[cur] += val;
				return;
			}
			
			int mid = (left+right)/2;
			if(index <= mid) Insert(cur*2, left, mid, index, val);
			else Insert(cur*2+1, mid+1, right, index, val);
			node[cur] = node[cur*2] + node[cur*2+1];
        }
        int Search(int cur, int left, int right, int start, int end){
                if(left<= start && right >= end){
                        return node[cur];
                }
                int mid = (start+end)/2;
                int sum = 0;
                if(left<=mid)
                        sum += Search(cur*2, left, right, start, mid);
                if(right>mid)
                        sum += Search(cur*2+1, left, right, mid+1, end);
                return sum;
        }
};
int main(){
        scanf("%d",&T);
        while(T--){
                scanf("%d",&n);
                Tree* t = new Tree();
                for(int i=0;i<n;i++){
                        scanf("%d %d",&input[i].x, &input[i].y);
                        input[i].index = i;
                }
                compress();

                long ans = 0;
                for(int i=0;i<n;i++){
                        int ret = t->Search(1, 0, arr[i].y, 0, n-1);
                        t->Insert(1, 0, n-1, arr[i].y, 1);
                        ans+=ret;
                }
                printf("%ld\n",ans);
                for(int i=0;i<n;i++){
                        input[i].x = 0;
                        input[i].y = 0;
                        input[i].index = 0;
                        arr[i].x = 0;
                        arr[i].y = 0;
                }
				delete t;
        }
        return 0;
}


