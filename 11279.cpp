#include<stdio.h>

int max(int a, int b){
        return a>b;
}

class PQ{
        public:
                int node[1000000];
                int ptr = 1;
                int (*func)(int,int);

                PQ(int func_(int, int)){
                        func = func_;
                }
                void swap(int a, int b){
                        int tmp = node[a];
                        node[a] = node[b];
                        node[b] = tmp;
                }
                void Insert(int val){
                        node[ptr] = val;
                        int cur = ptr;
                        ptr++;

                        while(cur>1 && func(node[cur/2], node[cur])){
                                swap(cur/2, cur);
                                cur/=2;
                        }
                }

                int Delete(){
                        int ret = node[1];
                        int cur = 1;
                        ptr--;
                        node[cur] = node[ptr];

                        int idx = 1;
                        while(cur <= ptr){
                                if(cur*2 <= ptr && func(node[idx], node[cur*2]))idx = cur*2;
                                if(cur*2+1 <= ptr && func(node[idx], node[cur*2+1]))idx = cur*2+1;
                                if(idx == cur) break;
                                swap(cur, idx);
                                cur = idx;
                        }
                        return ret;
                }
                int top(){
                        return node[1];
                }
                bool empty(){
                        return ptr == 1;
                }
                void clear(){
                        ptr=1;
                }
};

int main(){
	int N;
	scanf("%d",&N);
	PQ* maxheap = new PQ(max);
	while(N--){
		int t;
		scanf("%d",&t);
		if(t==0){
			if(!maxheap->empty()){
				printf("%d\n",maxheap->Delete());
			}else{
				printf("0\n");
			}
		}else{
			maxheap->Insert(t);
		}
	}
}
