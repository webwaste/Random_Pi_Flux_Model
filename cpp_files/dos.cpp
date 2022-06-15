#include"../Headers/supl_func.h"
#include"../Headers/lattice.h"
#include<eigen3/Eigen/Core>
using namespace Eigen;

//Eigen package takes care of the linear algebra stuffs. 


int main(){
	complex<double> I = {0,1}; //definition of iota.
	double eta = 0.01;

	lattice lat(2,2);
	lat.read("../Data/fixed_gauge.lat");
	int dim = lat.Nx()*lat.Ny(); // Dimension of the hamiltonian matrix
	
	string input_file = "../Data/Hamiltonian.mat";
	MatrixXd hamiltonian(dim,dim);
   	hamiltonian = dload(input_file,dim,dim);
	MatrixXc G; 
	ofstream ofile("../Data/Density_of_states.dat");
	for(double E = -5; E<5; E+=0.003){
		G = ((E + I*eta)*MatrixXd::Identity(dim,dim) - hamiltonian).inverse();
		double dos_E = - G.trace().imag()/(M_PI);
		ofile<<E<<" "<<dos_E<<endl;
	}
	ofile.close();
	return 0; 

}

			
