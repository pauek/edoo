
#include <iostream>
#include <fstream>
using namespace std;

#include "DataHora.h"

int main() {
  DataHora ini, fin, buscada;
  string desc;
  
  cout << "Data i hora (dd/mm/aaaa-HH:MM:SS)? ";
  cin >> buscada;

  ifstream F("Agenda.txt");
  F >> ini >> fin;
  getline(F, desc);
  bool trobada = false;
  while (!F.eof() && !trobada) {
	 if (ini <= buscada && buscada <= fin) {
		trobada = true;
	 } else {
		F >> ini >> fin;
		getline(F, desc);
	 }
  }
  if (trobada) cout << desc << endl;
}
