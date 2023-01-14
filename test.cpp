#include<stdio.h>
#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;

long N, L;


class Polong{
	public:
		long x;
		long y;
		Polong(const Polong& a){
			x = a.x;
			y = a.y;
		}
		Polong(long x_, long y_): x(x_), y(y_){};
};

long CCW(Polong& a, Polong& b, Polong& c){
	long x1 = b.x - a.x, x2 = c.x - b.x;
	long y1 = b.y - a.y, y2 = c.y - b.y;
	long val = 1LL*(y2*x1) - 1LL*(x2*y1);
	if(val>0) return 1;
	else if (val==0) return 0;
	else return -1;
}
double length(long a, long b){
	return  sqrt(1.0f*a*a+b*b);
}
double length(Polong& a, Polong& b){
	long x = b.x-a.x, y= b.y-a.y;
	return length(x,y);
}
double angle(Polong& a, Polong& b, Polong &c){
	long x1 = b.x - a.x, x2 = c.x - b.x;
	long y1 = b.y - a.y, y2 = c.y - b.y;
	double ret = (1.0f*x1*x2+y1*y2)/length(x1,y1)/length(x2,y2);
	return acos(ret);
}
vector<Polong> ptrs;
vector<Polong> stack;
bool cmpCCW(Polong& a, Polong& b){
	long ret = CCW(ptrs[0], a, b);
	if(ret != 0){
		return ret>0;
	}else{
		return a.y == b.y? a.x < b.x: a.y < b.y;
	}
}

int main(){
	scanf("%ld",&N);
	long a,b, mina=50001, minb=50001, idx=-1;
	for(long i=0; i<N; i++){
		scanf("%ld %ld",&a,&b);
		ptrs.push_back(Polong(a,b));
		if(b<minb || b==minb && a<mina){
			minb = b;
			mina = a;
			idx = i;
		}
	}
	ptrs[idx] = Polong(ptrs[0]);
	ptrs[0] = Polong(mina, minb);
	sort(ptrs.begin()+1, ptrs.end(), cmpCCW);

	stack.push_back(ptrs[0]);
	for(long i=1; i<ptrs.size(); i++){
		while(stack.size()>1 && CCW(stack[stack.size()-2], stack[stack.size()-1], ptrs[i])<=0) stack.pop_back();
		stack.push_back(ptrs[i]);
	}

	double ans = 0.0f;

	printf("%ld",stack.size());
}
