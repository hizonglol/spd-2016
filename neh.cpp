#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <array>

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
	vector<vector<vector<unsigned> > > database_cell_time_right;//wektor z pakietami cmax
	
	tools::load(database, filename);
	
	for(unsigned i = 1; i<2/*database.size()*/; ++i){
	
		//posortowane po najdluzszym czasie t1
		priority_queue <vector<unsigned>, vector<vector<unsigned> >, tools::compare_time> data_pack_queue;
		for (unsigned j=0; j<database[i].size(); ++j) {
			data_pack_queue.push(database[i][j]);
		}
		
		vector<vector<unsigned> > data_pack;
		unsigned ** data_pack_time_left = new unsigned *[data_pack_queue.size()];
		for(unsigned i=0; i<data_pack_queue.top().size(); ++i) data_pack_time_left[i] = new unsigned [data_pack_queue.top().size()];
		unsigned ** data_pack_time_right = new unsigned *[data_pack_queue.size()];
		for(unsigned i=0; i<data_pack_queue.top().size(); ++i) data_pack_time_right[i] = new unsigned [data_pack_queue.top().size()];
		
		data_pack.insert(data_pack.begin(), data_pack_queue.top());
		data_pack_queue.pop();
		
		
		//dodatkowa tablica z rozmiarami m na n
		for(unsigned i=0, temp=0; i<data_pack[0].size()-1; ++i){
			data_pack_time_left[0][i] = temp += data_pack[0][i+1];
		}
		
		for(unsigned i=0, temp=0; i<data_pack[0].size()-1; ++i){
			data_pack_time_right[0][i] = temp += data_pack[0][data_pack[0].size()-i-1];
		}
		
		
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
		 	}
		 	data_pack.insert(data_pack.begin()+temp_index, data_pack[data_pack.size()-1]);
		 	data_pack.erase(data_pack.end());
		}
	}
	
	
	tools::save(database_after_sort);
	
	tools::pause();	
	return 0;
}
