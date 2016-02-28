#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "tools.h"

using namespace std;
/* zrodla do poczytania

http://dominik.zelazny.staff.iiar.pwr.wroc.pl/pliki/spd/zad1/Zadanie_1.pdf

*/

int main() {
	vector<vector<unsigned> > zad1;
	unsigned zad1_length;

	tools::load(zad1_length, zad1);
	tools::save(zad1);
	cout << "Czas calkowity: " << tools::c_max(zad1_length, zad1) << endl;
	tools::clean(zad1_length, zad1);
	
	tools::pause();
	return 0;
}
