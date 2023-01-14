#include<stdio.h>
#include<vector>
#include<algorithm>
#define INF 2147483647
using namespace std;
class Point{
	public:
		long x;
		long y;
		Point(){};
		Point(long x_, long y_): x(x_), y(y_){};
		Point operator-(Point& b){
			return Point(x - b.x, y - b.y);
		}
		Point operator+(Point& b){
			return Point(x + b.x, y + b.y);
		}
};
long CCW(const Point &a, const Point &b, const Point &c){
	long x1 = b.x-a.x, y1 = b.y-a.y;
	long x2 = c.x-b.x, y2 = c.y-b.y;
	long val = x1*y2 - y1*x2;
	if(val>0) return 1;
	else if (val==0) return 0;
	else return -1;
}

Point ptrs[200003];
Point stack[200003];

long dist(const Point& a, const Point &b){
	return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
}
bool cmpCCW(const Point& a, const Point& b){
	long ret = CCW(ptrs[0], a, b);
	if(ret == 0){
		return a.y == b.y ? a.x < b.x : a.y < b.y;
	}else{
		return ret > 0;
	}
}
int main(){
	int testcase=1;
	scanf("%d",&testcase);
	while(testcase--){
		long N;
		scanf("%ld",&N);
		long a, b, mina=INF, minb=INF, minidx=-1;

		for(long i=0; i<N; i++){
			scanf("%ld %ld",&a, &b);
			ptrs[i] = Point(a,b);
			if(minb > b || minb == b && mina > a){
				minidx = i;
				minb = b;
				mina = a;
			}
		}


		ptrs[minidx] = Point(ptrs[0].x, ptrs[0].y);
		ptrs[0] = Point(mina, minb);

		sort(ptrs+1, ptrs+N, cmpCCW);
		int top = 0;
		stack[top++] = ptrs[0];
		for(long cur = 1; cur < N; cur++){
			while(top>1 &&CCW(stack[top-2], stack[top-1], ptrs[cur])<=0){
			   	top--;
			}
			stack[top++] = ptrs[cur];
		}
		long d = 0, val;
		int left = 0, right=1, maxl, maxr;
		for(; left<top; left++){
			while(left!=right && CCW(Point(0,0), stack[(left+1)%top] - stack[left], stack[(right+1)%top] - stack[right])>0){
				right = (right+1)%top;
			}

			val = dist(stack[left], stack[right]);
			if(d < val){
				d = val;
				maxl = left;
				maxr = right;
			}
		}
		printf("%ld %ld %ld %ld\n", stack[maxl].x, stack[maxl].y, stack[maxr].x, stack[maxr].y);
	}
}









