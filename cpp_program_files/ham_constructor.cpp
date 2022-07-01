#include"../Headers/lattice.h"
#include<eigen3/Eigen/Core>
using namespace Eigen;

//Eigen package takes care of the linear algebra stuffs. 


int main(int argc, char* argv[]){
	string pid=""; 
	if(argc==2){
		pid = argv[1];
	}

	double mu = 0; // chemical potential
			
	lattice lat(2,2); //Initialization
	lat.read("Data/"+pid+"fixed_gauge.lat");

	int dim = lat.Nx()*lat.Ny(); // Dimension of the hamiltonian matrix
	MatrixXd hamiltonian(dim,dim);
   	hamiltonian	= MatrixXd::Identity(dim,dim)*mu;


	for(int y=0; y<lat.Ny(); y++){
		for(int x=0; x<lat.Nx(); x++){

			int i = y*lat.Nx() + x; 

			// calculating the coordinates of horizontal neighbour.
			int h_nbr_x = (x+1)%lat.Nx();
			int h_nbr_y = y;
			int j_h = h_nbr_y*lat.Nx() + h_nbr_x;

			// calculating the coordinates of vertical neighbour.
			int v_nbr_x = x; 
			int v_nbr_y = (y+1)%lat.Ny();
			int j_v = v_nbr_y*lat.Nx() + v_nbr_x;

			hamiltonian(i,j_h) = 2*lat.h_edge(x,y)-1;
			hamiltonian(j_h,i) = 2*lat.h_edge(x,y)-1;
			hamiltonian(i,j_v) = 2*lat.v_edge(x,y)-1;
			hamiltonian(j_v,i) = 2*lat.v_edge(x,y)-1;
		}
	}
	//Writing the hamiltonian into a file
	ofstream ham("Data/"+pid+"Hamiltonian.mat");
	ham<<hamiltonian; 
	ham.close();
}

			
