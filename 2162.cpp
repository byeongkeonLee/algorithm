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

int checker(int a[2], int b[2], int c[2], int d[2]){
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
	if(ANS) return 1;
	else return 0;

}
int arr[3000][2][2];

int parent[3000];
int find(int a){
	if(parent[a] == a){
		return a;
	}else{
		return parent[a] = find(parent[a]);
	}
}
int cnt[3000];
int main(){
	int N;
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		scanf("%d %d %d %d",&arr[i][0][0], &arr[i][0][1], &arr[i][1][0], &arr[i][1][1]);
		parent[i] = i;
	}
	int val;
	for(int i=0;i<N;i++){
		for(int j=i+1; j<N; j++){
			val = checker(arr[i][0], arr[i][1], arr[j][0], arr[j][1]);
			if(val==1){
				int find_i = find(i);
				int find_j = find(j);
				if(find_i != find_j) parent[find_j] = find_i;
			}
		}
	}
	for(int i=0; i<N; i++){
		cnt[find(i)]++;
	}
	int Dist=0;
	int Max=0;
	for(int i=0; i<N; i++){
		if(cnt[i]!=0){
			Dist++;
			if(Max < cnt[i]) Max = cnt[i];
		}
	}
	printf("%d\n%d\n",Dist,Max);
}

