#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "tools.h"

using namespace std;

int main(){
	string filename = "neh.data.txt";
	vector<vector<vector<unsigned> > > database;//wektor z pakietami zadan
	vector<vector<vector<unsigned> > > database_after_sort;//wektor z pakietami zadan po sortowaniu
	vector<vector<vector<unsigned> > > database_cell_time_left;//wektor z pakietami cmax
	vector<vector<vector<unsigned> > > database_cell_time_right;//wektor z pakietami cmax
	
	tools::load(database, filename);
	
	for(unsigned i = 0; i<database.size(); ++i){
		//kolejka priorytetowa do napisania zamiast tego ponizej
 	    vector<vector<unsigned> > data_pack = database[i];//wektor z zadaniami
		vector<vector<unsigned> > data_pack_cell_time_left;//graf z czasami od lewej do prawej
		vector<vector<unsigned> > data_pack_cell_time_right;//graf z czasami od prawej do lewej
		
		//pierwsza kolumna grafu l-p
		vector<unsigned> first_column_time_left;
		//liczenie czasu wykonania pierwszej kolumny
		first_column_time_left.push_back(data_pack[0][1]);
		for(unsigned i = 1; i<data_pack[0].size(); ++i) {
		first_column_time_left.push_back(data_pack[0][i]+first_column_time_left[i-1]);
	    }
		data_pack_cell_time_left.push_back(first_column_time_left);
		
		//pierwsza kolumna grafu p-l
		
		database_after_sort.push_back(data_pack);
		database_cell_time_left.push_back(data_pack_cell_time_left);
		database_cell_time_right.push_back(data_pack_cell_time_right);
	}
	
	
	tools::save(database_after_sort);
	
	tools::pause();	
	return 0;
}
