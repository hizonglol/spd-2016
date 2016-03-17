#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define N 50

int w[N+1],p[N+1],d[N+1],pi[N+1];

unsigned int max(int x, int y) {
return (x>y)?x:y;
}

unsigned int f(int j, int s) {
return w[j]*max(0,s-d[j]);
}

int pd(const int n, const int p[], int pi[], unsigned int &z);
unsigned int F(const int n, const int pi[]);

void main(void)
{ int i,n=15; unsigned int e;

	for (i=1;i<=n;i++) {
		w[i]=1+random(5);
		p[i]=1+random(50);
		d[i]=random(5*n);
	}

	//w[1]=2; w[2]=1; w[3]=3; w[4]=1;
	//p[1]=5; p[2]=4; p[3]=6; p[4]=8;
	//d[1]=8; d[2]=10; d[3]=14; d[4]=12;

	pd(n,p,pi,e);

//  getch();
	clrscr();
	for (i=1;i<=n;i++) printf("%8d",pi[i]);
	printf("\n%8u\n%8u\n",e,F(n,pi));
	getch();
}

int pd(const int n, const int p[], int pi[], unsigned int &z) {
	//indeks pomocniczy
 	unsigned long e;
 	//maska
	unsigned long c;
 	//ile jest mozliwych kombinacji
	unsigned long r=1uL<<n;
 	//wektor kar 2^n
  	unsigned int *G=new unsigned int [r];
  	//indeks zadania wyznaczajacego minimum
  	unsigned short int *v=new unsigned short int [r];
  	//s moment czasowy
  	unsigned int s,k,a,t;
  	unsigned short int u;

	//jesli nie zaalokowane
  	if (!G) { return -1; }
  	if (!v) { delete G; return -1; }

	//zadanie zerowe ma zerowa kare
	G[0]=0;
	//oraz sklada sie na nie zerowe pole z poprzednia kara
	v[0]=0;
	
	//przeszukujemy wszystkie pola z karami oraz indeksami sk³adowych kar
	for (e=1;e<r;e++) {
		//suma czasow dzialania
 		s=0;
 		//przesuwamy maske c dopoki nie bedzie rowna e
 		for (c=k=1;c<=e;c<<=1,k++) if (e&c) s+=p[k]; //zwiekszamy sume o czas przetwarzania
 	
 		//negacja bitowa i przypisanie
		t=~0;
	
		for (c=k=1;c<=e;c<<=1,k++) {
			if (e&c) {
				//bierzemy element poprzedni z wektora kar,
				//powiekszamy o kare elementu przetwarzanego
				//i zapamietujemy
				a=G[e-c]+f(k,s);
				//wyszukujemy kombinacje dajaca najmniejsz¹ karê
				if (a<t) {
					t=a;
					u=k;
				}
			}
		}
		
		//zapisujemy optymalna kare
    	G[e]=t;
    	//zapisujemy indeks pola z ktorego zostala wzieta poprzednia kara
		v[e]=u;
		//idziemy z czasem do przodu
    	t=t+1;
  	}

	t=n;
	z=G[--e];
  
	while (t) {
		pi[t--]=k=v[e];
		e=e-(1uL<<(k-1));
	}

	delete G;
	delete v;
	return 0;
}

unsigned int F(const int n, const int pi[]) {
	unsigned int s=0,t=0;
	int j,k;

	for (j=1;j<=n;j++) {
		k=pi[j];
		s+=p[k];
		t+=w[k]*max(0,s-d[k]);
	}
	
	return t;
}
