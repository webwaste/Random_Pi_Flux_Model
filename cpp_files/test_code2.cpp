#include<iostream>
#include<vector>
#include<complex>
#include<cmath>
#include<algorithm>
#include"Headers/supl_func.h"
#include<eigen3/Eigen/Core>
#include <eigen3/Eigen/Eigenvalues>
using namespace Eigen;
using namespace std; 

int main(){
	double Lx = 4; 
	double Ly = 2; 
	double E  = 0; 
	complex<double> I = {0,1};
	
	MatrixXd T00, T01, T10, T_10, T0_1;
	MatrixXcd H;
	T00 = dload("Data/T00",8,8);
	T01 = dload("Data/T01",8,8);
	T10 = dload("Data/T10",8,8);
	T_10 = dload("Data/T_10",8,8);
	T0_1 = dload("Data/T0_1",8,8);
	

	std::vector<double> Energies;

	for(double ny = 0; ny<Ly; ny+=1){
		for(double nx = 0; nx<Lx; nx+=1){
			double kx = 2*M_PI*nx/Lx;
			double ky = 2*M_PI*ny/Ly;
			
			H = T00 + T01*exp(-I*ky) + T10*exp(-I*kx) + T_10*exp(I*kx) + T0_1*exp(I*ky);
			ComplexEigenSolver<MatrixXcd> eig(H);
			for(int i=0; i<8; i++){
				Energies.push_back(eig.eigenvalues().real()[i]);
			}
		}
	}
	std::sort(Energies.begin(), Energies.end());
	for(int i = 0; i<Energies.size(); i++){
		std::cout<<Energies[i]<<" ";
	}
	cout<<endl;
	return 0; 
}
			


