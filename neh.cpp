#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

/*
optymalizacja polega na zmianie liczenia cmax
*/

#include "tools.h"

using namespace std;

int main(){
	string filename = "neh.data.txt";
	vector<vector<vector<unsigned> > > database;//wektor z pakietami zadan
	vector<vector<vector<unsigned> > > database_after_sort;//wektor z pakietami zadan po sortowaniu
	vector<vector<vector<unsigned> > > database_cell_time_left;//wektor z pakietami cmax
	//vector<vector<vector<unsigned> > > database_cell_time_right;//wektor z pakietami cmax
	
	tools::load(database, filename);
	
	for(unsigned i = 0; i<1/*database.size()*/; ++i){
		
		//posortowane po najdluzszym czasie t1
		priority_queue <vector<unsigned>, vector<vector<unsigned> >, tools::compare_time> data_pack_queue;
		for (unsigned j=0; j<database[i].size(); ++j) {
			data_pack_queue.push(database[i][j]);
		}
		
		
		
		vector<vector<unsigned> > data_pack;
		data_pack.insert(data_pack.begin(), data_pack_queue.top());
		data_pack_queue.pop();
		
		for (unsigned i=0, time=0; data_pack_queue.size(); ++i){
			data_pack.insert(data_pack.begin(), data_pack_queue.top());
			data_pack_queue.pop();
			time = tools::c_max(data_pack);
			unsigned temp_time=0;
			unsigned temp_index=0;
			
			
			for (unsigned j=1; j<data_pack.size(); ++j){
				data_pack[j-1].swap(data_pack[j]);
				
				temp_time = tools::c_max(data_pack);
			
				if (time > temp_time) {
					temp_index = j;
				}
				
				cout << endl;//dla sprawdzenia
		 	}
		}
		
	}
	
	
	tools::save(database_after_sort);
	
	tools::pause();	
	return 0;
}
