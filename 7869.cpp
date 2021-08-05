#include<stdio.h>
#include<math.h>

inline double pow(double a){
	return a*a;
}
inline double min(double a, double b){
	return a>b? b:a;
}
int main(){

	double x1,y1,r1, x2,y2,r2;
	scanf("%lf %lf %lf %lf %lf %lf",&x1, &y1, &r1, &x2, &y2, &r2);

	double l=sqrt(pow(x2-x1)+pow(y2-y1));
	double ANS = 0;
	if(r1+r2<=l){
		ANS = 0;	
	}else if(r1+r2>l && abs(r1-r2)<l){
		double a = 2*acos((pow(l)+pow(r1)-pow(r2))/(2*l*r1));	
		double b = 2*acos((pow(l)+pow(r2)-pow(r1))/(2*l*r2));	
		ANS = pow(r1)*(a-sin(a))+pow(r2)*(b-sin(b));
		ANS /=2;
	}else{
		ANS = pow(min(r1,r2))*M_PI;
	}
	printf("%.3lf\n",ANS);
}
