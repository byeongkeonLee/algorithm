#include<stdio.h>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

string in[100000];

class H{
	public:
	string str;
	int idx;
	H(string str_, int idx_):str(str_), idx(idx_){};
};

bool cmp(const H& a, const H& b){
	return a.str.compare(b.str)<0;
}

vector<H> h;

int search(string target){
	int start = 0, end = h.size(), mid;
	while(start!=end){
		mid = (start+end)/2;
//		printf("<<%s %s>>",target.c_str(), h[mid].str.c_str());
		if(target.compare(h[mid].str)<=0){
			end = mid;
		}else{
			start = mid+1;
		}
	}
	return h[start].idx;
}
int main(){
	int N,M;
	scanf("%d %d",&N,&M);

	char input[22];
	for(int i=0; i<N; i++){
		scanf("%s", input);
		in[i] = std::string(input);
		h.push_back(H(in[i], i+1));
	}
	sort(h.begin(), h.end(), cmp);

	for(int i=0; i<M; i++){
		scanf("%s",input);
		if(input[0]>='0' && input[0] <='9'){
			printf("%s\n",in[atoi(input)-1].c_str());
		}else{
			printf("%d\n",search(input));
		}
	}
}
