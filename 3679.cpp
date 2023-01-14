#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

class Point{
	public:
	int x,y;
	int idx;
	Point(int x_, int y_, int idx_): x(x_), y(y_), idx(idx_){};
};


vector<Point> ptrs;

int CCW(Point& a, Point& b, Point& c){
	int x1 = b.x-a.x, y1 = b.y-a.y;
	int x2 = c.x-b.x, y2 = c.y-b.y;
	int val = x1*y2 - x2*y1;
	if(val>0) return 1;
	else if(val==0) return 0;
	else return -1;
}
int dist(Point &a, Point &b){
	return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
}
bool cmpCCW(Point& a, Point& b){
	int ret = CCW(ptrs[0], a, b);
	if(ret!=0){
		return ret>0;
	}else{
		return dist(ptrs[0], a) < dist(ptrs[0], b);
	}
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		ptrs.clear();
		int N;
		scanf("%d",&N);
		int a,b;
		int mina=10001, minb=10001, idx;
		for(int i=0; i<N; i++){
			scanf("%d %d ",&a,&b);
			ptrs.push_back(Point(a,b,i));
			if(minb > b || minb == b && mina > a){
				minb = b;
				mina = a;
				idx = i;
			}
		}
		ptrs[idx] = ptrs[0];
		ptrs[0] = Point(mina, minb,idx);

		sort(ptrs.begin()+1, ptrs.end(), cmpCCW);
		vector<Point> backstack;
		int top = ptrs.size()-1;
		bool flag = false;
		while(CCW(ptrs[0], ptrs[top], ptrs[top-1])==0){
			flag = true;
			backstack.push_back(ptrs.back());
			ptrs.pop_back();
			top = ptrs.size()-1;
		}
		if(flag){
			backstack.push_back(ptrs.back());
			ptrs.pop_back();
		}

		for(auto itr = ptrs.begin(); itr != ptrs.end(); itr++){
			printf("%d ",itr->idx);
		}
		for(auto itr = backstack.begin(); itr != backstack.end(); itr++){
			printf("%d ",itr->idx);
		}
		printf("\n");
	}
}
