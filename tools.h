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
                    
				    for(unsigned i=1; i<=data_quantity; ++i){//tutaj wczytujemy pakiet zadan
					    std::vector<unsigned> vector_line;
					    vector_line.reserve(task_length+1);
					    vector_line.push_back(i);
					    
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
		file.open("after_sort.txt", std::ios::out);
	
		if (file.fail()) {
			std::cerr << std::endl << "File didn't open properly within tools::save()";
			return 1;
		}
	
		if (file.is_open()) {
			for(unsigned i=0; i<database.size(); ++i){//tutaj wczytujemy pakiet zadan
				file << "NEH." << i+1 << ':' << std::endl;
					    
				for(unsigned j=0; j<database[i].size(); ++j){//tutaj wczytujemy linie
					file << database[i][j][0] << ' ';
				}
				
				file << std::endl << std::endl;
			}
		
		return 0;
		}
		
		std::cerr << std::endl << "Unidentified error within tools::save()";
		return -1;
	}
	
	int c_max(std::vector<std::vector<unsigned> > data_pack){
		std::vector<unsigned> temp_time;
		temp_time.resize(data_pack[0].size()-1);
		
		//zalatwiamy pierwszy element data_pack
		temp_time[0]=data_pack[0][1];
		for(unsigned i=1; i<temp_time.size(); ++i) temp_time[i]=temp_time[i-1]+data_pack[0][i+1];
		
		for(unsigned i=1; i<data_pack.size(); ++i){
			temp_time[0] += data_pack[i][1];
			for(unsigned j=1; j<temp_time.size(); ++j){
				temp_time[j] = (std::max(temp_time[j-1], temp_time[j]) + data_pack[i][j+1]);
			}
		}
		
		return temp_time[temp_time.size()-1];
	}
	
	struct compare_time {
        bool operator()(std::vector<unsigned> const& t1, std::vector<unsigned> const& t2) {
        	if ((t1[1]+t1[2]+t1[3]) == (t2[1]+t2[2]+t2[3])) return t1[0] > t2[0];//zwracamy ten z nizszym indeksem jesli ten sam czas
           	return (t1[1]+t1[2]+t1[3]) < (t2[1]+t2[2]+t2[3]);//zwracamy ten z dluzszym czasem
       	}
	};
	
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
