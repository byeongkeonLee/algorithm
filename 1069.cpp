#include<stdio.h>
#include<math.h>

double min(double a, double b){
	return a > b? b : a;
}
int main(){
	int x,y,d,t;
	scanf("%d %d %d %d",&x, &y, &d, &t);

	double l = sqrt(x*x+y*y);

	double type3 = l;
	double type2 = 0;
	double type1 = 0;
	int jumpT = 0, jumpD = 0;
	
	while(jumpD <= l){
		jumpD += d;
		jumpT += 1;
	}
	jumpT--; jumpD-=d;

	type1 = ((jumpT>0?jumpT:1)+1)*t;
	type2 = jumpT*t + (l-jumpD);
/*
	printf("jumpT : %d\n",jumpT);
	printf("%lf %lf %lf\n",type1, type2, type3);
*/
	printf("%.16lf\n", min(min(type1, type2), type3));
}
