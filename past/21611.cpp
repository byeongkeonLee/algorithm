#include<stdio.h>
#include<string.h>
using namespace std;

int arr[2601],in[49][49];
int tmp[49*49]={0,}, ptr;
int N,q,L;
int key[51][51];

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int ANS = 0;

int idr[4] = {0,1,0,-1};
int idc[4] = {-1,0,1,0};
void init(){
	int r,c;
	r = c = N/2;
	int S = 1;
	int cnt = 0;
	while(c>=0){
		for(int k=0; k<4 && c>=0; k++){
			for(int i=0;i<S && c>=0;i++){
				r += idr[k];
				c += idc[k];
				arr[cnt] = in[r][c];
				key[r][c] = cnt++;
			}
			if(k%2==1) S++;
		}
	}
	L = cnt;
}
void bli(int d,int s){
	int r,c;
	r = c = N/2;
	for(int i=1;i<=s;i++){
		int nr = r+dr[d]*i, nc = c+dc[d]*i;
		arr[key[nr][nc]] = 0;
	}
}
int Del(int idx, int cnt, int now){
	int f = 0;
	if(cnt>=4){
		f = 1;
		for(int j=0;j<cnt;j++){
			arr[idx + j] = 0;
		}
		ANS += cnt*now;
	}
	return f;
}
int boom(){
	int now = -1, cnt = 0, idx = -1;
	int flag = 0;
	for(int i=0;i<L;i++){
		if(now != arr[i]){
			flag |= Del(idx, cnt, now);
			now = arr[i]; cnt = 0; idx = i;
		}
		cnt ++;
	}
	return flag | Del(idx, cnt, now);
}
int g(int cnt, int now){
	if(now>0){
		tmp[ptr] = cnt;
		tmp[ptr+1] = now;
		ptr += 2;
		if(ptr>N*N-1) return 1;
	}
	return 0;
}
void gen(){
	int now = -1, cnt=-1;
	ptr = 0;
	memset(tmp, 0, (N*N-1)*sizeof(int));
	for(int i=0; arr[i]!=0 ; i++){
		if(now != arr[i]){
			if(g(cnt, now)) break;
			now = arr[i]; cnt = 0;
		}
		cnt++;
	}
	g(cnt,now);
	L = ptr;
	memcpy(arr,tmp,(N*N-1)*sizeof(int));
}
void zip(){
	int d = 0;
	int i = 0;
	for(i=0;i<L;i++){
		if(d>0)
			arr[i-d] = arr[i];
		if(arr[i]==0)
			d++;
	}
	L -= d;
	for(i= L; i<N*N-1;i++) arr[i] = 0;
}
int main(){
	scanf("%d %d",&N,&q);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			scanf("%d",&in[i][j]);
		}
	}
	init();
	int dir,s;
	while(q--){
		scanf("%d %d",&dir, &s);
		bli(dir-1,s);
		zip();
		while(boom())
			zip();
		gen();
	}
	printf("%d\n",ANS);
}
