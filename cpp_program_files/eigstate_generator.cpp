#include"../Headers/lattice.h"
#include"../Headers/matrix.h"
#include<fstream>
#include<json/json.h>
#include<cmath>
#include<filesystem>


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

	filesystem::create_directories("Data/"+to_string(Lx)+"X"+to_string(Ly));

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

		}
	}

	matrix eigvec(dim,dim);
	eigvec.array = ham.eig_vec();

	eigvec.write("Data/"+to_string(Lx)+"X"+to_string(Ly)+"/"+to_string(Lx)+"_eig_states.dat");
}

			
