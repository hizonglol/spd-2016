#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "tools.h"

using namespace std;

int main(){
	string filename = "neh.data.txt";
	vector<vector<vector<unsigned> > > database;
	vector<unsigned> database_cmax;
	
	tools::load(database, filename);
	
	for(unsigned i = 0; i<database.size(); ++i){
 	    vector<vector<unsigned> > data_pack = database[i];
	
	}
	
	cout << database[0][0][0] << ' ' << database[0][0][1];
	
	tools::pause();	
	return 0;
}
