#include"../Headers/lattice.h"
#include<vector>
#include <random>
#include<algorithm>

int main(int argc, char** argv){
	int Lx = stoi(argv[1]); 
	int Ly = stoi(argv[2]); 
	int N_pi = stoi(argv[3]); 
	lattice lat(Lx,Ly);
	ofstream ofile("Data/rand_pi_flux.list");

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
	lat.write("Data/rand_pi_flux.lat");


	return 0; 
}
	/*

	
	for(int i=0; i<N_pi; i++){

	
	
*/
