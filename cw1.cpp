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
	vector<vector<unsigned> > sorted;
	unsigned zad1_length;
	string wejscie;
	wejscie = "dane2.txt";

	tools::load(zad1_length, zad1, wejscie);
	tools::save(zad1);
	cout << "Czas calkowity: " << tools::c_max(zad1_length, zad1) << endl;
	tools::sort_1(zad1);
	cout << "Czas calkowity po sortowaniu 1: " << tools::c_max(zad1_length, zad1) << endl;
	tools::print(zad1);
	tools::sort_2(zad1);
	cout << "Czas calkowity po sortowaniu 2: " << tools::c_max(zad1_length, zad1) << endl;
	tools::print(zad1);
	tools::sort_3(zad1);
	cout << "Czas calkowity po sortowaniu 3: " << tools::c_max(zad1_length, zad1) << endl;
	tools::print(zad1);
	tools::sort_schrage(zad1_length, zad1, sorted);
	cout << "Czas calkowity po sortowaniu Schrage'a: " << tools::c_max(zad1_length, sorted) << endl;
	tools::print(sorted);
	

	tools::clean(zad1_length, zad1);
	tools::clean(zad1_length, sorted);
	
	tools::pause();
	return 0;
}
