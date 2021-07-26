#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

class Point{
		public:
	int x;
	int y;
	Point(int x_, int y_): x(x_), y(y_){};
	bool operator<(const Point a) const{
		return a.x > this->x;
	}
};
class Rectangle{
	public:
	int x;
	int b;
	int t;
	bool start;

	Rectangle(int x_, int b_, int t_, bool start_): x(x_), b(b_), t(t_), start(start_){};
	bool operator<(const Rectangle a) const{
		return a.x > this->x;
	}
};

class Tree{
	int node[1<<18];

	public:
	Tree(){
		for(int i=0;i< (1<<18);i++){
			node[i] = 0;
		}
	}
	void Insert(int cur, int left, int right, int start, int end, int val){
		if(start > right || end < left) return;
		if(start >= left && end <= right){
			node[cur] += val;
			return;
		}

		int mid = (start+end)/2;
		Insert(cur*2, left, right, start, mid, val);
		Insert(cur*2+1, left, right, mid+1, end, val);
	}

	int Search(int cur, int start, int end, int index){
		if(start==end){
			return node[cur];
		}
		int mid = (start+end)/2;
		if(index <= mid) return node[cur]+Search(cur*2, start, mid, index);
		else return node[cur]+Search(cur*2+1, mid+1, end, index);
	}	
};




int main(){
	int Testcase;
	scanf("%d",&Testcase);
	while(Testcase--){
		int n,m;
		scanf("%d %d",&n,&m);
		
		vector<Point> pointVec;
		int x,y;

		for(int i=0; i<n; i++){
			scanf("%d %d",&x,&y);
			pointVec.push_back(Point(x,y));
		}
		
		sort(pointVec.begin(), pointVec.end());

		vector<Rectangle> rectVec;
		int l,r,b,t;
		for(int i=0; i<m; i++){
			scanf("%d %d %d %d",&l,&r,&b,&t);
			rectVec.push_back(Rectangle(l-1,b,t,true));
			rectVec.push_back(Rectangle(r+1,b,t,false));
		}
		sort(rectVec.begin(), rectVec.end());

		int pointIdx = 0, cur_x = pointVec[0].x, pointSize = pointVec.size();
		int ANS = 0;
		Tree *tree = new Tree();

		for(int rectIdx = 0, rectSize = rectVec.size(); rectIdx < rectSize; rectIdx++){
			int rect_x = rectVec[rectIdx].x;
//			printf("<%d %d %d %d>\n",rectIdx, rect_x, rectVec[rectIdx].b, rectVec[rectIdx].t);	
			for(;cur_x <= rect_x && pointIdx < pointSize; pointIdx++, cur_x = pointVec[pointIdx].x){
//				printf("(%d %d ret:%d)\n",cur_x, pointVec[pointIdx].y, tree->Search(1,0,100000, pointVec[pointIdx].y));
				ANS += tree->Search(1, 0, 100000, pointVec[pointIdx].y);
			}
			tree->Insert(1,rectVec[rectIdx].b, rectVec[rectIdx].t, 0, 100000, rectVec[rectIdx].start? 1: -1);
		}
		delete tree;
		printf("%d\n",ANS);
	}
}
