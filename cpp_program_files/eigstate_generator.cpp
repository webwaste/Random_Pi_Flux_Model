#include"../Headers/lattice.h"
#include"../Headers/matrix.h"
#include<fstream>
#include<json/json.h>
#include<cmath>


int main(int argc, char* argv[]){
	string pid=""; 
	if(argc==2){
		pid = argv[1];
	}

	double mu = 0; // chemical potential
			
	lattice lat(2,2); //Initialization
	lat.read("Data/"+pid+"fixed_gauge.lat");

	int dim = lat.Nx()*lat.Ny(); // Dimension of the hamiltonian matrix
	
	ifstream input("config.json");
	Json::Reader reader; 
	Json::Value config; 
	reader.parse(input,config);
	int Lx = config["Lx"].asInt();
	int Ly = config["Ly"].asInt();
//	string p = to_string(round(config["Probability"].asDouble()*100)/100);
//	cout<<p<<endl;
								 
//	MatrixXd hamiltonian(dim,dim);
//   	hamiltonian	= MatrixXd::Identity(dim,dim)*mu;

	matrix ham(dim,dim);


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
			ham.set(2*lat.h_edge(x,y)-1,i,j_h);
			ham.set(2*lat.h_edge(x,y)-1,j_h,i);
			ham.set(2*lat.v_edge(x,y)-1,i,j_v);
			ham.set(2*lat.v_edge(x,y)-1,j_v,i);

			/*
			hamiltonian(i,j_h) = 2*lat.h_edge(x,y)-1;
			hamiltonian(j_h,i) = 2*lat.h_edge(x,y)-1;
			hamiltonian(i,j_v) = 2*lat.v_edge(x,y)-1;
			hamiltonian(j_v,i) = 2*lat.v_edge(x,y)-1;
			*/
		}
	}
/*	
	SelfAdjointEigenSolver<MatrixXd> es;
	es.compute(hamiltonian);
	cout<<es.eigenvalues()<<endl;
*/
	matrix eigvec(dim,dim);
	eigvec.array = ham.eig_vec();

	ofstream eig_file("Data/contour.dat");
	ofstream diag_data("Data/diag.dat");

	for(int i=0; i<dim; i++){
		if(i%Lx==0){
			eig_file<<endl;
		}
		if(i%Lx+i/Lx==80 and i/Lx<=Lx/2){
			float rx = (Lx/2 - i/Lx);
			diag_data<<rx*sqrt(2)<<" "<<pow(eigvec.get(dim/2,i),2)<<endl;
		}
		eig_file<<i/Lx<<" "<<i%Lx<<" "<<pow(eigvec.get(dim/2,i),2)<<endl;
	}
	eig_file.close();
	diag_data.close();

	//Writing the hamiltonian into a file
/*	ofstream ham("Data/"+pid+"Hamiltonian.mat");
	ham<<hamiltonian; 
	ham.close();
	*/
}

			
