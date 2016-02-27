#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <iostream>
#include <vector>

namespace tools {

	//PAUSE *********************************************
	void pause()
	{
		do
		{
			std::cout << "\n" << "Press the Enter key to continue.";
		}
		while (std::cin.get() != '\n');
	}

	//LOAD *********************************************
	int load(unsigned& zad_length, std::vector< std::vector<int> > &zad)
	{
		std::ifstream file;
		file.open("dane.txt", std::ios::in);
		
		if (file.fail())
		{
			std::cout << "File didn't open properly";
			return 1;
		}
		
		if (file.is_open())
    	{
    		unsigned i;
			file >> zad_length;
			std::cout << zad_length;
			file.close();
			
			while(!file.eof())
			{
			
			}
		
   		return 0;
    	}
    	
		std::cerr << "Unidentified error";
		return -1;
	}
	
	//C_MAX *********************************************
	int c_max(unsigned& zad_length, std::vector< std::vector<int> > &zad) {
		
		
		return 0;
	}
	
}

#endif //TOOLS_H_INCLUDED
