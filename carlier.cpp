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
1. 13862
2. 20917
3. 31343
4. 33878
*/

int main() {
	vector<vector<unsigned> > zad1;
	vector<vector<unsigned> > zad2;
	vector<vector<unsigned> > zad3;
	vector<vector<unsigned> > zad4;
	unsigned zad1_length;
	unsigned zad2_length;
	unsigned zad3_length;
	unsigned zad4_length;
	string wejscie1 = "dane1.txt";
	string wejscie2 = "dane2.txt";
	string wejscie3 = "dane3.txt";
	string wejscie4 = "dane4.txt";
	//unsigned U1 = 255565;
	//unsigned U2, U3, U4;
	//U4 = U3 = U2 = U1;
	unsigned suma, suma1, suma2, suma3, suma4;

	tools::load(zad1_length, zad1, wejscie1);
	suma1 = tools::sort_data2(zad1_length, zad1);
	cout << "Czas Carliera dla danych 1: " << suma1 << endl;
	
	tools::load(zad2_length, zad2, wejscie2);
	suma2 = tools::sort_data2(zad2_length, zad2);
	cout << "Czas Carliera dla danych 2: " << suma2 << endl;
	tools::print(zad2);
	
	tools::load(zad3_length, zad3, wejscie3);
	suma3 = tools::sort_data2(zad3_length, zad3);
	cout << "Czas Carliera dla danych 3: " << suma3 << endl;
	tools::print(zad3);
	
	tools::load(zad4_length, zad4, wejscie4);
	suma4 = tools::sort_data2(zad4_length, zad4);
	cout << "Czas Carliera dla danych 4: " << suma4 << endl;
	tools::print(zad4);

	suma = suma1 + suma2 + suma3 + suma4;
	cout << "Suma czasow: " << suma << endl;

	//tools::save(zad2); //zapisujemy do pliku permutacje zadan
	//tools::clean(zad2_length, zad2); //sprzatamy wektory
	
	tools::pause();
	return 0;
}
