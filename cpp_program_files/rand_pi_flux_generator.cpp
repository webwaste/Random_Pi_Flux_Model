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

	lattice lat(Lx,Ly);
	ofstream ofile("Data/"+pid+"rand_pi_flux.list");

	vector<int> pi_flux; 

	int min = 0;
	int max = Lx*Ly-1;
	std::random_device rd; // only used once to initialise (seed) engine
	std::mt19937 rng(rd());// random-number engine used (Mersenne-Twister)
	std::uniform_int_distribution<int> uni(min,max);
	
	auto random_integer = uni(rng);

	while(pi_flux.size()<N_pi){
		random_integer = uni(rng);

		if(std::find(pi_flux.begin(), pi_flux.end(), random_integer) == pi_flux.end()){
			pi_flux.push_back(random_integer);
			int x = random_integer%Lx;
			int y = random_integer/Lx;

			ofile<<"("<<x<<","<<y<<")"<<endl;
			lat.flip_plqt(x,y);
		}

		else continue; 
	}
	ofile.close();
	lat.write("Data/"+pid+"rand_pi_flux.lat");


	return 0; 
}
