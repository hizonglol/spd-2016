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
	unsigned zad1_length;
	string wejscie;
	wejscie = "dane.txt";

	tools::load(zad1_length, zad1, wejscie);
	tools::schrage(zad1_length, zad1);
	cout << "Czas calkowity po sortowaniu Schrage'a 2: " << tools::c_max(zad1_length, zad1) << endl;
	//	cout << "Czas Carliera: " << tools::sort_carlier(zad1_length, zad1, sorted) << endl;

	tools::save(zad1);
	tools::clean(zad1_length, zad1);
	
	tools::pause();
	return 0;
}
