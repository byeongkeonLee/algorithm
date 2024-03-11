#include<stdio.h>
#include<complex>
#include<string.h>
#include<vector>
#include<math.h>
using namespace std;

typedef complex<double> Complex;


char a[300001], b[300001];
int N = 1;
void fft(vector<Complex> &c, Complex w){
	int n = c.size();
	if(n == 1) return;

	vector<Complex> even(n/2), odd(n/2);
	for(int i=0; i<n; i++){
		(i%2 ? odd : even)[i/2] = c[i];
	}

	fft(even, w*w);
	fft(odd, w*w);

	Complex wp(1, 0);
	for(int i = 0; i < n/2; i++){
		c[i] = even[i] + wp*odd[i];
		c[i+n/2] = even[i] - wp*odd[i];
		wp *= w;
	}
}
int main(){
	scanf("%s %s\n",a, b);

	int a_len = strlen(a);
	int b_len = strlen(b);
	int l = a_len > b_len ? a_len : b_len;
		
	while(l){
		l>>=1;
		N <<= 1;
	}
	N <<= 2;

	vector<Complex> a_dft, b_dft;
	for(int i=a_len-1; i>=0; i--)
		a_dft.push_back(Complex(a[i] - '0', 0));
	for(int i=a_len; i<N; i++)
		a_dft.push_back(Complex(0,0));

	for(int i=b_len-1; i>=0; i--)
		b_dft.push_back(Complex(b[i] - '0', 0));
	for(int i=b_len; i<N; i++)
		b_dft.push_back(Complex(0,0));

	Complex base = Complex(cos(2*M_PI / N), sin(2*M_PI / N));
	fft(a_dft, base);
	fft(b_dft, base);

	vector<Complex> c_dft(N);
	
	for(int i=0; i<N; i++){
		c_dft[i] = a_dft[i] * b_dft[i];
//		printf("i %d: a:(%f, %f) b:(%f, %f) c:(%f, %f)\n", i, a_dft[i].real(), a_dft[i].imag(), b_dft[i].real(), b_dft[i].imag(), c_dft[i].real(), c_dft[i].imag());

	}

	fft(c_dft, Complex(1,0)/base);

	vector<int> ans;

	for(int i=0; i<N; i++){
		c_dft[i] /= Complex(N, 0);
		c_dft[i] = Complex(round(c_dft[i].real()), round(c_dft[i].imag()));
	}

	long long int tmp = 0;
	for(int i=0; i<N; i++){
		tmp = (long long int)(c_dft[i].real()+tmp);
	//	printf("[%lld]",tmp);
		ans.push_back(tmp%10);
		tmp /= 10;	
	}
	bool zero_flag = false;
	for(int i= ans.size()-1; i >= 0; i--){
		if(ans[i] !=0) zero_flag = true;
		if(zero_flag) printf("%d",ans[i]);
	}
	if(!zero_flag) printf("0");
	printf("\n");

}
