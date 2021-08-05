#include<stdio.h>


int ccw(int a[2], int b[2], int c[2]){
	int ab[2], bc[2];
	ab[0] = b[0]-a[0];
	ab[1] = b[1]-a[1];
	bc[0] = c[0]-b[0];
	bc[1] = c[1]-b[1];

	return ((long)ab[0]*bc[1]-(long)ab[1]*bc[0])>0? 1:-1;
}
int main(){
	int a[2], b[2], c[2], d[2];
	scanf("%d %d",&a[0], &a[1]);
	scanf("%d %d",&b[0], &b[1]);
	scanf("%d %d",&c[0], &c[1]);
	scanf("%d %d",&d[0], &d[1]);

	bool flag = ccw(a,b,c)*ccw(a,b,d) <0;
	bool flag2 = ccw(c,d,a)*ccw(c,d,b) <0;
	if(flag && flag2) printf("1\n");
	else printf("0\n");
}

