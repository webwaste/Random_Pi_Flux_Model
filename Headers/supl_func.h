#include<iostream> 
#include<cblas.h>
#include<fstream>
#include<filesystem>
#include<cmath>
#include<complex>
#include<bitset>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/LU>
#include<eigen3/Eigen/SVD>
#include<string>
using namespace std; 
using namespace Eigen; 
using MatrixXc = Matrix<complex<double>, Dynamic, Dynamic>;

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

Matrix<complex<double>, Dynamic, Dynamic> cload(string name, int row, int col){
	complex<double>* data;
	data = (complex<double>*) malloc(row*col*sizeof(complex<double>));
	ifstream file(name);
	for(int i = 0; i<row*col; i++){
		file>>data[i];
	}
	Map<Matrix<complex<double>, Dynamic, Dynamic, RowMajor>> mat(data,row,col);
	return mat;
}


MatrixXd dload(string name, const int row, const int col){
	double* data;
	data = (double*) malloc(row*col*sizeof(double));
	ifstream file(name);
	for(int i = 0; i<row*col; i++){
		file>>data[i];
	}
	Map<Matrix<double, Dynamic, Dynamic, RowMajor>> mat(data,row,col);
	return mat;
}

MatrixXi iload(string name, const int row, const int col){
	int* data;
	data = (int*) malloc(row*col*sizeof(int));
	ifstream file(name);
	for(int i = 0; i<row*col; i++){
		file>>data[i];
	}
	Map<Matrix<int, Dynamic, Dynamic, RowMajor>> mat(data,row,col);
	return mat;
}
