#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <iostream>
#include <vector>

namespace tools {

	//PAUSE *********************************************
	const void pause() {
		do {
			std::cout << "\n" << "Press the Enter key to continue.";
		} while (std::cin.get() != '\n');
	}

	//LOAD *********************************************
	const int load(unsigned& zad_length, std::vector< std::vector<int> > &zad) {
		std::ifstream file;
		file.open("dane.txt", std::ios::in);
		
		if (file.fail()) {
			std::cerr << "File didn't open properly within tools::load()";
			return 1;
		}
		
		if (file.is_open()) {
    		//! to do optymalizacji
    		unsigned counter = 1;
    		unsigned r, p, q;
			file >> zad_length;
			
			while (counter <= zad_length) {
				std::vector<int> temp;
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
    	
		std::cerr << "Unidentified error within tools::load()";
		return -1;
	}
	
	const int save(std::vector< std::vector<int> > const &zad) {
		std::ofstream file;
		file.open("posortowane.txt", std::ios::out);
	
		if (file.fail()) {
			std::cerr << "File didn't open properly within tools::save()";
			return 1;
		}
	
		if (file.is_open()) {
		
			for (int i=0; i < zad.size(); ++i){
				for (int j=1; j < zad[1].size(); ++j){
					file << zad[i][j];
					file << ' ';
				}
				file << std::endl;
			}
		return 0;
		}
		
		std::cerr << "Unidentified error within tools::save()";
		return -1;
	}
	
	//C_MAX *********************************************
	const int c_max(unsigned& const zad_length, std::vector< std::vector<int> > const &zad) {
		
		
		return 0;
	}
	
}

#endif //TOOLS_H_INCLUDED
