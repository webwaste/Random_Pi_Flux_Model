#include"matrix.h"

int main(){
	int x=3; 
	bool* arr = (bool*) malloc(x*sizeof(bool));
	arr[0] = true;
	arr[1] = false;
	arr[2] = false;
	ofstream out("y.test");
	out<<arr[0]<<endl;
	return 0; 
}
