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
	string wejscie1;
	string wejscie2;
	string wejscie3;
	string wejscie4;
	wejscie1 = "dane1.txt";
	wejscie2 = "dane2.txt";
	wejscie3 = "dane3.txt";
	wejscie4 = "dane4.txt";
	int U1 = 255565;
	int U2 = 255565;
	int U3 = 255565;
	int U4 = 255565;
	int suma;

	tools::load(zad1_length, zad1, wejscie1);
	//tools::schrage(zad1_length, zad1);
	//cout << "Czas calkowity po sortowaniu Schrage'a: " << tools::c_max(zad1_length, zad1) << endl;
	//tools::print(zad1);
	
	//tools::carlier(zad1_length, zad1, U1);
	//cout << "Czas Carliera dla danych 1: " << tools::c_max(zad1_length, zad1) << endl;
	
	cout << tools::preschrage(zad1_length,zad1) << endl;
	tools::print(zad1);
	
	/*
	tools::load(zad2_length, zad2, wejscie2);
	tools::carlier(zad1_length, zad1, U2);
	cout << "Czas Carliera dla danych 2: " << tools::c_max(zad2_length, zad2) << endl;
	tools::print(zad2);
	
	tools::load(zad3_length, zad3, wejscie3);
	tools::carlier(zad1_length, zad1, U3);
	cout << "Czas Carliera dla danych 3: " << tools::c_max(zad3_length, zad3) << endl;
	tools::print(zad3);
	
	tools::load(zad4_length, zad4, wejscie4);
	tools::carlier(zad1_length, zad1, U4);
	cout << "Czas Carliera dla danych 4: " << tools::c_max(zad4_length, zad4) << endl;
	tools::print(zad4);

	suma = tools::c_max(zad1_length, zad1) + tools::c_max(zad2_length, zad2) + tools::c_max(zad3_length, zad3) + tools::c_max(zad4_length, zad4);
	cout << "Suma czasow: " << suma << endl;
*/
	tools::save(zad1);
	tools::clean(zad1_length, zad1);
	
	tools::pause();
	return 0;
}
