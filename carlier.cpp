#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "tools.h"

using namespace std;

	
/* jak powinno wyjsc dla tych danych:
Schrage:
1. 13981   
2. 21529   
3. 31683   
4. 34444   

Carlier:
0. 228
1. 3026
2. 3665
3. 3309
4. 3191
*/


int main() {
	vector<vector<unsigned> > zad1;
	unsigned zad1_length;
	string wejscie1 = "dane0.txt";
	//string wejscie1 = "dane1.txt";
	//string wejscie1 = "dane2.txt";
	//string wejscie1 = "dane3.txt";
	//string wejscie1 = "dane4.txt";
	//string wejscie1 = "dane5.txt";
	//string wejscie1 = "dane6.txt";
	//string wejscie1 = "dane7.txt";
	//string wejscie1 = "dane8.txt";
	unsigned U1 = ~0u;

	tools::load(zad1_length, zad1, wejscie1);

	tools::carlier(zad1_length, zad1, U1);

	return 0;
}
