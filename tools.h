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

	
	/* komparatory do Schrage */
	struct compare_r {
        bool operator()(std::vector<unsigned> const& t1, std::vector<unsigned> const& t2) {
           	return t1[1] > t2[1];
        }
   	};
   	
	struct compare_q {
        bool operator()(std::vector<unsigned> const& t1, std::vector<unsigned> const& t2) {
           	return t1[3] < t2[3];
        }
   	};
	
	/* schrage zmieniajacy sorted i zwracajacy czas */
	int schrage (unsigned const& zad_length, std::vector< std::vector<unsigned> > & sorted) {
		int t = 0;
		int k = 0;
		int c_max = 0;
		std::vector<std::vector<unsigned> > pi;
		
		std::priority_queue <std::vector<unsigned>, std::vector< std::vector<unsigned> >, compare_r> N;
		std::priority_queue <std::vector<unsigned>, std::vector< std::vector<unsigned> >, compare_q> G;
		
		while (!sorted.empty()) {
			N.push(sorted.back());
			sorted.pop_back();
		}
		
		while ((!G.empty()) || (!N.empty())) {
			
			while ((!N.empty()) && (N.top()[1] <= t)) {
				G.push(N.top());
				N.pop();
			}
			
			if (G.empty()) {
				t = N.top()[1];
			}
			else {
			t = t + G.top()[2];
			c_max = std::max<int>(c_max, t + G.top()[3]);
			pi.push_back(G.top());
			G.pop();
			}
		}
		
		sorted = pi;
	
		return tools::c_max(zad_length, sorted);
	}
	
	/* schrage zwracajacy czas *///*********************************************************
	int preschrage (unsigned const& zad_length, std::vector< std::vector<unsigned> > const& sorted) {
		int t = 0;
		int k = 0;
		int c_max = 0;
		std::vector<std::vector<unsigned> > pi;
		
		std::priority_queue <std::vector<unsigned>, std::vector< std::vector<unsigned> >, compare_r> N;
		std::priority_queue <std::vector<unsigned>, std::vector< std::vector<unsigned> >, compare_q> G;
		
		while (!sorted.empty()) {
			N.push(sorted.back());
		}
		
		while ((!G.empty()) || (!N.empty())) {
			
			while ((!N.empty()) && (N.top()[1] <= t)) {
				G.push(N.top());
				N.pop();
			}
			

			if (G.empty()) {
				t = N.top()[1];
			}
			else {
			t = t + G.top()[2];
			c_max = std::max<int>(c_max, t + G.top()[3]);
			pi.push_back(G.top());
			G.pop();
			}
		}
	
		return tools::c_max(zad_length, pi);
	}
	
	/* carlier *///**************************************************************************
	int sort_carlier(unsigned const& zad_length, std::vector< std::vector<unsigned> > & sorted, int& UB){
		long int U, LB;
		int n;
		int temp_r;
		int temp_q;
		n = zad_length;
		std::vector<std::vector<unsigned> > pi;
		
		//1
		U = schrage(zad_length, sorted);
		//2
		if(U < UB){
			UB = U;
			pi = sorted;
		}
		//3
		
		//4
		if (/* c nie istnieje*/) return 0;
		//5
		
		//6
		// temp_r = c[1];
		// tymczasowa modyfikacja czasu przygotowania w zadaniu c
		// c[1] = std::max(c[1], r_prim + p_prim);
		//7
		LB = preschrage(zad_length, sorted);
		
		//8
		if (LB < UB) ;
		//9
		carlier(zad_length, sorted, UB);
		//10
		// przywracany oryginalny czas przygotowania w zadaniu c
		// c[1] = temp_r;
		
		//11
		// temp_q = c[3];
		// tymczasowa modyfikacja czasu stygniecia w zadaniu c
		// c[3] = std::max(c[3], q_prim + p_prim);
		//12
		LB = preshrage(zad_length, sorted);
		//13
		if (LB < UB) ;
		//14
		carlier(zad_length, sorted, UB);
		//15
		//przywracany oryginalny czas stygniecia w zadaniu c
		// c[3] = temp_q;
		return U;
		
		
		return -1;
	}
}

#endif //TOOLS_H_INCLUDED
