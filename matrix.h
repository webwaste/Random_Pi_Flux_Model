#include<iostream>
#include<cstring>
#include<fstream>
using namespace std; 

class matrix{
	public:
	int row; 
	int col; 
	double* array = (double*) malloc(row*col*sizeof(double));

	matrix(int i=1, int j=1):row(i),col(j) {}
	double elmnt(int r, int c){
		return array[r*col + c];
	}

	void read(string name){
		ifstream ifile(name);
		if(!ifile.is_open()){
			cout<<"File not openned"<<endl;
		}
		else{
			ifile>>row;
			ifile>>col;
			double* temp_array = (double*) malloc(row*col*sizeof(double));
			free(array);
			array = temp_array;
			for(int i=0; i<row*col; i++){
				ifile>>array[i];
			}
			ifile.close();
		}
	}

	void write(string name){
		ofstream ofile(name);
		if(!ofile.is_open()){
			cout<<"File not openned"<<endl;
		}
		else{
			ofile<<row<<"\t"<<col<<endl;
			for(int i = 0; i<row; i++){
				for(int j = 0; j<col; j++){
					ofile<<array[i*col + j]<<"\t";
				}
				ofile<<endl;
			}
			ofile.close();
		}
	}
};

