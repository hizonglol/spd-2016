#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

#include "tools.h"

using namespace std;

int main(){
	string filename = "neh.data.txt";
	vector<vector<vector<unsigned> > > database;//wektor z pakietami zadan
	vector<vector<vector<unsigned> > > database_after_sort;//wektor z pakietami zadan po sortowaniu
	vector<vector<vector<unsigned> > > database_cell_time_left;//wektor z pakietami cmax
	vector<vector<vector<unsigned> > > database_cell_time_right;//wektor z pakietami cmax
	
	tools::load(database, filename);
	
	for(unsigned i = 0; i<1/*database.size()*/; ++i){
		
		//posortowane po najdluzszym czasie t1
		priority_queue <vector<unsigned>, vector<vector<unsigned> >, tools::compare_time> data_pack_queue;
		for (unsigned j=0; j<database[i].size(); ++j) {
			data_pack_queue.push(database[i][j]);
		}
		
		vector<vector<unsigned> > data_pack;//do tego wpisujemy zadania ktore na koniec bedac posortowane zwracamy
		vector<vector<unsigned> > data_pack_cell_time_left;//graf z czasami od lewej do prawej
		vector<vector<unsigned> > data_pack_cell_time_right;//graf z czasami od prawej do lewej
		
		data_pack.push_back(data_pack_queue.top());//wrzucamy element z najdluzszym czasem do koleji
		data_pack_queue.pop();//usuwamy go z kolejki
		
		//pierwsza kolumna grafu l-p
		vector<unsigned> first_column_time_left;
		//liczenie czasu wykonania pierwszej kolumny
		first_column_time_left.push_back(data_pack[0][1]);
		for(unsigned k = 2; k<data_pack[0].size(); ++k) {//2 dlatego bo na 0 mamy indeks, a na 1 juz zostalo policzone
		    first_column_time_left.push_back(first_column_time_left[k-2]+data_pack[0][k]);
	    }
		data_pack_cell_time_left.push_back(first_column_time_left);
		
		//dla sprawdzenia pierwszej kolumny
		cout<<first_column_time_left[0] << endl;
		cout<<first_column_time_left[1] << endl;
		cout<<first_column_time_left[2];
		
		//pierwsza kolumna grafu p-l
		//...
		
		database_after_sort.emplace_back(data_pack);
		database_cell_time_left.push_back(data_pack_cell_time_left);
		database_cell_time_right.push_back(data_pack_cell_time_right);
	}
	
	
	tools::save(database_after_sort);
	
	tools::pause();	
	return 0;
}
