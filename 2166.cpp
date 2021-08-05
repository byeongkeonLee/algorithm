#include<stdio.h>

double abs(double a){
	return a>0? a:-a;
}
int main(){
	int N;
	scanf("%d",&N);
	long long ans=0;

	int x0,y0;
	int xp,yp;
	int a,b;
	for(int i=0; i<N; i++){
		scanf("%d %d",&a,&b);
		if(i>0){
			ans += ((long)xp*b-(long)yp*a);
		}else{
			x0 = a;
			y0 = b;
		}
		xp = a;
		yp = b;
	}
	ans += (long)xp*y0-(long)yp*x0;
	printf("%.1lf",abs((double)ans/2));

}
