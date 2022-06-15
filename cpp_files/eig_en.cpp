#include"../Headers/supl_func.h"
#include"../Headers/lattice.h"
#include<eigen3/Eigen/Core>
#include <eigen3/Eigen/Eigenvalues>
#include<vector>
using namespace Eigen;

//Eigen package takes care of the linear algebra stuffs. 


int main(){
	lattice lat(2,2);
	lat.read("../Data/fixed_gauge.lat");
	int dim = lat.Nx()*lat.Ny(); // Dimension of the hamiltonian matrix
	
	string input_file = "../Data/Hamiltonian.mat";
	MatrixXd hamiltonian(dim,dim);
   	hamiltonian = dload(input_file,dim,dim);
	EigenSolver<MatrixXd> eig(hamiltonian);
//	cout<<"Eigen values: \n"<<eig.eigenvalues().real()<<endl;
	vector<double> eig_val;
	for(int i=0; i<dim; i++){
	   	eig_val.push_back(eig.eigenvalues().real()[i]);
	}
	sort(eig_val.begin(), eig_val.end());
	for(int i = 0; i<dim; i++){
		cout<<eig_val[i]<<" ";
	}
	cout<<endl;

	return 0; 

}

			
