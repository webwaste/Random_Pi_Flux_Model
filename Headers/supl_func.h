#include<iostream> 
#include<cblas.h>
#include<fstream>
#include<filesystem>
#include<cmath>
#include<complex>
#include<bitset>
#include<string>
using namespace std; 

template <typename T> int sgn(T val) {
	//Signum function. returns the sign of a non-zero number. and returns 0 for 0.
	    return (T(0) < val) - (val < T(0));
}

int C(const int N, int n){
	// ================================================
	// Function for calculating N choose n 
	// ===============================================-

		return tgamma(N+1)/(tgamma(n+1)*tgamma(N-n+1));
}
int bas_size(int n,const int N,const int L){
	// ================================================
	// Function for calculating number of config for a given n, N, L.
	// ===============================================-

		return C(L/2,n)*C(L/2,N-n);
}

