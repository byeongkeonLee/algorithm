#include<iostream>
using namespace std;
enum FACE{U,D,F,B,L,R};
char init[6] = {'w','y','r','o','g','b'};
char cube[6][3][3];

char pos[8][2] = {{0,0}, {0,1}, {0,2}, {1,2}, {2,2}, {2,1}, {2,0}, {1,0}};
char siderot[6][12][2] = {{{L,0}, {L,1}, {L,2}, {B,0}, {B,1}, {B,2}, {R,0}, {R,1}, {R,2}, {F,0}, {F,1}, {F,2}},
	{{L,6}, {L,7}, {L,8}, {F,6}, {F,7}, {F,8}, {R,6}, {R,7}, {R,8}, {B,6}, {B,7}, {B,8}},
	{{L,8}, {L,5}, {L,2}, {U,6}, {U,7}, {U,8}, {R,0}, {R,3}, {R,6}, {D,2}, {D,1}, {D,0}},
	{{R,2}, {R,5}, {R,8}, {U,0}, {U,1}, {U,2}, {L,6}, {L,3}, {L,0}, {D,8}, {D,7}, {D,6}},
	{{B,8}, {B,5}, {B,2}, {U,0}, {U,3}, {U,6}, {F,0}, {F,3}, {F,6}, {D,0}, {D,3}, {D,6}},
	{{F,2}, {F,5}, {F,8}, {U,2}, {U,5}, {U,8}, {B,6}, {B,3}, {B,0}, {D,2}, {D,5}, {D,8}}};

char Clock[8] = {6,7,0,1,2,3,4,5};
char anti_Clock[8] = {2,3,4,5,6,7,0,1};
char Clock_side[4][3] = {{3,4,5},{6,7,8},{9,10,11},{0,1,2}};
char anti_Clock_side[4][3] = {{9,10,11},{0,1,2},{3,4,5},{6,7,8}};
char _1to2r[9] = {0,0,0,1,1,1,2,2,2};
char _1to2c[9] = {0,1,2,0,1,2,0,1,2};


char face2char[128];
char tmp[8];
char tmp2[4][3];

void rotate(int face,int dir){
	int cur = 0, next = 0;
	int  target = 0;
	for(int i=0;i<8;i++){
		target = dir? Clock[i] : anti_Clock[i];
		tmp[i] = cube[face][pos[target][0]][pos[target][1]];
	}
	for(int i=0;i<8;i++){
		cube[face][pos[i][0]][pos[i][1]] = tmp[i];
	}
}

void process(int face, int dir){
	rotate(face, dir);
	int f, idx, r, c;

	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			f = siderot[face][i*3+j][0];
			idx = siderot[face][i*3+j][1];
			r = _1to2r[idx];
			c = _1to2c[idx];
			tmp2[i][j] = cube[f][r][c];
		}
	}
	int next;
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			next = dir? Clock_side[i][j] : anti_Clock_side[i][j];
			f = siderot[face][next][0];
			idx = siderot[face][next][1];
			r = _1to2r[idx];
			c = _1to2c[idx];
			cube[f][r][c] = tmp2[i][j];
		}
	}
}
int main(){
	int T;
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;

	face2char['U'] = U;
	face2char['D'] = D;
	face2char['F'] = F;
	face2char['B'] = B;
	face2char['L'] = L;
	face2char['R'] = R;


	while(T--){
		int n;
		cin >> n;

		for(int k=0;k<6;k++){
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					cube[k][i][j] = init[k];
				}
			}
		}
		char face, dir;
		for(int in=0;in<n;in++){
			cin >> face >> dir;
			face = face2char[face];
			dir = dir=='+'? 1:0;
			process(face, dir);
		}
		for(int i=0;i<3;i++){
			cout << cube[U][i][0] << cube[U][i][1]<< cube[U][i][2] <<'\n';
		}
	}
	return 0;
}

