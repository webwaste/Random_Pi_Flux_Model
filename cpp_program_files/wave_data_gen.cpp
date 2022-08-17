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

	vector<double> sub_lat_1;
	vector<double> sub_lat_2;
	vector<double> sub_lat_3;
	vector<double> sub_lat_4;
	vector<double> full_lat;

	ofstream f_sublat_1("Data/"+to_string(Lx)+"_sub_lat_1.wave");
	ofstream f_sublat_2("Data/"+to_string(Lx)+"_sub_lat_2.wave");
	ofstream f_sublat_3("Data/"+to_string(Lx)+"_sub_lat_3.wave");
	ofstream f_sublat_4("Data/"+to_string(Lx)+"_sub_lat_4.wave");
	ofstream f_full_lat("Data/f"+to_string(Lx)+"_ull_lat.wave");
	ofstream diag1_sublat_1("Data/"+to_string(Lx)+"_diag1_sub1.dat");
	ofstream diag2_sublat_1("Data/"+to_string(Lx)+"_diag2_sub1.dat");
	ofstream diag1_sublat_2("Data/"+to_string(Lx)+"_diag1_sub2.dat");
	ofstream diag2_sublat_2("Data/"+to_string(Lx)+"_diag2_sub2.dat");
	ofstream diag1_sublat_3("Data/"+to_string(Lx)+"_diag1_sub3.dat");
	ofstream diag2_sublat_3("Data/"+to_string(Lx)+"_diag2_sub3.dat");
	ofstream diag1_sublat_4("Data/"+to_string(Lx)+"_diag1_sub4.dat");
	ofstream diag2_sublat_4("Data/"+to_string(Lx)+"_diag2_sub4.dat");

	matrix wave_func(dim,dim);
	wave_func.read("Data/zero_eng_state.dat");

	for(int i=0; i<dim; i++){
		int x = i%Lx;
		int y = i/Lx;
		if(x==0){
			f_sublat_1<<endl;
			f_sublat_2<<endl;
			f_sublat_3<<endl;
			f_sublat_4<<endl;
			f_full_lat<<endl;
		}
		
		if(x%2==0 and y%2==0){
			sub_lat_4.push_back(wave_func.get(dim/2,i));
			f_sublat_4<<x<<" "<<y<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			if(x+y==Lx-1){
				float rx = sqrt(2)*(Ly/2 - y);
				diag1_sublat_4<<rx<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			}

			if(x==y){
				float rx = sqrt(2)*(Ly/2 - y);
				diag2_sublat_4<<rx<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			}
		}
		if(x%2==1 and y%2==0){
			sub_lat_2.push_back(wave_func.get(dim/2,i));
			f_sublat_2<<x<<" "<<y<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			if(x+y==Lx-2){
				float rx = sqrt(2)*(Ly/2 - y);
				diag1_sublat_2<<rx<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			}

			if(x==y+1){
				float rx = sqrt(2)*(Ly/2 - y);
				diag2_sublat_2<<rx<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			}
		}
		if(x%2==0 and y%2==1){ 
			sub_lat_1.push_back(wave_func.get(dim/2,i));
			f_sublat_1<<x<<" "<<y<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			if(x+y==Lx){
				float rx = sqrt(2)*(Ly/2 - y);
				diag1_sublat_1<<rx<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			}

			if(x==y-1){
				float rx = sqrt(2)*(Ly/2 - y);
				diag2_sublat_1<<rx<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			}
		}
		if(x%2==1 and y%2==1){
			sub_lat_3.push_back(wave_func.get(dim/2,i));
			f_sublat_3<<x<<" "<<y<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			if(x+y==Lx-1){
				float rx = sqrt(2)*(Ly/2 - y);
				diag1_sublat_3<<rx<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			}

			if(x==y){
				float rx = sqrt(2)*(Ly/2 - y);
				diag2_sublat_3<<rx<<" "<<abs(wave_func.get(dim/2,i))<<endl;
			}
		}

		full_lat.push_back(wave_func.get(dim/2,i));
		f_full_lat<<x<<" "<<y<<" "<<abs(wave_func.get(dim/2,i))<<endl;
	}

	f_sublat_1.close();
	f_sublat_2.close();
	f_sublat_3.close();
	f_sublat_4.close();
	f_full_lat.close();
	diag1_sublat_1.close();
	diag2_sublat_1.close();
	diag1_sublat_2.close();
	diag2_sublat_2.close();
	diag1_sublat_3.close();
	diag2_sublat_3.close();
	diag1_sublat_4.close();
	diag2_sublat_4.close();

	return 0; 
}

			
