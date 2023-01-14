#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

class Point{
	public:
	int x,y;
	Point(int x_, int y_): x(x_),y(y_){};
	Point operator-(Point& b){
		return Point(x - b.x, y - b.y);
	}
	bool operator>(Point & b){
		return x > b.x || x == b.x && y > b.y;
	}

	bool operator<=(Point & b){
		return x < b.x || x == b.x && y <= b.y;
	}
};

int CCW(Point a, Point b, Point c){
	int x1 = b.x - a.x, y1 = b.y - a.y;
	int x2 = c.x - b.x, y2 = c.y - b.y;
	int val = x1*y2 - x2*y1;
	
	if(val > 0) return 1;
	else if (val==0) return 0;
	else return -1;
}
Point zero_point(0,0);
bool cmpCCW(Point &a, Point &b){
	int ret = CCW(zero_point, a, b);
	if(ret == 0){
		return a.y == b.y ? a.x < b.x : a.y < b.y;
	}else{
		return ret > 0;
	}
}

vector<Point> convexHull(int N){
	vector<Point> ptrs;
	int a,b, mina=10001, minb=10001, idx;
	for(int i=0; i<N; i++){
		scanf("%d %d",&a,&b);
		ptrs.push_back(Point(a,b));
		if(b < minb || b == minb && a< mina){
			idx = i;
			minb = b;
			mina = a;
		}
	}
	ptrs[idx] = ptrs[0];
	ptrs[0] = Point(mina, minb);
	zero_point = ptrs[0];
	sort(ptrs.begin()+1, ptrs.end(), cmpCCW);
	vector<Point> stack;
	stack.push_back(ptrs[0]);
	for(int i=1; i<ptrs.size(); i++){
		while(stack.size()>1 && CCW(stack[stack.size()-2], stack[stack.size()-1], ptrs[i])<=0)
		   	stack.pop_back();
		stack.push_back(ptrs[i]);
	}
	return stack;
}
bool determine_cross(Point& a, Point& b, Point& c, Point& d){
	int abc = CCW(a,b,c);
	int abd = CCW(a,b,d);
	int cda = CCW(c,d,a);
	int cdb = CCW(c,d,b);

	if(abc * abd == 0 && cda * cdb == 0){
		if(a > b) swap(a,b);
		if(c > d) swap(c,d);

		return a <= d && c <= b;
	}else{
		return abc * abd <= 0 && cda * cdb <= 0;
	}
}
int main(){
	int testcase;
	scanf("%d",&testcase);
	Point zero(0,0);
	while(testcase--){
		int n,m;
		scanf("%d %d",&n,&m);
		
		vector<Point> black = convexHull(n);
		vector<Point> white = convexHull(m);
		black.push_back(black[0]);
		white.push_back(white[0]);
		bool answer = true;
		
		for(auto b = black.begin(); b != black.end()-1 && answer; b++){
			for(auto w = white.begin(); w != white.end()-1 && answer; w++){
				bool ret = determine_cross(*b, *(b+1), *w, *(w+1));
				printf("[b(%d %d) (%d %d),  w(%d %d) (%d %d)] %d\n",b->x, b->y, (b+1)->x, (b+1)->y, w->x, w->y, (w+1)->x, (w+1)->y, ret);
				if(ret){
					answer = false;
				}
			}
		}

		if(answer){
			auto outer = (black[0].y == white[0].y? black[0].x < white[0].x : black[0].y < white[0].y) ? black : white;
			auto inner = (black[0].y == white[0].y? black[0].x < white[0].x : black[0].y < white[0].y) ? white : black;
			if(outer.size()>=4)
				answer = false;
			for(auto o = outer.begin(); o != outer.end()-1 && !answer; o++){
				for(auto i = inner.begin(); i != inner.end()-1 && !answer; i++){
					int ret = CCW(*o, *(o+1), *i);
//				printf("[o(%d %d) (%d %d),  i(%d %d)] %d\n",o->x, o->y, (o+1)->x, (o+1)->y, i->x, i->y, ret);
					if(ret<0){
						answer = true;
					}
				}
			}
		}
		

		printf("%s\n",answer? "YES": "NO");
	}
}



