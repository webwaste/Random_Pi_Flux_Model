#include"../Headers/lattice.h"
#include"../Headers/matrix.h"
#include<fstream>
#include<json/json.h>
#include<cmath>
#include<iomanip>
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


	matrix wave_func(dim,dim);
	wave_func.read("Data/"+to_string(Lx)+"X"+to_string(Ly)+"/"+to_string(Lx)+"_eig_states.dat");

	for(int en = -4; en< 4;  en++){
		ofstream low_eng_wave_func("Data/"+to_string(Lx)+"X"+to_string(Ly)+"/"+to_string(Lx)+"_low_eng_state_"+to_string(en+4)+".plt");
		for(int i=0; i<dim; i++){
			int x = i%Lx; // giving integers. 
			int y = i/Lx;
			if(x==0){
				low_eng_wave_func<<endl;
			}
			low_eng_wave_func<<setw(4)<<(y - Ly/2)<<" "<<setw(4)<<(x - Lx/2)<<" ";
			
			if(x%2==0 and y%2==0){
				low_eng_wave_func<<4<<" ";
	
			}
			if(x%2==1 and y%2==0){
				low_eng_wave_func<<2<<" ";
				
			}
			if(x%2==0 and y%2==1){ 
				low_eng_wave_func<<1<<" ";
			
			}
			if(x%2==1 and y%2==1){
				low_eng_wave_func<<3<<" ";
		
			}
	
			low_eng_wave_func<<wave_func.get(dim/2 + en,i)<<endl;
		}
		low_eng_wave_func.close();
	}


	return 0; 
}

			
