#include<stdio.h>
#include<algorithm>
using namespace std;
typedef struct vec{
        int a;
        int b;
}Vec;

bool cmp(const Vec& a, const Vec& b){
        return a.a < b.a;
}

Vec arr[1000000];
int N, Start, End, ans;
int main(){
        End = Start = -1000000001;
        scanf("%d",&N);
        for(int i=0;i<N;i++){
                scanf("%d %d",&arr[i].a, &arr[i].b);
        }
        sort(arr,arr+N,cmp);

        for(int i=0;i<N;i++){
                if(End < arr[i].a){ //case 1
                        ans += End - Start;
                        Start = arr[i].a;
                }
                if(End < arr[i].b) //case 2
                        End = arr[i].b;
        }
        ans += End - Start;
        printf("%d\n",ans);
        return 0;
}

