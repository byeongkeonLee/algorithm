#include<stdio.h>
#include<vector>
#include<math.h>
#include<algorithm>
#define DEF 100000000000000L
using namespace std;

class Ptr{
        public:
                int x;
                int y;
                double angle;
                Ptr(int x_, int y_): x(x_), y(y_){};
};
bool cmp(const Ptr& a, const Ptr& b){
		long k = a.angle * DEF;
		long r = b.angle * DEF;
		printf("%lld %lld\n",k,r);
		if(k!=r)
			return k<r;
		else
			return 1LL*a.x*a.x + a.y*a.y < 1LL*b.x*b.x + b.y*b.y;
}
vector<Ptr> ptrs;
vector<int> stack;
int CCW(Ptr a, Ptr b, Ptr c){ // a->b  b->c
        int x1 = b.x - a.x, y1 = b.y - a.y;
        int x2 = c.x - b.x, y2 = c.y - b.y;

        long val = 1LL*x1*y2 - 1LL*x2*y1;
        if(val > 0) return 1;
        else if (val == 0) return 0;
        else return -1;
}
int main(){
        int N;
        int a, b, y_min, y_val=40001, x_val;
        scanf("%d",&N);
        for(int i=0; i<N; i++){
                scanf("%d %d",&a,&b);
                ptrs.push_back(Ptr(a,b));
                if(y_val > b){
                        y_val = b;
                        x_val = a;
                        y_min = i;
                }
        }
        for(auto itr = ptrs.begin(); itr != ptrs.end(); itr++){
                a = itr->x - x_val;
                b = itr->y - y_val;
                itr->x = a;
                itr->y = b;
                if(a==0 && b==0){
                        itr->angle = -99999;
                        continue;
                }
                itr->angle = acos((double)a/sqrt((double)(1LL*a*a+1LL*b*b)));
        }
        sort(ptrs.begin(), ptrs.end(), cmp);

        stack.push_back(0);
        int cur = 1;

        while(cur < N){
                int back = stack.back();
                if(back==0){
                        stack.push_back(cur);
                }else{
                        a = stack[stack.size()-2];
                        b = stack[stack.size()-1];
                        int ret = CCW(ptrs[a], ptrs[b], ptrs[cur]);
						
                        if(ret <= 0){
                                stack.pop_back();
                                continue;
                        }
                        stack.push_back(cur);
                }
                cur++;
        }
		for(int i=0; i<ptrs.size(); i++){
			printf("%d %d %lf\n",ptrs[i].x, ptrs[i].y, ptrs[i].angle);
		}
        printf("%ld\n",stack.size());
}

