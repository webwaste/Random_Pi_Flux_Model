#include"lattice.h"
#include<vector>
//The purpse of this module is to take a predefined pi-flux configuration
//and fix the gauge(values of the edges) 
//and return a lattice configuration as outuput.

template <typename T> int sgn(T val) {
	    return (T(0) < val) - (val < T(0));
}


int main(){

	string input_file = "rand_pi_flux.lat";
	lattice lat(2,2);
	lat.read(input_file);
	vector<int> pi_flux_list; //The consecutive elements are assumed to be coupled, starting from zero. 
	
	//Constructing the list from the input file.
	for(int i=0; i<lat.Ny(); i++){
		for(int j =0; j<lat.Nx(); j++){
			if(lat.plqt(j,i)){
				pi_flux_list.push_back(lat.Nx()*i + j);
				cout<<"pi_flux found at "<<j<<" "<<i<<endl;
			}
		}
	}

	//all the edge values are made 0. 
	lat.reset_edges();

	for(int i=0; i<pi_flux_list.size(); i+=2){
		int plqt_1_x = pi_flux_list[i]%lat.Nx();
		int plqt_1_y = pi_flux_list[i]/lat.Nx();
		int plqt_2_x = pi_flux_list[i+1]%lat.Nx();
		int plqt_2_y = pi_flux_list[i+1]/lat.Nx();



		int xdiff = plqt_2_x - plqt_1_x;
		int ydiff = plqt_2_y - plqt_1_y;

		int curr_pos_x = plqt_1_x;
		int curr_pos_y = plqt_1_y;

		// First we have to move along the x. 
		while(curr_pos_x != plqt_2_x){
			curr_pos_x += sgn(xdiff);
			if(sgn(xdiff) == 1){
			   	lat.flip_v_edge(curr_pos_x,curr_pos_y);
			}
			else if(sgn(xdiff) == -1){
			   	lat.flip_v_edge(curr_pos_x+1,curr_pos_y);
			}
		}
		// Now we move along y.	
		while(curr_pos_y != plqt_2_y){
			curr_pos_y += sgn(ydiff);
			if(sgn(ydiff) == 1){
			   	lat.flip_h_edge(curr_pos_x,curr_pos_y);
			}
			else if(sgn(xdiff) == -1){
			   	lat.flip_h_edge(curr_pos_x,curr_pos_y+1);
			}
		}
	}
	lat.write("fixed_gauge.lat");
	
}
