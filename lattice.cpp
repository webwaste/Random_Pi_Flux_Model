#include<iostream>
#include<cstring>
#include<fstream>
using namespace std; 


class lattice{
	int Lx, Ly;
	bool* points = (bool*) malloc(Lx*Ly*sizeof(bool)); // redundent 
	bool* h_edges = (bool*) malloc(Lx*Ly*sizeof(bool));
	bool* v_edges = (bool*) malloc(Lx*Ly*sizeof(bool));
	bool* plqts = (bool*) malloc(Lx*Ly*sizeof(bool));
	
	public:
	// Methods for initialization/ setting the Lx and Ly
	lattice(int Nx, int Ny){
		Lx = Nx; 
		Ly = Ny; 
		bool* h_edges_temp = (bool*) malloc(Lx*Ly*sizeof(bool));
		bool* v_edges_temp = (bool*) malloc(Lx*Ly*sizeof(bool));
		bool* plqts_temp = (bool*) malloc(Lx*Ly*sizeof(bool));
		free(h_edges); 
		free(v_edges);
		free(plqts);
		h_edges = h_edges_temp;
		v_edges = v_edges_temp;
		plqts = plqts_temp;
		for (int i = 0; i< Lx*Ly; i++){
			h_edges[i] = 0; 
			v_edges[i] = 0; 
			plqts[i] = 0; 
		}
	}

	// Methods for getting the state of vertical/horizontal edges or plaquettes.
	bool occup(int x, int y){
		return points[Lx*y + x];
	}
	bool v_edge(int x, int y){
		return v_edges[Lx*y + x];
	}
	bool h_edge(int x, int y){
		return h_edges[Lx*y + x];
	}
	bool plqt(int x, int y){
		return plqts[Lx*y + x];
	}

	//Methods for flipping the state of the vertical/horizontal edges or plaquettes.

	void flip_v_edge(int x, int y){
		v_edges[Lx*y + x] = !v_edges[Lx*y + x];
	}
	void flip_h_edge(int x, int y){
		h_edges[Lx*y + x] = !h_edges[Lx*y + x];
	}
	void flip_plqt(int x, int y){
		plqts[Lx*y + x] = !plqts[Lx*y + x];
	}

	//Methods for writing the state of the lattice in a file
	
	void write(string name){
		ofstream wrt_file(name);
		wrt_file<<"Lattice_configuration"<<endl;
		wrt_file<<"Lx= "<<Lx<<endl;
		wrt_file<<"Ly= "<<Ly<<endl;

		wrt_file<<"Vertical_edges_states:"<<endl;
		for(int i =0; i<Lx; i++){
			for(int j=0; j<Ly; j++){
				wrt_file<<v_edges[Lx*j + i]<<" ";
			}
			wrt_file<<endl;
		}

		wrt_file<<"Horizontal_edges_states:"<<endl;
		for(int i =0; i<Lx; i++){
			for(int j=0; j<Ly; j++){
				wrt_file<<h_edges[Lx*j + i]<<" ";
			}
			wrt_file<<endl;
		}

		wrt_file<<"Plaquettes_states:"<<endl;
		for(int i =0; i<Lx; i++){
			for(int j=0; j<Ly; j++){
				wrt_file<<plqts[Lx*j + i]<<" ";
			}
			wrt_file<<endl;
		}
	}

	//Methods for reading the state of the lattice from a file
	
	void read(string name){
		ifstream read_file(name);
		string junk; // to remove the words 
					 //
		read_file>>junk;
		read_file>>junk;
		read_file>>Lx;

		read_file>>junk;
		read_file>>Ly;
		cout<<Lx<<Ly<<endl;
	
		bool* h_edges_temp = (bool*) malloc(Lx*Ly*sizeof(bool));
		bool* v_edges_temp = (bool*) malloc(Lx*Ly*sizeof(bool));
		bool* plqts_temp = (bool*) malloc(Lx*Ly*sizeof(bool));
		free(h_edges); 
		free(v_edges);
		free(plqts);
		h_edges = h_edges_temp;
		v_edges = v_edges_temp;
		plqts = plqts_temp;
	

		read_file>>junk;
		for(int i = 0; i<Lx*Ly; i++){
			read_file>>v_edges[i];
			cout<<v_edges[i];
		}
		

		read_file>>junk;
		for(int i = 0; i<Lx*Ly; i++){
			read_file>>h_edges[i];
			cout<<h_edges[i];
		}

		read_file>>junk;
		for(int i = 0; i<Lx*Ly; i++){
			read_file>>plqts[i];
			cout<<plqts[i];
		}
	}

};
	
int main(){
	lattice x(50,50); 
	x.write("x.lat");
	/*
	cout<<x.v_edge(1,1)<<endl;
	cout<<x.h_edge(0,0)<<endl;
	cout<<x.plqt(0,1)<<endl;
	cout<<x.plqt(1,0)<<endl;
	*/
	return 0; 
}	

