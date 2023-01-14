#include<stdio.h>
#define IMAX ((long long int)1<<63)-1UL

typedef long long int LLI;

LLI min(LLI a, LLI b){
	return a>b? b:a;
}
class Tree{
        public:
        LLI node[400000];

        LLI Init(int cur, int* arr, int left, int right){
                if(left==right){
                        node[cur] = (LLI)arr[left] << 32 | left;
                        return node[cur];
                }
                int mid = (left+right)/2;
                node[cur] = min(Init(cur*2, arr, left, mid), Init(cur*2+1, arr, mid+1, right));
				return node[cur];
        }
        LLI Search(int cur, int left, int right, int start, int end){
                if(left<=start && right>=end){
				   	return node[cur];
				}
                int mid = (start+end)/2;
                LLI ret = IMAX;
                if(left<=mid) ret = Search(cur*2, left, right, start, mid);
                if(right>mid) ret = min(ret, Search(cur*2+1, left, right, mid+1, end));
                return ret;
        }
        Tree(){
			for(int i=0; i<400000;i++){
				node[i] = IMAX;
			}
//			printf("%lld\n",IMAX);
        }
        LLI Update(int cur, int index, long val, int left, int right){
                if(left==right){
                        node[cur] = (LLI)val << 32 | left;
                        return node[cur];
                }
                int mid = (left+right)/2;
				LLI ret = IMAX;
                if(index <= mid) Update(cur*2, index, val, left, mid);
                if(index > mid) Update(cur*2+1, index, val, mid+1, right);
				return node[cur] = min(node[cur*2], node[cur*2+1]);
        }
		void print(){
			for(int i=0; i<10; i++){
				printf("[%d %lx]",i,node[i]);
			}
			printf("\n");
		}
};

int N,M,K;
int arr[100000];
int main(){
        scanf("%d",&N);
        Tree* t = new Tree();
        for(int i=0 ; i<N ; i++){
                scanf("%d",&arr[i]);
        }
        t->Init(1, arr, 0, N-1);

        int query;
        int a, b;
		scanf("%d",&M);
        for(int i=0 ; i<M ; i++){
                scanf("%d %d %d",&query, &a,&b);
                a--;
                if(query==1){
                        t->Update(1, a, b, 0, N-1);
                }else if(query==2){
                        b--;
                        printf("%lld\n",(t->Search(1, a, b, 0, N-1)&((1UL<<31)-1))+1);
                }
//				t->print();
        }
        return 0;
}

