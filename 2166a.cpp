#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;
 
long double sum = 0;
int main()
{
    double x[10002];
    double y[10002];
    int n;
    int cnt = 0;
    cin >> n;
 
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
 
    x[n] = x[0];
    y[n] = y[0];
     
    for (int i = 0; i < n; i++)
        sum += ((x[i] * y[i + 1]) / 2 - (x[i + 1] * y[i]) / 2);
 
 
    printf("a%.1lf", fabs(sum));
}


