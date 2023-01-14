#include<stdio.h>
#include<vector>
#include<math.h>
#include<algorithm>
#define DEF 100000000
using namespace std;

class Ptr{
	public:
		long x;
		long y;
		Ptr(long x_, long y_): x(x_), y(y_){};
};
bool cmp(const Ptr& a, const Ptr& b){
	if((long) b.x * a.y != (long)b.y * a.x)
		return (long)b.x * a.y < (long)b.y * a.x;
	else return a.x*a.x + a.y*a.y < b.x*b.x + b.y*b.y;
}
vector<Ptr> ptrs;
vector<long> stack;
long CCW(Ptr a, Ptr b, Ptr c){ // a->b  b->c
	long x1 = b.x - a.x, y1 = b.y - a.y;
	long x2 = c.x - b.x, y2 = c.y - b.y;

	long val = x1*y2 - x2*y1;
	if(val > 0) return 1;
	else if (val == 0) return 0;
	else return -1;
}
bool cmpY(const Ptr& a, const Ptr& b){
	return a.y < b.y || a.y == b.y && a.x< b.x;
}
int main(){
	long N;
	long a, b;
	scanf("%ld",&N);
	for(long i=0; i<N; i++){
		scanf("%ld %ld",&a,&b);
		ptrs.push_back(Ptr(a,b));
	}

	sort(ptrs.begin(), ptrs.end(), cmpY);
	a = ptrs[0].x;
	b = ptrs[0].y;
	for(auto itr = ptrs.begin(); itr != ptrs.end(); itr++){
		itr->x = itr->x - a;
		itr->y = itr->y - b;
	}

	sort(ptrs.begin(), ptrs.end(), cmp);
	ptrs.push_back(ptrs[0]);

	stack.push_back(0);
	long cur = 1;

	while(cur <= N){
		long back = stack.back();
		if(back==0){
			stack.push_back(cur);
		}else{
			a = stack[stack.size()-2];
			b = stack[stack.size()-1];
			long ret = CCW(ptrs[a], ptrs[b], ptrs[cur]);
			if(ret <= 0){
				stack.pop_back();
				continue;
			}
			stack.push_back(cur);
		}
		cur++;
	}
	printf("%ld\n",stack.size()-1);
//	for(long i=0; i<N; i++){
//		prlongf("%d %d %.16lf\n",ptrs[i].x, ptrs[i].y, ptrs[i].angle);
//	}
}
