namespace tools {
	
	
	//PAUSE *****************************************************************************************
	void pause() {
		do std::cout << std::endl << std::endl << "Press the Enter key to continue...";
		while (std::cin.get() != '\n');
	}
	
	
	//LOAD ******************************************************************************************
	short load(std::vector<std::vector<std::vector<unsigned> > >& database,
			std::vector<std::vector<unsigned> >& indexes,
			std::string const& wejscie)
	{
		std::ifstream file;
		std::string line;
		unsigned data_quantity, task_length, number;
		unsigned i, j;
		
		std::vector<unsigned> pack_indexes;
		pack_indexes.resize(2);
		
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
                    pack_indexes[0]=data_quantity;
                    pack_indexes[1]=task_length;
                    indexes.push_back(pack_indexes);
                    
					std::vector<std::vector<unsigned> > data_pack;
					data_pack.reserve(data_quantity);
					
					std::vector<unsigned> vector_line;
					vector_line.resize(task_length+1);
                    
				    for(i=1; i<=data_quantity; ++i){//tutaj wczytujemy pakiet zadan
					    vector_line[0]=i;
					    
					    for(j=1; j<=task_length; ++j){//tutaj wczytujemy linie
						    file >> number;
						    vector_line[j]=number;
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
		unsigned i, j;
		
		//zalatwiamy pierwszy element data_pack
		temp_time[0]=data_pack[0][1];
		for(i=1; i<temp_time.size(); ++i) temp_time[i]=temp_time[i-1]+data_pack[0][i+1];
		
		for(i=1; i<data_pack.size(); ++i){
			temp_time[0] += data_pack[i][1];
			for(j=1; j<temp_time.size(); ++j){
				temp_time[j] = (std::max(temp_time[j-1], temp_time[j]) + data_pack[i][j+1]);
			}
		}
		
		return temp_time[temp_time.size()-1];
	}

	//funkcja odbudowujaca graf od lewej do prawej **************************************************
	void c_max_left(std::vector<std::vector<unsigned> > const& data_pack,
					unsigned ** data_pack_time_left, unsigned rebuild_index, unsigned const& n)
	{
	
	    unsigned i, j, temp;
	    unsigned data_pack_size = data_pack.size();

		if(rebuild_index == 0){
			for(i=0, temp=0; i<n; ++i){
				data_pack_time_left[0][i] = temp += data_pack[0][i+1];
			}
			++rebuild_index;
		}
	
		//sprawdzamy czy czasem nie kazemy sie zbudowac od miejsca w ktorym juz sie skonczyl graf
		if(rebuild_index < data_pack_size){
			//budujemy od indeksu na pewno niezerowego
			for(i=rebuild_index; i<data_pack_size; ++i){
				data_pack_time_left[i][0] = data_pack_time_left[i-1][0] + data_pack[i][1];
				
				for(j=1; j<n; ++j){
					data_pack_time_left[i][j] = data_pack[i][j+1] + std::max(data_pack_time_left[i-1][j], data_pack_time_left[i][j-1]);
				}
			}
		}
	}
	
	//funkcja odbudowujaca graf od prawej do lewej **************************************************
	void c_max_right(std::vector<std::vector<unsigned> > const& data_pack,
					unsigned ** data_pack_time_right, unsigned rebuild_index, unsigned const& n)
	{
		
		unsigned i, j, temp;
		unsigned data_pack_size = data_pack.size();
		unsigned data_pack_size_minus_1 = data_pack_size - 1;
		
		if(rebuild_index == 0){
			for(i=0, temp=0; i<n; ++i){
				data_pack_time_right[0][i] = temp += data_pack[data_pack_size_minus_1][n-i];
			}
			++rebuild_index;
		}
	
		if(rebuild_index < data_pack_size){
			for(i=rebuild_index; i<data_pack_size; ++i){
				data_pack_time_right[i][0] = data_pack_time_right[i-1][0] + data_pack[data_pack_size_minus_1-i][n];
				
				for(j=1; j<n; ++j){
					data_pack_time_right[i][j] = data_pack[data_pack_size_minus_1-i][n-j] + std::max(data_pack_time_right[i-1][j], data_pack_time_right[i][j-1]);
				}
			}
		}
	}
	
	//klasa do porownywania elementow w kolejce priorytetowej ***************************************
	struct compare_time {
        bool operator()(std::vector<unsigned> const& t1, std::vector<unsigned> const& t2) {
        	unsigned time1 = 0, time2 = 0;
        	unsigned i;
        	
        	for(i = 1; i< t1.size(); ++i) time1 += t1[i];
       		for(i = 1; i< t2.size(); ++i) time2 += t2[i];
        	if (time1 == time2) return t1[0] > t2[0];//zwracamy ten z nizszym indeksem jesli ten sam czas
           	return (time1) < (time2);//zwracamy ten z dluzszym czasem
       	}
	};
	
	/*
	//CLEAN *****************************************************************************************
	short clean() {
	
		
		std::cerr << std::endl << "Unidentified error within tools::clean()";
		return -1;
	}
	*/
	
}
