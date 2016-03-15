#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

namespace tools {

	//PAUSE *****************************************************************************************
	void pause() {
		do std::cout << std::endl << std::endl << "Press the Enter key to continue...";
		while (std::cin.get() != '\n');
	}

	//LOAD ******************************************************************************************
	short load(unsigned& zad_length, std::vector<std::vector<unsigned> >& zad, std::string wejscie) {
		std::ifstream file;
		file.open(wejscie.c_str(), std::ios::in);
		
		if (file.fail()) {
			std::cerr << std::endl << "File didn't open properly within tools::load()";
			return 1;
		}
		
		if (file.is_open()) {
    		//! to do optymalizacji
    		unsigned counter = 1;
    		unsigned r, p, q;
			file >> zad_length;
			
			while (counter <= zad_length) {
				std::vector<unsigned> temp;
				file >> r;
				file >> p;
				file >> q;
				temp.push_back(counter);
				temp.push_back(r);
				temp.push_back(p);
				temp.push_back(q);
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
	short clean(unsigned& zad_length, std::vector< std::vector<unsigned> >& zad) {
		
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
	
	/*
	c_max() wykonane wg algorytmu podanego na laboratorium nr 1
	*/
	
	//C_MAX *****************************************************************************************
	long c_max(unsigned const& zad_length, std::vector< std::vector<unsigned> > const& zad) {
		
		unsigned long c_max = 0;
		unsigned long t_p = 0;
		unsigned i;
	
		for (i=0; i < zad_length; ++i) {
			t_p = std::max<unsigned long>(t_p,zad[i][1]) + zad[i][2];
			c_max = std::max<unsigned long>(t_p + zad[i][3], c_max);
		}
		
		if (i-- == zad.size() ) return c_max;
		else {
			std::cerr << std::endl << "Vector was not fully checked within c_max()";
			return -2;
		}
		
		std::cerr << std::endl << "Unidentified error within tools::c_max()";
		return -1;
	}

	
	/* komparatory do Schrage *///*******************************************************************
	struct compare_r {
        bool operator()(std::vector<unsigned> const& t1, std::vector<unsigned> const& t2) {
           	return t1[1] > t2[1];
        }
   	};
   	
	struct compare_q {
        bool operator()(std::vector<unsigned> const& t1, std::vector<unsigned> const& t2) {
           	return t1[3] < t2[3];
        }
   	};
	
	/*
	schrage() oraz preshrage() napisany na podstawie algorytmu podanego na stronie:
	http://dominik.zelazny.staff.iiar.pwr.wroc.pl/materialy/Algorytm_Schrage.pdf
	*/
	
	/* schrage *///**********************************************************************************
	int schrage (std::vector< std::vector<unsigned> > & tasks) {
		unsigned t = 0;
		unsigned c_max = 0;
		std::vector<std::vector<unsigned> > pi; //permutacja zadan po sortowaniu
		
		std::priority_queue <std::vector<unsigned>, std::vector< std::vector<unsigned> >, compare_r> N; //kolejka min(r)
		std::priority_queue <std::vector<unsigned>, std::vector< std::vector<unsigned> >, compare_q> G; //kolejka max(q)
		
		while (!tasks.empty()) {
			N.push(tasks.back()); //wrzucamy zadania do kolejki min(r)
			tasks.pop_back(); //kasujemy zadania do posortowania
		}
		
		while ((!G.empty()) || (!N.empty())) { //dopoki wszystkie zadania nie zostaly przetworzone
			
			while ((!N.empty()) && (N.top()[1] <= t)) { //jesli jest zadanie co "p" ma mniejsze od momentu czasowego
				G.push(N.top()); //wrzucamy nowe zadanie do kolejki max(q)
				N.pop(); //i kasujemy z kolejki min(r)
			}
			
			if (G.empty()) { //jesli nie ma zadnego zadania przygotowanego do przetwarzania
				t = N.top()[1]; //przesuwamy sie o odpowiedni czas
			}
			else {
			t += G.top()[2]; //przesuwamy sie z czasem "t" do przodu
			c_max = std::max<int>(c_max, t + G.top()[3]); //zwiekszamy "c_max"
			pi.push_back(G.top()); //zapisujemy wykonane zadanie w permutacji "pi"
			G.pop(); //kasujemy zadanie z kolejki max(q)
			}
		}
		
		tasks = pi; //wpisujemy w wektor do posortowania permutacje zadan posortowanych
	
		return c_max;
	}
	
	/* schrage z przerwaniami *///*******************************************************************
	int preschrage (unsigned const& zad_length, std::vector< std::vector<unsigned> >const & tasks) {
		unsigned t = 0; //aktualny moment czasowy
		unsigned c_max = 0;
		std::vector<unsigned> machine_task; //zmienna przechowujaca zadanie wykonywane na maszynie
		machine_task.push_back(255565);  machine_task.push_back(0);
		machine_task.push_back(0);  machine_task.push_back(0); //tworzymy zadanie poczatkowe
		
		std::priority_queue <std::vector<unsigned>, std::vector< std::vector<unsigned> >, compare_r> N; //kolejka min(r)
		std::priority_queue <std::vector<unsigned>, std::vector< std::vector<unsigned> >, compare_q> G; //kolejka max(q)
		
		for (unsigned i = 0; i<zad_length; ++i) {
			N.push(tasks[i]); //wrzucamy zadania do kolejki min(r)
		}
		
		while ((!G.empty()) || (!N.empty())) { //dopoki wszystkie zadania nie zostaly przetworzone
			
			while ((!N.empty()) && (N.top()[1] <= t)) { //jesli jest zadanie co "p" ma mniejsze od momentu czasowego
				G.push(N.top()); //wrzucamy nowe zadanie do kolejki max(q) ale zostawiamy do porownania z zadaniem na maszynie
				
				if (N.top()[3] > machine_task[3]) { //jesli dorzucone zadanie ma wieksze "q" od zadania na maszynie
					machine_task[2] = t - N.top()[1]; //zmniejszamy zadanie na maszynie o tyle ile sie wykonalo
					t = N.top()[1]; //nowy czas jest czasem "p" zadania nowo przybylego
				}
				
				if (machine_task[2] > 0) {
					G.push(machine_task); //jesli zadanie na maszynie nie skonczone to z powrotem do kolejki max(q)
				}
				
				N.pop(); //po porownaniu z zadaniem na maszynie kasujemy
			}

			if (G.empty()) { //jesli nie ma zadnego zadania przygotowanego do przetwarzania
				t = N.top()[1]; //przesuwamy sie o odpowiedni czas
			}
			else {
			machine_task = G.top(); //wrzucamy na maszyne zadanie z kolejki max(q)
			G.pop();
			t += machine_task[2]; //przesuwamy sie z czasem "t" do przodu
			c_max = std::max<int>(c_max, t + machine_task[3]); //zwiekszamy "c_max"
			}
		}
		
		return c_max;
	}
	
	/*
	set_a_b_index(), c_not_exists(), carlier() napisane na podstawie algorytmu podanego na stronie:
	http://dominik.zelazny.staff.iiar.pwr.wroc.pl/materialy/Algorytm_Carlier.pdf
	*/
	
	/* wyznaczanie sciezki krytycznej o indeksach a i b *///************************************************************************
	void set_a_b_c_index(unsigned const& n, std::vector<std::vector<unsigned> > const& pi, long unsigned const& U, unsigned & a_index, unsigned & b_index){
		a_index = 0;
		b_index = 0;
		unsigned j, s;
		unsigned sum;
		unsigned t_p = 0;
		unsigned c_temp = 0;
		
		std::cout << "Wyznaczam b." << std::endl;
		
		for (j=0; j<n; j++){ //przeszukujemy wszystkie zadania z permutacji "pi"
			t_p = std::max<unsigned long>(t_p,pi[j][1]) + pi[j][2];
			c_temp = std::max<unsigned long>(t_p + pi[j][3], c_temp); //tutaj zwiekszam sobie c_max dla j-tego elementu
			
			if (c_temp == U){
				std::cout << "Indeks b: "  << j << std::endl;
				b_index = j;
			}
		}
		
		std::cout << "Wyznaczam a." << std::endl;
		
		sum = 0;
		for (s=0; s<=b_index; s++)	sum += pi[s][2]; //suma "p" od 0 do "b_index"
		
		for (j=0; j<n; j++){ //przesuwamy sie po wszystkich elementach wektora
			if (pi[j][1] + sum + pi[b_index][3] <= U) { //sprawdzamy warunek
				a_index = j;
				std::cout << "Indeks a: " << a_index << std::endl;
				break; //pierwsze znalezione "a_index" konczy petle
			}
			
			sum -= pi[j][2]; //zmieniamy przedzial sumy kiedy zmienia sie "a"
		}
	}
	
	/* wyznaczanie c *///****************************************************************************
	bool c_not_exists(std::vector<std::vector<unsigned> > const& pi, unsigned const& a_index, unsigned const& b_index, unsigned& c_index) {
		bool c_not_exists = true; //c domyslnie nie istnieje
		
		for (unsigned j=a_index; j<=b_index; ++j){ //poruszamy sie po sciezce krytycznej
			if (pi[j][3] < pi[b_index][3]){ //szukamy zadania o najwyzszym indeksie poprzedzajacego "b_index" z dluzszym "q" od "b_index"
				c_not_exists = false; //c istnieje
				c_index = j; //jesli znalezione zadanie c to zapisujemy jego indeks w "c_index"
			}
		}
		
		return c_not_exists;
	}
	
	/* carlier *///**********************************************************************************
	int carlier(unsigned const& n, std::vector< std::vector<unsigned> > & tasks, unsigned& UB){
		long unsigned U, LB;
		unsigned r_old, q_old;
		unsigned r_prim = 0;
		unsigned p_prim = 0;
		unsigned q_prim = 0;
		unsigned a_index, b_index, c_index;
		
		std::vector<std::vector<unsigned> > pi = tasks;
		
		//1
		U = schrage(pi); //wyznaczamy sobie c_max w permutacji "pi"
		std::cout << "Carlier 1." << std::endl;
		
		//2
		if(U < UB){ //jesli c_max jest mniejsze od gornego ograniczenia to zapisujemy te permutacje
			UB = U;
			tasks = pi;
		}
		std::cout << "Carlier 2." << std::endl;
		
		//pierwsza polowa 3
		set_a_b_c_index(n, pi, U, a_index, b_index); //wyznaczamy indeksy sciezki krytycznej
		std::cout << "Carlier 3." << std::endl;
		
		//4 i druga polowa 3
		if (c_not_exists(pi, a_index, b_index, c_index)){ //wyznaczamy indeks zadania referencyjnego
		std::cout << "C does not exist.";
		return 0;
		}
		std::cout << "Carlier 4." << std::endl;
		
		//5
		p_prim = 0;
		for (unsigned i=(c_index+1); i<b_index; ++i) {
			if (pi[i][1] < r_prim) r_prim = pi[i][1];
			if (pi[i][3] < q_prim) q_prim = pi[i][3];
			p_prim += pi[i][2];
		}
		std::cout << "Carlier 5." << std::endl;
		
		//6
		r_old = pi[c_index][1]; //zapamietujemy sobie wartosc "r" zadania referencyjnego o indeksie "c_index"
		pi[c_index][1] = std::max<unsigned>(pi[c_index][1], r_prim+p_prim); //nadpisujemy wartosc "r" zadania referencyjnego nowa wartoscia
		std::cout << "Carlier 6." << std::endl;
		
		//7
		LB = preschrage(n, pi); //wyznaczamy dolne ograniczenie permutacji "pi"
		std::cout << "Carlier 7." << std::endl;
		
		//8
		if (LB < UB) { //jesli da sie lepiej upakowac zadania
		   std::cout << "Carlier 8." << std::endl; 
		   /*9*/ 
		   carlier(n, pi, UB); //to uruchamiamy znowu carliera
		}
		std::cout << "Carlier 9." << std::endl;
		
		//10
		pi[c_index][1] = r_old; //przywracamy stara wartosc "r" w zadaniu referencyjnym
		std::cout << "Carlier 10." << std::endl;
		
		//11
		q_old = pi[c_index][3]; //zapamietujemy wartosc "q" z zadania referencyjnego
		pi[c_index][3] = std::max<unsigned>(pi[c_index][3], q_prim+p_prim); //nadpisujemy wartosc "q" zadania referencyjnego
		std::cout << "Carlier 11." << std::endl;
		
		//12
		LB = preschrage(n, pi); //wyznaczamy sobie dolne ograniczenie permutacji "pi"
		std::cout << "Carlier 12." << std::endl;
		
		//13
		if (LB < UB){ //jesli da sie lepiej upakowac
		    std::cout << "Carlier 13." << std::endl; 
			/*14*/ 
		 	carlier(n, pi, UB); //to uruchamiamy carlier 
		}
  		std::cout << "Carlier 14." << std::endl; 
  		
		//15
		pi[c_index][3] = q_old; //przywracamy stara wartosc "q" w zadaniu referencyjnym
  		std::cout << "Carlier 15." << std::endl; 
		
		return -1;
	}
}

#endif //TOOLS_H_INCLUDED
