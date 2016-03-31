namespace tools {
	
	
	//PAUSE *****************************************************************************************
	void pause() {
		do std::cout << std::endl << std::endl << "Press the Enter key to continue...";
		while (std::cin.get() != '\n');
	}
	
	
	//LOAD ******************************************************************************************
	short load(unsigned zad_length, std::vector<std::vector<unsigned> >& zad, std::string wejscie) {
		std::ifstream file;
		file.open(wejscie.c_str(), std::ios::in);
		
		if (file.fail()) {
			std::cerr << std::endl << "File didn't open properly within tools::load()";
			return 1;
		}
		
		if (file.is_open()) {
    		//! to do optymalizacji
    		unsigned counter = 1;
    		unsigned p, w, d;
			file >> zad_length;
			
			while (counter <= zad_length) {
				std::vector<unsigned> temp;
				file >> p;
				file >> w;
				file >> d;
				temp.push_back(counter);
				temp.push_back(p);
				temp.push_back(w);
				temp.push_back(d);
				zad.push_back(temp);
				++counter;
			}
			
			file.close();
		
   		return 0;
    	}
    	
		std::cerr << std::endl << "Unidentified error within tools::load()";
		return -1;
	}
	
	
	//SAVE ******************************************************************************************
	short save(std::vector< std::vector<unsigned> > const& zad) {
		std::ofstream file;
		file.open("posortowane.txt", std::ios::out);
	
		if (file.fail()) {
			std::cerr << std::endl << "File didn't open properly within tools::save()";
			return 1;
		}
	
		if (file.is_open()) {
			for (unsigned i=0; i < zad.size(); ++i){
				for (unsigned j=1; j < zad[i].size(); ++j){
					file << zad[i][j];
					file << ' ';
				}
				file << std::endl;
			}
		
		return 0;
		}
		
		
		std::cerr << std::endl << "Unidentified error within tools::save()";
		return -1;
	}
	
		
	//PRINT *****************************************************************************************
	short print(std::vector< std::vector<unsigned> > const& zad) {

		for (unsigned i=0; i < zad.size(); ++i){
			std::cout << zad[i][0];
			std::cout << ' ';
		}
		std::cout << std::endl;
		
		return 0;
	}
	
	
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
	
	/* kara i-tego zadania bez kar poprzedzajacych */
	int i_penalty(unsigned c_temp, std::vector< std::vector <unsigned> > const& task, int k) {
		if (c_temp > task[k][3]){
			return (c_temp - task[k][3])* task[k][2];
		}
		else return 0;
	}
	
	/* kara calkowita dla wektora wejsciowego */
	unsigned long sum_penalty(std::vector< std::vector<unsigned> > const& tasks){
		unsigned long sum = 0;
		unsigned long c_temp = 0;
		
		for (unsigned i = 0; i<tasks.size(); ++i){
			c_temp += tasks[i][1];
			if(c_temp > tasks[i][3]) sum += (c_temp - tasks[i][3])*tasks[i][2];
		}
		return sum;
	}
	
	/* czas wybranych zadan */
	unsigned long time(int i, std::vector< std::vector<unsigned> > const& tasks){
		int k, j;
		int time = 0;
		for(j = 1, k = 0;j <= i;j<<=1,k++){
			if(j&i) time += tasks[k][1];
		}
		return time;
	}
	
	/* czas calkowity dla wektora wejsciowego */
	unsigned long sum_time(std::vector< std::vector<unsigned> > const& tasks){
		unsigned long sum = 0;
		for (unsigned i = 0; i<tasks.size(); ++i) sum += tasks[i][1];
		return sum;
	}
	
	void print1d(std::vector< long int > const& task) {
		std::cout << "Drukuje\n";
		for(unsigned int i = 0; i < task.size(); i++){
			std::cout << task[i] << std::endl;
		}
	}
	
	void print2d(std::vector< std::vector < long int > > const& task, int pole) {
		std::cout << "Drukuje pole " << pole << std::endl;
		for(unsigned int i = 0; i < task.size(); i++){
			std::cout << task[i][pole] << std::endl;
		}
	}
	
	/* zamienia wektor jednowymiarowy indeksow na wektor zadan */
	void swap_index(std::vector< long int > const& index_l, std::vector< std::vector<unsigned> >& tasks, unsigned n) {
		std::vector< int > indeksy;
		std::vector< std::vector<unsigned> > temp_vec;
		indeksy.resize(n);
		temp_vec.resize(n);
		unsigned indeks;
		unsigned temp = index_l.size() - 1;
		
		for(unsigned int i = n; i; i--){
			indeks = index_l[temp];
			indeksy[i-1] = indeks;
			temp = temp - (1uL<<(indeks-1));
		}
		
		for(unsigned int i = 0; i < indeksy.size(); i++){
			temp_vec[i] = tasks[indeksy[i]-1];
		}
		
		tasks.swap(temp_vec);
	}
	
	/* sortuje wektor zadan krytycznych aby uzyskac rozwiazanie pierwsze topologicznie */
	void sort_vector(std::vector< std::vector<unsigned> >& tasks1) {
		unsigned zapas = 0;
		unsigned time = 0;
		unsigned poz = 0;
		unsigned poz2 = 0;
		unsigned index;
		unsigned min_task;
		unsigned min_zapas;
		unsigned i, j;
		bool warunek;
		
		for(poz = 0; poz < tasks1.size(); poz++){
			time = 0;
			zapas = 0;
			min_zapas = 99999;
			min_task = 99999;
			index = 99999;
			warunek = false;
			
			// liczenie minimalnego czasu przetwarzania dla zadan po pozycji startowej
			for(j = poz+1; j < tasks1.size(); j++){
				if(tasks1[j][1] < min_task)	min_task = tasks1[j][1];
			}
//			std::cout << "Minimalny czas tasks1 " << min_task << std::endl;
			
			// liczenie czasu zadan przed pozycja startowa
			for(i = 0; i < poz; i++){
				time += tasks1[i][1];
			}
//			std::cout << "Czas przed " << time << std::endl;
			// liczenie zapasu zadania startowego
			time += tasks1[poz][1];
			std::cout << "Czas startu " << time << std::endl;
			if(tasks1[poz][3] > time){
				min_zapas = tasks1[poz][3] - time;
			}
			else min_zapas = 0;	
			
//			std::cout << "Zadanie startu " << tasks1[poz][0] << std::endl;
//			std::cout << "Zapas zad startu " << min_zapas << std::endl;

			// szukanie zadania o najmniejszym indeksie, ktore mozna wstawic przed zadanie startowe
			if(min_zapas >= min_task){
				for(i = poz+1; i < tasks1.size(); i++){
					time += tasks1[i][1];
//					std::cout << "Czas po starcie " << time << std::endl;
//					std::cout << "Limit zadania " << tasks1[i][3] << std::endl;
					if(tasks1[i][3] >= time){
						zapas = tasks1[i][3] - time;
						if(zapas < min_zapas) min_zapas = zapas;						
//						std::cout << "Zapas " << min_zapas << "  Numer zad startu: "  << tasks1[poz][0] << std::endl;
//						std::cout << "Numer zadania: " << tasks1[i][0] << "  Index: " << index << std::endl;
//						std::cout << "Limit zadania: " << tasks1[i][3] << "  Min zapas: " << min_zapas << std::endl;
						
						// jezeli numer zadania jest mniejszy i czas przetwarzania jest mniejszy od min zapasu
						if(tasks1[i][0] < index && tasks1[i][0] < tasks1[poz][0] && tasks1[i][1] <= min_zapas){
							index = tasks1[i][0];
							poz2 = i;
							warunek = true;
//							std::cout << "Wybrano zadanie " << index << "  na pozycji " << poz2 << std::endl;
						}
					}
				}
			}
			
//			std::cout << "Start: " << poz << std::endl;
//			std::cout << "Zadanie poczatkowe: " << tasks1[poz][0] << std::endl;
//			std::cout << "Zadanie: " << poz2 << std::endl;
//			std::cout << "Zadanie wybrane: " << tasks1[poz2][0] << std::endl;
		
			// wstawianie znalezionego zadania przed zadanie startowe	
			if(warunek) {
//				std::cout << "Pozycja poz2 " << poz2 << std::endl;
//				tools::print(tasks1);
				tasks1.insert(tasks1.begin()+poz,tasks1[poz2]);
//				tools::print(tasks1);
//				std::cout << "Zapas przed " << min_zapas << std::endl;
				min_zapas = min_zapas - tasks1[poz2][1];
//				std::cout << "Zapas po " << min_zapas << std::endl;
				tasks1.erase(tasks1.begin()+poz2+1);
//				tools::print(tasks1);
				poz--;
			}
			//	else warunek = false;
			
			tools::print(tasks1);
//			pause();
		}
	}	
	
	/* laczy wektory zadan tak, aby uzyskac rozwiazanie pierwsze topologicznie */
	void merge(std::vector< std::vector<unsigned> >& tasks1, std::vector< std::vector<unsigned> >& tasks2) {
		unsigned zapas = 0;
		unsigned time = 0;
		unsigned poz = 0;
		unsigned poz2 = 0;
		unsigned min_task;
		unsigned min_zapas;
		unsigned i, j;
		bool warunek = true;
		
		while(warunek){
			time = 0;
			zapas = 0;
			min_zapas = 99999;
			min_task = 99999;
			for(j = 0; j < tasks2.size(); j++){
				if(tasks2[j][1] < min_task)	min_task = tasks2[j][1];
			}
//			std::cout << "Minimalny czas tasks2 " << min_task << std::endl;
			
			for(i = 0; i < tasks1.size(); i++){
				time += tasks1[i][1];
				if(tasks1[i][3] > time){
					zapas = tasks1[i][3] - time;
				}
				else zapas = 0;
				
				if(min_zapas == 0 && zapas >= min_task){
					min_zapas = zapas;
					if(poz<i) poz = i;
				}
				
				if(zapas < min_zapas){
					min_zapas = zapas;
//					poz = i;
				}
				if(zapas < min_task){
					min_zapas = 0;				
				}

//				std::cout << "Numer zadania " << tasks1[i][0] << "  Pozycja zadania " << i << std::endl;
//				std::cout << "Czas " << time << std::endl;
//				std::cout << "Zapas " << zapas << std::endl;
//				std::cout << "Minimalny zapas " << min_zapas << std::endl;
//				std::cout << "Zadanie " << poz << std::endl;
			}
			
//			std::cout << "Czas " << time << std::endl;
//			std::cout << "Zapas " << min_zapas << std::endl;
//			std::cout << "Zadanie " << poz << std::endl;
			
			if(poz < tasks1.size()) poz2 = tasks1[poz][0];
			
			if(min_zapas < min_task || tasks2.size() == 1 || poz == tasks1.size() - 1){
				warunek = false;
				while(!tasks2.empty()){
					tasks1.push_back(tasks2[0]);
					tasks2.erase(tasks2.begin());
				}	
			} 
			else{
				for(j = 0; j < tasks2.size(); j++){
					if(tasks2[j][1] <= min_zapas && tasks2[j][0] < poz2) {
//						tools::print(tasks1);
						tasks1.insert(tasks1.begin()+poz,tasks2[j]);
//						std::cout << "Zapas przed " << min_zapas << std::endl;
						min_zapas = min_zapas - tasks2[j][1];
//						std::cout << "Zapas po " << min_zapas << std::endl;
						tasks2.erase(tasks2.begin()+j);
//						tools::print(tasks1);
						poz++;
						j--;
					}
				}
				poz++;
			}
			
//			tools::print(tasks1);
//			tools::print(tasks2);
			
//			pause();
		}
	}
	
}
