#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>


int main(){
	double Lx = 8; 
	double Ly = 8; 
	double E  = 0; 
	std::vector<double> Energies;
	for(double ny = 0; ny<Ly; ny+=1){
		for(double nx = 0; nx<Lx; nx+=1){
			double kx = 2*M_PI*nx/Lx;
			double ky = 2*M_PI*ny/Ly;
			E = 2*(cos(kx) + cos(ky));
			Energies.push_back(E);
		}
	}
	std::sort(Energies.begin(), Energies.end());
	for(int i = 0; i<Energies.size(); i++){
		std::cout<<Energies[i]<<" ";
	}
	return 0; 
}
			


