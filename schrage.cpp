#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "tools.h"

using namespace std;

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
	string wyjscie1 = "out1.txt";
	string wyjscie2 = "out2.txt";
	string wyjscie3 = "out3.txt";
	string wyjscie4 = "out4.txt";
	unsigned suma, suma1, suma2, suma3, suma4;

	tools::load(zad1_length, zad1, wejscie1);
	suma1 = tools::better_schrage(zad1_length, zad1);
	cout << "Czas Schrage dla danych 1: " << suma1 << endl;
	
	tools::load(zad2_length, zad2, wejscie2);
	suma2 = tools::better_schrage(zad2_length, zad2);
	cout << "Czas Schrage dla danych 2: " << suma2 << endl;
	tools::print(zad2);
	
	tools::load(zad3_length, zad3, wejscie3);
	suma3 = tools::better_schrage(zad3_length, zad3);
	cout << "Czas Schrage dla danych 3: " << suma3 << endl;
	tools::print(zad3);
	
	tools::load(zad4_length, zad4, wejscie4);
	suma4 = tools::better_schrage(zad4_length, zad4);
	cout << "Czas Schrage dla danych 4: " << suma4 << endl;
	tools::print(zad4);

	suma = suma1 + suma2 + suma3 + suma4;
	cout << "Suma czasow: " << suma << endl;

	tools::save(zad1, wyjscie1);
	tools::save(zad2, wyjscie2);
    tools::save(zad3, wyjscie3);
    tools::save(zad4, wyjscie4);
    tools::save_time(suma1, suma2, suma3, suma4, suma);
    
	return 0;
}
