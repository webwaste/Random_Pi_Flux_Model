#include"../Headers/lattice.h"
#include"../Headers/matrix.h"
#include<fstream>
#include<json/json.h>
#include<cmath>


int main(int argc, char* argv[]){
	matrix ham(3,3);
	ham.array[0]=3;
	ham.array[1]=-2;
	ham.array[2]=4;
	ham.array[3]=-2;
	ham.array[4]=6;
	ham.array[5]=2;
	ham.array[6]=4;
	ham.array[7]=2;
	ham.array[8]=3;


	matrix eigvec(3,3);
	double* eigval = ham.eig_val(); 
	cout<<eigval[0]<<endl;
	cout<<eigval[1]<<endl;
	cout<<eigval[2]<<endl;
	eigvec.array = ham.eig_vec();
	eigvec.write("matrix.mat");


	//Writing the hamiltonian into a file
/*	ofstream ham("Data/"+pid+"Hamiltonian.mat");
	ham<<hamiltonian; 
	ham.close();
	*/
}

			
