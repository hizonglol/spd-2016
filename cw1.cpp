#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "tools.h"

using namespace std;
/* zrodla do poczytania

http://dominik.zelazny.staff.iiar.pwr.wroc.pl/pliki/spd/zad1/Zadanie_1.pdf
algorytmy ze strony Smutnickiego:
http://czeslaw.smutnicki.staff.iiar.pwr.wroc.pl/sterowanie%20procesami%20dyskretnymi/rpq.cpp

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
	int U1 = 150000;
	int U2 = 150000;
	int U3 = 150000;
	int U4 = 150000;

	tools::load(zad1_length, zad1, wejscie1);
	//tools::schrage(zad1_length, zad1);
	//cout << "Czas calkowity po sortowaniu Schrage'a 2: " << tools::c_max(zad1_length, zad1) << endl;
	tools::carlier(zad1_length, zad1, U1);
	cout << "Czas Carliera: " << tools::c_max(zad1_length, zad1) << endl;

	tools::save(zad1);
	tools::clean(zad1_length, zad1);
	
	tools::pause();
	return 0;
}
