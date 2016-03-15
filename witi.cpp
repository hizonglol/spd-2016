#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "tools.h"

using namespace std;

int main(){
	
std::vector< std::vector<unsigned> > tasks1;
unsigned tasks1_length;
string wejscie1 = "dane1.txt";
std::vector< std::vector<unsigned long> > penalties;

tools::load(tasks1_length, tasks1, wejscie1);

int r=1uL<<tasks1.size();

std::vector<unsigned long> temp;
temp.push_back(0);
temp.push_back(0);
temp.push_back(0);
penalties.push_back(temp);

//int c_max = 0;

for (int i = 1; i <= r; ++i){
	temp[0] = i;
	
	//temp[1] = tools::penalty(c_max, );
	
	//penalties.push_back(p);
	//c_max += ;
}
	std::cout << tools::sum_penalty(tasks1);

tools::pause();
	
	return 0;
}
