#include<stdio.h>
#include<vector>
using namespace std;

vector<pair<unsigned int, int>> stack;

int main(){
	int N, input;
	scanf("%d",&N);
	long ANS = 0;
	bool flag;
	for(int i=0; i<N; i++){
		if(!flag)
			scanf("%d",&input);
		flag = false;
		if(stack.empty()){
			stack.push_back(make_pair(input, 1));
		}else if(input < stack.back().first){
			ANS++;
			stack.push_back(make_pair(input, 1));
		}else if(input == stack.back().first){
			ANS += stack.back().second;
			if(stack.size()!=1)
				ANS++;
			stack.back().second+=1;
		}else{
			while(!stack.empty() && input > stack.back().first){
				ANS += stack.back().second;
				stack.pop_back();
			}
			i--;
			flag = true;
		}
	}
	printf("%ld\n",ANS);
}
