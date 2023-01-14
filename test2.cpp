#include<stdio.h>
#include<string>

using namespace std;
char tmp[6] ={'a','b',0, 'c', 'd',0};
int main(){
	string a (tmp, 6);
	printf("%c",a[4]);
	printf("%d %s",a.length(), a.c_str());}
