
#include <iostream>
#include <fstream>
using namespace std;

#include "FranjaHoraria.h"

int main() {
  DataHora buscada;
  FranjaHoraria franja;
  string desc;
  
  cout << "Data i hora (dd/mm/aaaa-HH:MM:SS)? ";
  cin >> buscada;

  ifstream F("Agenda.txt");
  F >> franja;
  getline(F, desc);
  bool trobada = false;
  while (!F.eof() && !trobada) {
	 if (franja.a_dins(buscada)) {
		trobada = true;
	 } else {
		F >> franja;
		getline(F, desc);
	 }
  }
  if (trobada) cout << desc << endl;
}


