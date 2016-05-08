#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "tools.h"

using namespace std;

int main() {
	std::priority_queue <std::vector<unsigned>, std::vector< std::vector<unsigned> >, tools::compare_r> N;
	string wejscie1 = "dane1.txt";
	string wyjscie1 = "out1.txt";
	unsigned suma;

	tools::load(N, wejscie1);
	suma = tools::schrage(N);
	//suma = tools::schrage_interrupt(N);
	//cout << "Czas Schrage dla danych 1: " << suma << endl;
	//tools::print(zad4);
	
	cout << "Czas: " << suma << endl;
    
	return 0;
}
