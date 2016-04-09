namespace tools {
	
	
	//PAUSE *****************************************************************************************
	void pause() {
		do std::cout << std::endl << std::endl << "Press the Enter key to continue...";
		while (std::cin.get() != '\n');
	}
	
	
	//LOAD ******************************************************************************************
	short load(std::vector<std::vector<std::vector<unsigned> > >& database, std::string wejscie) {
		std::ifstream file;
		std::string line;
		unsigned data_quantity;
		unsigned task_length;
		unsigned number;
		
		file.open(wejscie.c_str(), std::ios::in);
		
		if (file.fail()) {
			std::cerr << std::endl << "File didn't open properly within tools::load()";
			return 1;
		}
		
		if (file.is_open()) {
			while(!file.eof()){
				getline(file, line);
			    if(line[0] == 'd' && line[8] == ':'){
                    file >> data_quantity >> task_length;
					std::vector<std::vector<unsigned> > data_pack;
					data_pack.reserve(data_quantity);
                    
				    for(unsigned i=0; i<data_quantity; ++i){//tutaj wczytujemy pakiet zadan
					    std::vector<unsigned> vector_line;
					    vector_line.reserve(task_length);
					    
					    for(unsigned j=0; j<task_length; ++j){//tutaj wczytujemy linie
						    file >> number;
						    vector_line.push_back(number);
					    }
						data_pack.push_back(vector_line);
				    }
				    database.push_back(data_pack);
				}
			}
			
			file.close();
   			return 0;
    	}
    	
		std::cerr << std::endl << "Unidentified error within tools::load()";
		return -1;
	}
	
	
	//SAVE ******************************************************************************************
	short save(std::vector<std::vector<std::vector<unsigned> > > const& database) {
		std::ofstream file;
		file.open("posortowane.txt", std::ios::out);
	
		if (file.fail()) {
			std::cerr << std::endl << "File didn't open properly within tools::save()";
			return 1;
		}
	
		if (file.is_open()) {
			
			//do napisania wedle potrzeb
		
		return 0;
		}
		
		std::cerr << std::endl << "Unidentified error within tools::save()";
		return -1;
	}
	
	/*	
	//PRINT *****************************************************************************************
	short print(std::vector< std::vector<unsigned> > const& zad) {
		
		return 0;
	}
	*/
	
	/*
	//CLEAN *****************************************************************************************
	short clean(unsigned zad_length, std::vector< std::vector<unsigned> >& zad) {
		
		for (unsigned i=0; i < zad_length; ++i) {
			zad[i].clear();
		}
		zad.clear();
		zad_length = 0;
		
		if(zad.empty() && zad_length == 0) return 0;
		else {
			std::cerr << std::endl << "Vector is not empty within tools::clean()";
			return 1;
		}
		
		std::cerr << std::endl << "Unidentified error within tools::clean()";
		return -1;
	}
	*/
	
}
