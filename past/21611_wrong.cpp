#include<stdio.h>
#include<string.h>
using namespace std;

int arr[51*51], input[49][49];
int N,q, Len, F;
int key[51][51];

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int ANS = 0;
void make_list(){
        int r = N/2, c = N/2;
        int scale = 1;
        int cnt = 0;
        while(c>=0 && r>=0){
                for(int i=0;i<scale;i++){
                        c = c-1;
                        if(c<0)break;
                        arr[cnt] = input[r][c];
                        key[r][c] = cnt++;
                }
                if(c<0) break;
                for(int i=0;i<scale;i++){
                        r = r+1;
                        arr[cnt] = input[r][c];
                        key[r][c] = cnt++;
                }
                scale ++;
                for(int i=0;i<scale;i++){
                        c = c+1;
                        arr[cnt] = input[r][c];
                        key[r][c] = cnt++;
                }
                for(int i=0;i<scale;i++){
                        r = r-1;
                        arr[cnt] = input[r][c];
                        key[r][c] = cnt++;
                }
                scale ++;
        }
        Len = cnt;
}
void blizzard(int dir,int s){
        int r = N/2, c = N/2;
        for(int i=1;i<=s;i++){
                int nr = r+dr[dir]*i, nc = c+dc[dir]*i;
                arr[key[nr][nc]] = 0;
        }
}
int boom(){
        int now = -1, cnt = 0, s_index = -1;
        int flag = 0;
        for(int i=0;i<Len;i++){
                if(now != arr[i]){
                        if(cnt>=4){
                                flag = true;
                                for(int j=0;j<cnt;j++){
                                        arr[s_index + j] = 0;
                                }
                                ANS += cnt*now;
                        }
                        now = arr[i]; cnt = 1; s_index = i;
                }else{
                        cnt ++;
                }
        }
        if(cnt>=4){
                flag = true;
                for(int j=0;j<cnt;j++){
                        arr[s_index + j] = 0;
                }
                ANS += cnt*now;
        }
        return flag;
}
void gen(){
        int now = -1, cnt=-1, ptr = 0;
        int tmp[49*49]={0,};
        for(int i=0;i<Len;i++){
                if(now != arr[i]){
                        if(now>0){
                                tmp[ptr] = cnt;
                                tmp[ptr+1] = now;
                                ptr += 2;
                                if(ptr>N*N-1) break;
                        }
                        now = arr[i]; cnt = 1;
                }else{
                        cnt++;
                }
        }
        Len = ptr;
        memcpy(arr,tmp,(N*N-1)*sizeof(int));
}
void condense(){
        int space = 0;
        for(int i=0;i<Len;i++){
                if(space>0)
                        arr[i-space] = arr[i];
                if(arr[i]==0) space++;
        }
        for(int i=0;i<space;i++){
                arr[Len-space+i] = 0;
        }
        Len -= space;
}
void print_map(){
        for(int i=0;i<N*N;i++){
                printf("%d ",arr[i]);
        }
        printf("/ [%d]\n",Len);
        fflush(stdout);
}
int main(){
        scanf("%d %d",&N,&q);
        for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                        scanf("%d",&input[i][j]);
                }
        }
        make_list();
        int dir,s;
        while(q--){
                scanf("%d %d",&dir, &s);
                blizzard(dir-1,s);
		print_map();
                condense();
		print_map();
                while(boom()){
                        condense();
                };
		print_map();
                gen();
		print_map();
		printf("\n");
        }
        printf("%d\n",ANS);
        return 0;
}

