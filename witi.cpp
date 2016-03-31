#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "tools.h"

using namespace std;

int main(){
	int loop;
	string wejscie1 = "dane_a.txt";
	
	for(loop = 97; loop < 108; loop++){
		wejscie1[5] = loop;
		cout << "Wczytano " << wejscie1 << endl;
		
		unsigned long limit;
		unsigned c_max;
		int i, j, k, pen, index;
		int long min_kara;		
		
		/* wektor drugi zawiera zadania, ktore nie wygeneruja kary niezaleznie od pozycji */
		vector< vector<unsigned> > tasks, tasks1, tasks2;
		vector< long int > penalties;
		vector< long int > indeks;	
		tools::load(tasks.size(), tasks, wejscie1);
		
		/* ustalanie limitu czasowego wzgledem ktorego dzielone sa wektory */
		limit = tools::sum_time(tasks);
		
		/* dzielenie wektora na dwa */
		for(unsigned l = 0; l < tasks.size(); ++l){
			if(tasks[l][3] < limit) tasks1.push_back(tasks[l]);
			else tasks2.push_back(tasks[l]);
		}
		
		int r=1uL<<tasks1.size();
		penalties.resize(r);
		indeks.resize(r);
		penalties[0] = 0;
		indeks[0] = 0;
		
		/* algorytm szukajacy rozwiazania optymalnego po wektorze 1 */
		for (i = 1; i < r; ++i){
			min_kara = 999999;
			c_max = 0;
			c_max = tools::time(i, tasks1);
			for(j = 1,k = 1;j <= i;j<<=1){
				if(i&j){
					pen = penalties[i-j] + tools::i_penalty(c_max, tasks1, k-1);
					if(pen<min_kara){
						min_kara = pen;
						index = k;
					}
				}
				k++;
			}
			penalties[i] = min_kara;
			indeks[i] = index;
		}
		
		tools::swap_index(indeks,tasks1,tasks1.size());	
		tools::merge(tasks1,tasks2);
		tools::print(tasks1);

		cout << "Kara: " << penalties.back() << endl;
		cout << "Kara alternatywna: " << tools::sum_penalty(tasks1) << endl << endl;
		
		tools::clean(tasks1.size(),tasks1);
		tools::clean(tasks2.size(),tasks2);
		tools::clean(tasks.size(),tasks);
		penalties.clear();
		indeks.clear();
	}
	tools::pause();	
	return 0;
}
