#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

namespace tools {

	//PAUSE *****************************************************************************************
	const void pause() {
		do std::cout << std::endl << std::endl << "Press the Enter key to continue...";
		while (std::cin.get() != '\n');
	}

	//LOAD ******************************************************************************************
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

	//SAVE ******************************************************************************************
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
	
	//PRINT *****************************************************************************************
	const short print(std::vector< std::vector<unsigned> > const& zad) {

		for (unsigned i=0; i < zad.size(); ++i){
			std::cout << zad[i][0];
			std::cout << ' ';
		}
		std::cout << std::endl;
		
		return 0;
	}

	//CLEAN *****************************************************************************************
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
	
	//C_MAX *****************************************************************************************
	long c_max(unsigned const& zad_length, std::vector< std::vector<unsigned> > const& zad) {
		
		unsigned long c_max = 0;
		unsigned long t_p = 0;
		unsigned i;
	
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

	
	/* komparatory do Schrage *///*******************************************************************
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
	
	/* schrage zmieniajacy sorted i zwracajacy czas *///*********************************************
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
	
	/* schrage zwracajacy czas *///******************************************************************
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
	
	//TO TRZEBA DOKONCZYC
	/* wyznaczanie a i b *///************************************************************************
	int set_a_b_index(unsigned const& n, std::vector<std::vector<unsigned> > const& pi, long int const& U, int & a_index, int & b_index){
		a_index = 0;
		b_index = 0;
		int j;
		int sum;
		
		int c_pi_temp = pi[1][1] + pi[1][2];
		
		for (j=(n-1); j>=0; --j){
			if ((c_pi_temp + pi[j][3]) <= U){
				// napisac jak zwieksza sie c_pi_temp
				b_index = j;
				break;
			}
		}
		
		// tutaj liczymy sume p od pi[0] do pi[b]
		for (j=0; j<n; ++j){
			sum -= pi[j][2];
			if (pi[j][1] + sum + pi[b_index][3] >= U) {
				a_index = j;
				break;
			}
		}
	}
	
	/* wyznaczanie c *///****************************************************************************
	bool c_not_exists(unsigned const& n, std::vector<std::vector<unsigned> > const& pi, int const& a_index, int const& b_index, int& c_index) {
		bool c_not_exists = true;
		
		for (int j=a_index; j<=b_index; ++j){
			if (pi[j][3] < pi[b_index][3]){
				c_not_exists = false;
				c_index = j;
			}
		}
		
		return c_not_exists;
	}
	
	/* carlier *///**********************************************************************************
	int sort_carlier(unsigned const& n, std::vector< std::vector<unsigned> > & sorted, int& UB){
		long int U, LB;
		int r_old, q_old;
		int r_prim, p_prim, q_prim;
		int a_index, b_index, c_index;
		
		std::vector<std::vector<unsigned> > pi;
		
		//1
		U = schrage(n, sorted);
		
		//2
		if(U < UB){
			UB = U;
			pi = sorted;
		}
		
		//pierwsza polowa 3
		set_a_b_index(n, pi, U, a_index, b_index);
		
		//4 i druga polowa 3
		if (c_not_exists(n, pi, a_index, b_index, c_index)) return 0;
		
		//5
		p_prim = 0;
		for (int i=(c_index+1); i<b_index; ++i) {
			if (pi[i][1] < r_prim) r_prim = pi[i][1];
			if (pi[i][3] < q_prim) q_prim = pi[i][3];
			p_prim += pi[i][2];
		}
		
		//6
		r_old = pi[c_index][1];
		pi[c_index][1] = std::max<int>(pi[c_index][1], r_prim+p_prim);
		
		//7
		LB = preschrage(n, sorted);
		
		//8
		if (LB < UB) /*9*/ sort_carlier(n, sorted, UB);
		
		//10
		pi[c_index][1] = r_old;
		
		//11
		q_old = pi[c_index][3];
		pi[c_index][3] = std::max<int>(pi[c_index][3], q_prim+p_prim);
		
		//12
		LB = preschrage(n, sorted);
		
		//13
		if (LB < UB) /*14*/ sort_carlier(n, sorted, UB);
		
		//15
		pi[c_index][3] = q_old;
		
		return -1;
	}
}

#endif //TOOLS_H_INCLUDED
