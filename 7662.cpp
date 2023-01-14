#include<stdio.h>

int min(int a, int b){
	return a>b;
}
int max(int a, int b){
	return a<b;
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
		void print(){
			for(int i=1; i<ptr; i++){
				printf("[%d %d]",i,node[i]);
			}
			printf("\n");
		}
};
long PQDelete(PQ *a, PQ *b){
	long ret=2147483648;
	while(!a->empty()){
		ret = a->Delete();
		if(!b->empty() && ret == b->top()){
			b->Delete();
			ret = 2147483648;
		}else{
			break;
		}
	}
	return ret;
}
int main(){
	int testcase;
	scanf("%d",&testcase);

	while(testcase--){
		PQ *maxHeap = new PQ(max);
		PQ *minHeap = new PQ(min);
		PQ *maxHeapCounter = new PQ(max);
		PQ *minHeapCounter = new PQ(min);

		int N;
		scanf("%d\n",&N);		
		char c;
		int val;
		for(int i=0; i<N; i++){
			scanf("%c %d\n",&c,&val);
			if(c=='I'){
				maxHeap->Insert(val);	
				minHeap->Insert(val);	
			}else{
				if(val == 1){
					long ret = PQDelete(maxHeap, maxHeapCounter);
					if(ret != 2147483648) minHeapCounter->Insert(ret);
				}else{
					long ret = PQDelete(minHeap, minHeapCounter);
					if(ret != 2147483648) maxHeapCounter->Insert(ret);
				}
			}
			/*	
				printf("<%d %c: %d %d>\n",i,c, maxHeap->ptr, minHeap->ptr);

				printf("max\n");
				maxHeap->print();
				printf("min\n");
				minHeap->print();

				printf("maxCounter\n");
				maxHeapCounter->print();
				printf("minCounter\n");
				minHeapCounter->print();
			 */
		}

		long a = PQDelete(maxHeap, maxHeapCounter);
		long b = PQDelete(minHeap, minHeapCounter);
		if(a == 2147483648){
			printf("EMPTY\n");
		}else{
			printf("%ld %ld\n",a,b);
		}
		delete maxHeap;
		delete minHeap;
		delete maxHeapCounter;
		delete minHeapCounter;
//		maxHeap->clear();
//		minHeap->clear();
	}

}
