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
	vector<vector<vector<unsigned> > > database_after_sort;//wektor z pakietami zadan po sortowaniu
	vector<vector<vector<unsigned> > > database_cell_time_left;//wektor z pakietami cmax
	vector<vector<vector<unsigned> > > database_cell_time_right;//wektor z pakietami cmax
	
	tools::load(database, indexes, filename);
	
	for(unsigned i = 0; i<database.size(); ++i){
	
		//posortowane po najdluzszym czasie t1
		priority_queue <vector<unsigned>, vector<vector<unsigned> >, tools::compare_time> data_pack_queue;
		for (unsigned j=0; j<database[i].size(); ++j) {
			data_pack_queue.push(database[i][j]);
		}
		//ilosc zadan
		const unsigned m = indexes[i][0];
		//wymiarowosc zadan
		const unsigned n = indexes[i][1];
		//paczka z zadaniami
		vector<vector<unsigned> > data_pack;
		vector<vector<unsigned> > data_temp;
		
		//graf z czasami od lewej do prawej
		unsigned ** data_pack_time_left = new unsigned *[m];
		for(unsigned i=0; i<m; ++i) data_pack_time_left[i] = new unsigned [n];
		//graf z czasami od prawej do lewej
		unsigned ** data_pack_time_right = new unsigned *[m];
		for(unsigned i=0; i<m; ++i) data_pack_time_right[i] = new unsigned [n];
		
		data_pack.insert(data_pack.begin(), data_pack_queue.top());
		data_temp.insert(data_temp.begin(), data_pack_queue.top());
		data_pack_queue.pop();
//		cout << "Wybrane zadanie " << data_temp[0][0] << endl;
		
//		inicjalizacja grafu z czasami od lewej do prawej
		for(unsigned i=0, temp=0; i<n; ++i){
			data_pack_time_left[0][i] = temp += data_pack[0][i+1];
		}
//		inicjalizacja grafu z czasami od prawej do lewej
		for(unsigned i=0, temp=0; i<n; ++i){
			data_pack_time_right[0][i] = temp += data_pack[0][n-i-1];
		}
		
		//tutaj to se sprawdz
		tools::c_max_left(data_pack, data_pack_time_left, 0, n);
		tools::c_max_right(data_pack, data_pack_time_right, 0, n);

		for (unsigned i=0; data_pack_queue.size(); ++i){
			data_temp[0] = data_pack_queue.top();
			data_pack_queue.pop();
//			cout << "Wybrane zadanie " << data_temp[0][0] << endl;
//			time = tools::c_max(data_pack);
			unsigned temp_time=0;
			unsigned temp_index=0;
			unsigned var;
			unsigned time = 999999;
			
			for (unsigned j=0; j<=data_pack.size(); ++j){
				var = 0;
				temp_time = 0;
				if(j==0){
//					var = data_temp[0][1];
//					temp_time = data_pack_time_right[data_pack.size()-1][n-1] + var;
					for(unsigned k=0; k<n; ++k){
						var += data_temp[0][k+1];
						temp_time = std::max(data_pack_time_right[data_pack.size()-1][n-1-k] + var, temp_time);
					}
				}
				else if(j==data_pack.size()){
//					var = data_temp[0][n];
//					temp_time = data_pack_time_left[data_pack.size()-1][n-1] + var;
					for(unsigned k=0; k<n; ++k){
						var += data_temp[0][n-k];
						temp_time = std::max(data_pack_time_left[data_pack.size()-1][n-1-k] + var, temp_time);
					}
				}			
				else{
					var = data_pack_time_left[j-1][0] + data_temp[0][1];
//					cout << data_pack_time_left[j-1][0] << "  " << var << "  " << data_pack_time_right[data_pack.size()-1-j][n-1] << endl;
					temp_time = var + data_pack_time_right[data_pack.size()-1-j][n-1];
					for(unsigned k=1; k<n; ++k){
						var = std::max(data_pack_time_left[j-1][k], var) + data_temp[0][k+1];
//						cout << data_pack_time_left[j-1][k] << "  " << var << "  " << data_pack_time_right[data_pack.size()-1-j][n-1-k] << endl;
						temp_time = std::max(var + data_pack_time_right[data_pack.size()-1-j][n-1-k], temp_time);
					}
				}

//				cout << "Czas wstawienia na " << j << " to " << temp_time << endl;
				if (temp_time < time) {
					temp_index = j;
					time = temp_time;
				}
//				cout << "Czas najmniejszy " << time << endl;
		 	}
		 	
		 	data_pack.insert(data_pack.begin()+temp_index, data_temp[0]);
		 	tools::c_max_left(data_pack, data_pack_time_left, temp_index, n);
			tools::c_max_right(data_pack, data_pack_time_right, data_pack.size()-1-temp_index, n);
			
//			cout << "Indeksy zadan \n";
//			for(i=0; i<data_pack.size(); ++i){
//				cout << data_pack[i][0] << " ";
//			}
//			cout << endl << endl;
		}
		
		c_max = tools::c_max(data_pack);
		cout << "Dane nr " << i << endl;
		cout << "Czas " << (tools::c_max(data_pack)) << endl << endl;
	}
	
	cout << "Skonczylem" << endl;
//	tools::save(database_after_sort);
	
//	tools::pause();	
	return 0;
}
