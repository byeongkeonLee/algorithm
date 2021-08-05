#include<stdio.h>


int ccw(int a[2], int b[2], int c[2]){
	int ab[2], bc[2];
	ab[0] = b[0]-a[0];
	ab[1] = b[1]-a[1];
	bc[0] = c[0]-b[0];
	bc[1] = c[1]-b[1];

	long ret = (long)ab[0]*bc[1]-(long)ab[1]*bc[0];
	if(ret >0) return 1;
	else if(ret==0) return 0;
	else return -1;
}
int min(int a, int b){
	return a>b?b:a;	
}
int max(int a, int b){
	return a<b?b:a;
}
int main(){
	int a[2], b[2], c[2], d[2];
	scanf("%d %d",&a[0], &a[1]);
	scanf("%d %d",&b[0], &b[1]);
	scanf("%d %d",&c[0], &c[1]);
	scanf("%d %d",&d[0], &d[1]);

	int abc = ccw(a,b,c);
	int abd = ccw(a,b,d);
	int cda = ccw(c,d,a);
	int cdb = ccw(c,d,b);

	bool ANS = false;
	//one line detection
	if(abc==0 || abd==0 || cda==0 || cdb==0){
		//four in one line
		if(abc==0 && abd==0){
			int leftX = min(a[0],b[0]);
			int rightX = max(a[0],b[0]);
			int leftY = min(a[1],b[1]);
			int rightY = max(a[1],b[1]);

			ANS = (c[0]>=leftX && c[0]<=rightX && c[1]>=leftY && c[1]<=rightY || d[0]>=leftX && d[0]<=rightX && d[1]>=leftY && d[1]<=rightY);

			leftX = min(c[0],d[0]);
			rightX = max(c[0],d[0]);
			leftY = min(c[1],d[1]);
			rightY = max(c[1],d[1]);
			ANS = ANS | (a[0]>=leftX && a[0]<=rightX && a[1]>=leftY && a[1]<=rightY  || b[0]>=leftX && b[0]<=rightX && b[1]>=leftY && b[1]<=rightY);

		}else if(abc==0 || abd==0){
			ANS = cda*cdb<=0;
		}else{
			ANS = abc*abd<=0;
		}
	}else{
		bool flag = ccw(a,b,c)*ccw(a,b,d) <0;
		bool flag2 = ccw(c,d,a)*ccw(c,d,b) <0;
		if(flag && flag2) ANS = true;
	}
	if(ANS) printf("1\n");
	else printf("0\n");
}

