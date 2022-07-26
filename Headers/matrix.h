#include<iostream>
#include<cstring>
#include<fstream>
#include<cblas.h>
#include<vector>
using namespace std; 

extern "C"{
	void dsyev_(char* JOBZ, char* UPLO, int* N, double* A, int* LDA, double* W, double* WORK, int* LWORK, int* INFO);
}


class matrix{
	public:
	int row; 
	int col; 
	double* array = (double*) malloc(row*col*sizeof(double));

	matrix(int r=1, int c=1):row(r),col(c) {
	for(int i=0; i<r*c; i++){
		array[i]=0;
	}
	}

	double get(int r, int c){
		return array[r*col + c];
	}

	void set(double a, int r, int c){
		array[r*col + c] = a;
	}


	double* eig_val(){
		char JOBZ = 'N'; //computes only eigen values.
		char UPLO = 'U'; //upper triagular part of A is considered. 
		int N = row;
		int LDA = row;
		double* W = (double*) malloc(row*sizeof(double));
		int LWORK = row*col;
		double* WORK = (double*) malloc(LWORK*sizeof(double));
		int INFO = 0;

		dsyev_(&JOBZ, &UPLO, &N, array, &LDA, W, WORK, &LWORK, &INFO);
//		vector<double> eigv(W, W + sizeof(W)/sizeof(W[0]));
//		return eigv;
		return W;
	}

	double* eig_vec(){
		char JOBZ = 'V'; //computes eigenvectors.
		char UPLO = 'U'; //upper triagular part of A is considered. 
		int N = row;
		int LDA = row;
		double* W = (double*) malloc(row*sizeof(double));
		int LWORK = 3*row*col;
		double* WORK = (double*) malloc(LWORK*sizeof(double));
		int INFO = 0;

		dsyev_(&JOBZ, &UPLO, &N, array, &LDA, W, WORK, &LWORK, &INFO);
//		vector<double> eigv(W, W + sizeof(W)/sizeof(W[0]));
//		return eigv;
		return array;
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

