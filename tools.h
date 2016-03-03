#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

namespace tools {

	//PAUSE *********************************************
	const void pause() {
		do std::cout << std::endl << std::endl << "Press the Enter key to continue...";
		while (std::cin.get() != '\n');
	}

	//LOAD *********************************************
	const short load(unsigned& zad_length, std::vector<std::vector<unsigned> >& zad, std::string wejscie) {
		std::ifstream file;
		file.open(wejscie.c_str(), std::ios::in);
		
		if (file.fail()) {
			std::cerr << std::endl << "File didn't open properly within tools::load()";
			return 1;
		}
		
		if (file.is_open()) {
    		//! to do optymalizacji
    		unsigned counter = 1;
    		unsigned r, p, q;
			file >> zad_length;
			
			while (counter <= zad_length) {
				std::vector<unsigned> temp;
				file >> r;
				file >> p;
				file >> q;
				temp.push_back(counter);
				temp.push_back(r);
				temp.push_back(p);
				temp.push_back(q);
				zad.push_back(temp);
				++counter;
			}
			
			file.close();
		
   		return 0;
    	}
    	
		std::cerr << std::endl << "Unidentified error within tools::load()";
		return -1;
	}

	//SAVE *********************************************
	const short save(std::vector< std::vector<unsigned> > const& zad) {
		std::ofstream file;
		file.open("posortowane.txt", std::ios::out);
	
		if (file.fail()) {
			std::cerr << std::endl << "File didn't open properly within tools::save()";
			return 1;
		}
	
		if (file.is_open()) {
			for (unsigned i=0; i < zad.size(); ++i){
				for (unsigned j=1; j < zad[i].size(); ++j){
					file << zad[i][j];
					file << ' ';
				}
				file << std::endl;
			}
		
		return 0;
		}
		
		
		std::cerr << std::endl << "Unidentified error within tools::save()";
		return -1;
	}
	
	const short print(std::vector< std::vector<unsigned> > const& zad) {

		for (unsigned i=0; i < zad.size(); ++i){
			std::cout << zad[i][0];
			std::cout << ' ';
		}
		std::cout << std::endl;
		
		return 0;
	}

	//CLEAN *********************************************
	const short clean(unsigned& zad_length, std::vector< std::vector<unsigned> >& zad) {
		
		for (unsigned i=0; i < zad_length; ++i) {
			zad[i].clear();
		}
		zad.clear();
		zad_length = 0;
		
		if(zad.empty() && zad_length == 0) return 0;
		else {
			std::cerr << std::endl << "Vector is not empty within tools::clean()";
			return 1;
		}
		
		std::cerr << std::endl << "Unidentified error within tools::clean()";
		return -1;
	}
	
	//C_MAX *********************************************
    // funkcja zaraca calkowity czas dzialania dla podanego wektora
	long c_max(unsigned const& zad_length, std::vector< std::vector<unsigned> > const& zad) {
		
	// musialem zmienic typ c_max i t_p do uzycia w funkcji max()	
	// edit: juz poprawione : 3
		unsigned long c_max = 0;
		unsigned long t_p = 0;
		unsigned i;
	
	// liczy zgodnie z danymi na stronie
		for (i=0; i < zad.size(); ++i) {
			t_p = std::max<unsigned long>(t_p,zad[i][1]) + zad[i][2];
			c_max = std::max<unsigned long>(t_p + zad[i][3], c_max);
		}
		
		if (i-- == zad.size() ) return c_max;
		else {
			std::cerr << std::endl << "Vector was not fully checked within c_max()";
			return -2;
		}
		
		std::cerr << std::endl << "Unidentified error within tools::c_max()";
		return -1;
	}
	
	struct compare1 {
        bool operator()(std::vector<unsigned> const& t1, std::vector<unsigned> const& t2) {
           	return t1[4] < t2[4];
        }
   	};
   	
   	struct compare2 {
   		bool operator()(std::vector<unsigned> const& t1, std::vector<unsigned> const& t2) {
           	return t1[1] < t2[1];
        }
	};
	
	struct compare3 {
   		bool operator()(std::vector<unsigned> const& t1, std::vector<unsigned> const& t2) {
           	return (t1[1]+t1[3]) < (t2[1]+t2[3]);
        }
	};
	
	int sort_1(std::vector< std::vector<unsigned> > & zad) {
		
		for (unsigned i=0; i < zad.size(); ++i) {
			zad[i].push_back(zad[i][1]-zad[i][3]);
		}
		
		std::sort(zad.begin(), zad.end(), compare1());
		
		return -1;
	}
	
	int sort_2(std::vector< std::vector<unsigned> > & zad) {
		
		std::sort(zad.begin(), zad.end(), compare2());
		
		return -1;
	}
	
	int sort_3(std::vector< std::vector<unsigned> > & zad) {
		
		std::sort(zad.begin(), zad.end(), compare3());
		
		return -1;
	}
	
	int sort_schrage (unsigned const& zad_length, std::vector< std::vector<unsigned> > & to_sort, std::vector< std::vector<unsigned> > & sorted) {
		
		// sorted - wektor posortowany (wynikowy)
		std::vector< std::vector<unsigned> > temp; // wektor tymczasowy z zadaniami gotowymi do rozpoczecia
		int i = 1;
		int t = 0;
		int c_max = 0;
		int q_max = 0;
		int q_max_position = 0;
		sort_2(to_sort); //sortowanie wektora wejsciowego wzgledem czasu r

		while (!to_sort.empty() || !temp.empty()) {
			for (int j = 0; j < to_sort.size(); ++j) {
				if (to_sort[j][1] <= c_max){
					temp.push_back(to_sort[j]);
					to_sort.erase(to_sort.begin() + j);
					j--;
				}
			}

			if (temp.empty()) {
				temp.push_back(to_sort[0]);
				to_sort.erase(to_sort.begin());
			}
			
			std::cout << "Dlugosc wektora temp: " << temp.size() << std::endl;
			std::cout << "Dlugosc wektora to_sort: " << to_sort.size() << std::endl;
			
			/* Przeszukiwanie wektora temp w celu znalezienia zadania z najdluzszym czasem q  */
			q_max = 0; // najwiekszy czas q
			q_max_position = 0; // pozycja zadania z najwiekszym czasem q
			
			for (int j = 0; j < temp.size(); ++j) {
				if (temp[j][3] > q_max){
				q_max = temp[j][3];
				q_max_position = j;
				}
			}
			
			c_max = c_max + temp[q_max_position][2]; // zwiekszenie czasu
			sorted.push_back(temp[q_max_position]); // wlozenie zadania do wektora posortowanego
			temp.erase(temp.begin() + q_max_position); // zadanie przestaje miec status "gotowe"		
			
		}
		return 0;
	}
	
	
	/* SHRAGE PRZEPISANY */
	struct compare_r {
        bool operator()(std::vector<unsigned> const& t1, std::vector<unsigned> const& t2) {
           	return t1[1] < t2[1];
        }
   	};
   	
	struct compare_q {
        bool operator()(std::vector<unsigned> const& t1, std::vector<unsigned> const& t2) {
           	return t1[3] > t2[3];
        }
   	};
	
	int sort_schrage2 (unsigned const& zad_length, std::vector< std::vector<unsigned> > & to_sort, std::vector< std::vector<unsigned> > & sorted) {
		int t = 0;
		int k = 0;
		int c_max = 0;
		std::vector<std::vector<unsigned> > pi;
		
		std::priority_queue <std::vector<unsigned>, std::vector< std::vector<unsigned> >, compare_r> N;
		std::priority_queue <std::vector<unsigned>, std::vector< std::vector<unsigned> >, compare_q> G;
		
		while (sorted.size()) {
			N.push(sorted.back());
			sorted.pop_back();
		}
		
		while (G.size() || N.size()) {
			
			while (N.size() && N.top()[1] < t) {
				G.push(N.top());
				N.pop();
			}
			
			do {
			   	t = N.top()[1];
			   	
				while (N.size() && N.top()[1] < t) {
					G.push(N.top());
					N.pop();
				}
			} while (!G.size());
			
			k = k + 1;
			t = t + G.top()[2];
			c_max = std::max<int>(c_max, t + G.top()[3]);
			pi.push_back(G.top());
			G.pop();
		}
		

		sorted = pi;
	
		return 0;	
	}
	
}

#endif //TOOLS_H_INCLUDED
