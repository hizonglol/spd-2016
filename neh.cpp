#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include "tools.h"

using namespace std;

int main(){
	string filename = "neh.data.txt";//nazwa pliku wejsciowego
	vector<vector<vector<unsigned> > > database;//wektor z pakietami zadan
	vector<vector<unsigned> > indexes;//wektor z iloscia i wymiarowoscia zadan
	//vector<vector<vector<unsigned> > > database_after_sort;//wektor z pakietami zadan po sortowaniu
	vector<vector<vector<unsigned> > > database_cell_time_left;//wektor z pakietami cmax
	vector<vector<vector<unsigned> > > database_cell_time_right;//wektor z pakietami cmax
	
	tools::load(database, indexes, filename);
	
	string out_file = "wyniki.txt";
	std::ofstream file;
	file.open(out_file, std::ios::out);
	
	unsigned a, b, temp;
	unsigned i, j, k;
	unsigned temp_time, temp_index, var, time, data_pack_size;
	
	for(a = 0; a<database.size(); ++a){
	
		//posortowane po najdluzszym czasie t1
		priority_queue <vector<unsigned>, vector<vector<unsigned> >, tools::compare_time> data_pack_queue;
		for (b=0; b<database[a].size(); ++b) {
			data_pack_queue.push(database[a][b]);
		}
		//ilosc zadan
		const unsigned m = indexes[a][0];
		//wymiarowosc zadan
		const unsigned n = indexes[a][1];
		//paczka z zadaniami
		vector<vector<unsigned> > data_pack;
		vector<vector<unsigned> > data_temp;
		
		//graf z czasami od lewej do prawej
		unsigned ** data_pack_time_left = new unsigned *[m];
		for(b=0; b<m; ++b) data_pack_time_left[b] = new unsigned [n];
		//graf z czasami od prawej do lewej
		unsigned ** data_pack_time_right = new unsigned *[m];
		for(b=0; b<m; ++b) data_pack_time_right[b] = new unsigned [n];
		
		data_pack.insert(data_pack.begin(), data_pack_queue.top());
		data_temp.insert(data_temp.begin(), data_pack_queue.top());
		data_pack_queue.pop();
		
		//inicjalizacja grafu z czasami od lewej do prawej
		for(b=0, temp=0; b<n; ++b){
			data_pack_time_left[0][b] = temp += data_pack[0][b+1];
		}
		//inicjalizacja grafu z czasami od prawej do lewej
		for(b=0, temp=0; b<n; ++b){
			data_pack_time_right[0][b] = temp += data_pack[0][n-b-1];
		}

		for (i=0; data_pack_queue.size(); ++i){
			data_temp[0] = data_pack_queue.top();
			data_pack_queue.pop();
			temp_time=0;
			temp_index=0;
			time = 999999;
			data_pack_size = data_pack.size();
			
			for (j=0; j<=data_pack_size; ++j){
				var = 0;
				temp_time = 0;
				
				if (j==0){
					for (k=0; k<n; ++k){
						var += data_temp[0][k+1];
						temp_time = std::max(data_pack_time_right[data_pack_size-1][n-1-k] + var, temp_time);
					}
				}
				else if (j==data_pack_size){
					for (k=0; k<n; ++k){
						var += data_temp[0][n-k];
						temp_time = std::max(data_pack_time_left[data_pack_size-1][n-1-k] + var, temp_time);
					}
				}			
				else{
					var = data_pack_time_left[j-1][0] + data_temp[0][1];
					temp_time = var + data_pack_time_right[data_pack_size-1-j][n-1];
					for (k=1; k<n; ++k){
						var = std::max(data_pack_time_left[j-1][k], var) + data_temp[0][k+1];
						temp_time = std::max(var + data_pack_time_right[data_pack_size-1-j][n-1-k], temp_time);
					}
				}

				if (temp_time < time) {
					temp_index = j;
					time = temp_time;
				}
		 	}
		 	
		 	data_pack.insert(data_pack.begin()+temp_index, data_temp[0]);
		 	tools::c_max_left(data_pack, data_pack_time_left, temp_index, n);
			tools::c_max_right(data_pack, data_pack_time_right, data_pack.size()-1-temp_index, n);
		}
		
		//c_max = tools::c_max(data_pack);
		file << "Dane nr " << a << endl;
		file << "Czas " << (tools::c_max(data_pack)) << endl << endl;
	}
	
	//cout << "Koniec dzialania programu." << endl;
	file.close();
	
//	tools::save(database_after_sort);
	
//	tools::pause();	
	return 0;
}
