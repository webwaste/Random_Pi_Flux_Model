#include"../Headers/lattice.h"
#include<vector>
#include <random>
#include<algorithm>
#include<fstream>
#include<json/json.h>

int main(int argc, char* argv[]){
	string pid=""; 
	if(argc==2){
		pid = argv[1];
	}

	ifstream input("config.json");
	Json::Reader reader; 
	Json::Value config; 
	reader.parse(input,config);

	int Lx = (config["Lx"]).asInt(); 
	int Ly = (config["Ly"]).asInt(); 
	int N_pi = (config["No_of_plaquettes"]).asInt(); 

	int x = Lx/2; 
	int y = Ly/2; 

	lattice lat(Lx,Ly);

	for(int i=0; i<Ly; i++){
		for(int j=0; j<Lx; j++){
			if(i==y and j==x){
				continue;
			}
			lat.flip_plqt(j,i);
		}
	}

	lat.write("Data/"+pid+"rand_pi_flux.lat");


	return 0; 
}
