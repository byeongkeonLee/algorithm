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
	bool deterministic = false;
	double X, Y;
	//one line detection
	if(abc==0 || abd==0 || cda==0 || cdb==0){
		//four in one line
		if(abc==0 && abd==0){
			int leftABX = min(a[0],b[0]);
			int rightABX = max(a[0],b[0]);
			int leftABY = min(a[1],b[1]);
			int rightABY = max(a[1],b[1]);

			ANS = (c[0]>=leftABX && c[0]<=rightABX && c[1]>=leftABY && c[1]<=rightABY || d[0]>=leftABX && d[0]<=rightABX && d[1]>=leftABY && d[1]<=rightABY);
			
			int leftCDX = min(c[0],d[0]);
			int rightCDX = max(c[0],d[0]);
			int leftCDY = min(c[1],d[1]);
			int rightCDY = max(c[1],d[1]);
			ANS = ANS | (a[0]>=leftCDX && a[0]<=rightCDX && a[1]>=leftCDY && a[1]<=rightCDY  || b[0]>=leftCDX && b[0]<=rightCDX && b[1]>=leftCDY && b[1]<=rightCDY);

			if(rightABX==leftCDX && rightABY==leftCDY){
				deterministic = true;
				X = rightABX;
				Y = rightABY;
			}else if(rightCDX==leftABX && rightCDY==leftABY){
				deterministic = true;
				X = rightCDX;
				Y = rightCDY;
			}
			
			
		}else if(abc==0 || abd==0){
			ANS = cda*cdb<=0;
			if(abc==0){
				deterministic = true;
				X = c[0];
				Y = c[1];
			}else if(abd==0){
				deterministic = true;
				X = d[0];
				Y = d[1];
			}
		}else{
			ANS = abc*abd<=0;
			if(cda==0){
				deterministic = true;
				X = a[0];
				Y = a[1];
			}else if(cdb==0){
				deterministic = true;
				X = b[0];
				Y = b[1];
			}
		}
	}else{
		bool flag = ccw(a,b,c)*ccw(a,b,d) <0;
		bool flag2 = ccw(c,d,a)*ccw(c,d,b) <0;
		if(flag && flag2){
			if(b[0]!=a[0] && c[0]!=d[0]){
				double alpha = ((double)b[1]-a[1])/((double)b[0]-a[0]);
				double gamma = ((double)d[1]-c[1])/((double)d[0]-c[0]);
				double beta = ((double)a[1] - ((double)b[1]-a[1])*a[0]/((double)b[0]-a[0]));
				double delta = ((double)c[1] - ((double)d[1]-c[1])*c[0]/((double)d[0]-c[0]));
				X = (delta-beta)/(alpha-gamma);
				Y = alpha*X+beta;
			}else if(a[0]==b[0]){
				X = a[0];
				double gamma = ((double)d[1]-c[1])/((double)d[0]-c[0]);
				double delta = ((double)c[1] - ((double)d[1]-c[1])*c[0]/((double)d[0]-c[0]));
				Y = gamma*X+delta;
			}else{
				X = c[0];
				double alpha = ((double)b[1]-a[1])/((double)b[0]-a[0]);
				double beta = ((double)a[1] - ((double)b[1]-a[1])*a[0]/((double)b[0]-a[0]));
				Y = alpha*X+beta;
			}
			deterministic = true;
			ANS = true;
		}
	}
	if(ANS){ printf("1\n");
	if(deterministic) printf("%.16lf %.16lf\n",X, Y);}
	else printf("0\n");
}

