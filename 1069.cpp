#include<stdio.h>
#include<math.h>

double min(double a, double b){
	return a > b? b : a;
}
int max(int a, int b){
	return a > b? a : b;
}
int main(){
	int x,y,d,t;
	scanf("%d %d %d %d",&x, &y, &d, &t);

	double l = sqrt(x*x+y*y);

	double type1 = l;
	double type2 = 0;
	double type3 = 0;
	double type4 = 0;

	int N = 0, jumpD = 0;

	while(jumpD <= l){
		jumpD += d;
		N += 1;
	}
	N-=1; jumpD-=d;

	type2 = max(t*(N+1), 2*t);
	type3 = t*N+(l-d*N);
	type4 = t*(N+1)+(d*(N+1)-l);

	//	printf("jumpT : %d\n",jumpT);
	//	printf("%lf %lf %lf\n",type1, type2, type3);

	printf("%.16lf\n", min(min(type1, type2), min(type3,type4)));
}
