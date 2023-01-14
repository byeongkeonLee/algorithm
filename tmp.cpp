#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
class Point{
        public:
        int x;
        int y;
        Point(int x_, int y_): x(x_), y(y_){};

};

vector<Point> ptrs;
vector<Point> stack;
int CCW(const Point &a, const Point &b, const Point &c){
        long x1 = 1LL*b.x-a.x, y1 = 1LL*b.y-a.y;
        long x2 = 1LL*c.x-b.x, y2 = 1LL*c.y-b.y;
        long val = 1LL*x1*y2 - 1LL*y1*x2;
        if(val>0) return 1;
        else if (val==0) return 0;
        else return -1;
}
bool cmpY(const Point& a, const Point& b){
        return a.y < b.y || a.y == b.y && a.x < b.x;
}
bool cmpCCW(const Point& a, const Point& b){
        int ret = CCW(ptrs[0], a, b);
    if(ret == 0){
                return 1LL*a.x*a.x+1LL*a.y*a.y > 1LL*b.x*b.x+1LL*b.y*b.y;
        }else{
                return ret > 0;
        }
}

int main(){
        int testcase=1;
//      scanf("%d",&testcase);
        while(testcase--){
                int N;
                scanf("%d",&N);
                int a, b;
                ptrs.clear();
                stack.clear();
                for(int i=0; i<N; i++){
                        scanf("%d %d",&a, &b);
                        ptrs.push_back(Point(a,b));
                }
                sort(ptrs.begin(), ptrs.end(), cmpY);
                a = ptrs[0].x;
                b = ptrs[0].y;
                for(auto itr = ptrs.begin(); itr != ptrs.end(); itr++){
                        itr->x -= a;
                        itr->y -= b;
                }
                sort(ptrs.begin()+1, ptrs.end(), cmpCCW);
                stack.push_back(ptrs[0]);
                ptrs.push_back(ptrs[0]);
                int cur = 1;

                while(cur <= N){
                        if(stack.size()==1){
                                stack.push_back(ptrs[cur]);
                        }else{
                                Point &p2 = stack[stack.size()-2];
                                Point &p1 = stack[stack.size()-1];
                                int ret = CCW(p2, p1, ptrs[cur]);
                                if(ret <= 0){
                                        stack.pop_back();
                                        continue;
                                }
                                stack.push_back(ptrs[cur]);
                        }
                        cur++;
                }
                printf("%ld\n",stack.size()-1);
        }
}

