

//#include "pch.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;
struct lista {
	int id;
	struct lista *next;
};
int n;                   // Liczba wierzchołków
lista ** A;            // Macierz sąsiedztwa
bool * visited;          // Tablica odwiedzin

void tworzGraf(int a, int tablica[22][42]);
void tworzMacierz(bool segmenty[6][5][5]);
void losowanie(int n, int tablica[22][42]);
void BFS( int id);
int main()
{
	bool segmenty[6][5][5] =
	{
	   { // segment A
		  {0,0,1,0,0},
		  {0,1,1,0,0},
		  {1,1,0,1,1},
		  {0,1,1,1,0},
		  {0,0,1,0,0},
	   },
	   { // segment B
		  {0,0,1,1,0},
		  {1,0,0,1,0},
		  {1,1,1,1,1},
		  {0,1,1,1,0},
		  {0,0,1,1,0},
	   },
		 { // segment C
		  {1,1,1,1,1},
		  {1,1,0,1,1},
		  {1,1,0,0,1},
		  {0,1,0,0,0},
		  {0,1,1,1,1},
	   },
	   { // segment D
		  {0,0,1,1,1},
		  {0,1,1,0,1},
		  {1,1,0,1,1},
		  {1,0,1,1,0},
		  {0,1,1,0,0},
	   },
		 { // segment E
		  {1,1,1,0,0},
		  {0,1,1,1,0},
		  {1,1,0,1,1},
		  {1,1,0,1,1},
		  {1,1,1,1,0},
	   },
	   { // segment F
		  {0,0,1,0,0},
		  {0,0,1,0,0},
		  {1,1,1,1,1},
		  {0,0,1,0,0},
		  {0,0,1,0,0},
	   },

	};

	tworzMacierz(segmenty);

	/*int ax, ay;
	do
	{
		ay = rand() % (4 * 5);
		ax = rand() % (8 * 5);
	} while (!mapa[ay][ax]);
	*/
int m,i,v1,v2;
  lista *p,*r;

  cin >> n >> m;               // Czytamy liczbę wierzchołków i krawędzi

  A = new lista * [n];       // Tworzymy tablicę list sąsiedztwa
  visited = new bool[n];       // Tworzymy tablicę odwiedzin

  // Tablicę wypełniamy pustymi listami

  for(i = 0; i < n; i++)
  {
    A[i] = NULL;
    visited[i] = false;
  }

  // Odczytujemy kolejne definicje krawędzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzchołek startowy i końcowy krawędzi
    p = new lista;    // Tworzymy nowy element
    p->id = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na początek listy A[v1]
    A[v1] = p;
  }

  cout << endl;

  // Przechodzimy graf wszerz

  BFS(0);

  // Usuwamy tablicę list sąsiedztwa

  for(i = 0; i < n; i++)
  {
    p = A[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }
  delete [] A;
  delete [] visited;

  cout << endl;


	system("pause");
	return 0;
}
void tworzMacierz(bool segmenty[6][5][5])
{
	srand(time(0));
	bool mapa[4 * 5][8 * 5];
	for (int Y = 0; Y < 4; ++Y)
	{
		for (int X = 0; X < 8; ++X)
		{
			int rnd = rand() % 6;
			for (int y = 0; y < 5; ++y)
			{
				for (int x = 0; x < 5; ++x)
				{
					mapa[Y * 5 + y][X * 5 + x] = segmenty[rnd][y][x];
				}
			}
		}
	}
	int a = 1;
	int tablica[22][42];
	for (int i = 0; i < 22; i++) //stworzenie tablicy rozszerzonej z samymi zerami
	{
		for (int j = 0; j < 42; j++)
			tablica[i][j] = 0;
	}
	for (int i = 0; i < 20; i++) //wypelnienie nowej tablcy kolejnymi wierzchołakami
	{
		for (int j = 0; j < 40; j++)
		{
			if (mapa[i][j] == 1)
			{
				tablica[i + 1][j + 1] = a;
				a++;
			}

		}
	}
	for (int i = 0; i < 22; i++)
	{
		cout << endl;
		for (int j = 0; j < 42; j++)
			cout << setw(5) << tablica[i][j];
	}
	cout<<endl;
	tworzGraf(a, tablica);

}
void losowanie(int n, int tablica[22][42])
{   int a, b, c, d;
    srand(time(0));
    do{//PUNKT A

    b = rand() % 42;

    a = rand() % 22;
    d = rand() % 42;

    c = rand() % 22;

    }while(tablica[a][b]==0 || tablica[c][d]==0);



    cout<<"WSPOLRZEDNE PUNKTOW: A("<<a<<","<<b<<"), B("<<c<<","<<d<<")"<<endl;
    cout<<tablica[a][b]<<","<<tablica[c][d];
}


void tworzGraf(int a, int tablica[22][42])
{
	lista** graf;
	graf = new lista*[a];
	for (int i = 0; i < a; i++)
	{
		graf[i] = new lista;
	}

	int n = 0;
	for (int i = 1; i < 22; i++)
	{
		for (int j = 1; j < 42; j++)
		{
			if (tablica[i][j] != 0) {
				lista*pom = new lista;
				graf[n]->next = pom;
				pom->id = tablica[i][j];
				if (tablica[i - 1][j] = !0)
				{
					lista *tmp = new lista;
					tmp->id = tablica[i - 1][j];
					pom->next = tmp;
					pom = tmp;
				}
				if (tablica[i][j + 1] != 0)
				{
					lista *tmp = new lista;
					tmp->id = tablica[i][j + 1];
					pom->next = tmp;
					pom = tmp;
				}
				if (tablica[i + 1][j] != 0)
				{

					lista *tmp = new lista;
					tmp->id = tablica[i + 1][j];
					pom->next = tmp;
					pom = tmp;
				}
				if (tablica[i][j - 1] != 0)
				{

					lista *tmp = new lista;
					tmp->id = tablica[i][j - 1];
					pom->next = tmp;
					pom = tmp;
				}
				n++;
			}
		}
	}
	losowanie(n, tablica);
}




// Procedura przejścia wszerz
//---------------------------
void BFS( int id)
{
  lista *p,*q,*head,*tail; // Kolejka

  q = new lista;        // W kolejce umieszczamy id
  q->next = NULL;
  q->id = id;
  head = tail = q;

  visited[id] = true;      // Wierzchołek id oznaczamy jako odwiedzony

  while(head)
  {
    id = head->id;          // Odczytujemy id z kolejki

    q = head;             // Usuwamy z kolejki odczytane id
    head = head->next;
    if(!head) tail = NULL;
    delete q;

    cout << setw(3) << id;

    for(p = A[id]; p; p = p->next)
    if(!visited[p->id])
    {
      q = new lista; // W kolejce umieszczamy nieodwiedzonych sąsiadów
      q->next = NULL;
      q->id = p->id;
      if(!tail) head = q;
      else      tail->next = q;
      tail = q;
      visited[p->id] = true; // i oznaczamy ich jako odwiedzonych
    }
}  }
