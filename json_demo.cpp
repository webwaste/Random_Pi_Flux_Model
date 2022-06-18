#include<string>
#include<iostream>
#include<fstream>
#include<json/json.h>

using namespace std;

int main(int argc, char* argv[])
{
	ifstream ifs("alice.json");
	Json::Reader reader;
  	Json::Value obj;
	reader.parse(ifs,obj);
	cout<<"Book: "<<obj["book"].asString()<<endl;

    return 0;
}
