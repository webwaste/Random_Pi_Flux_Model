#include"../Headers/lattice.h"
#include"../Headers/matrix.h"
#include<fstream>
#include<json/json.h>
#include<cmath>
#include<sstream>
#include<iomanip>


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

	matrix eig_states(dim,dim);
	matrix wavefunc_0(Ly,Lx);
	eig_states.read("Data/zero_eng_state.dat");

	for(int i=0; i<dim; i++){
		wavefunc_0.array[i] = eig_states.get(dim/2,i);
	}

//	for(int fact_y = 0; fact_y<Ly/2; fact_y++){
		int fact_y = 1;
		float angle = atan((float)fact_y);
		stringstream stream; 
		stream<<std::fixed<<std::setprecision(2)<<angle;
		string name = "angle_" + stream.str();
		ofstream f_line(name);

		for(int i=0; i<Lx/2; i++){
			int j = fact_y*i;
			if(j>Ly/2){
				break;
			}
			f_line<<sqrt(i*i + j*j)<<" "<<wavefunc_0.get(Lx/2 - j, Ly/2 + i)<<endl;
		}
		f_line.close();
	//}

	return 0; 
}

			
