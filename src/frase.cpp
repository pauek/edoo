
#include <iostream>
using namespace std;

#include "frase.h"

Frase::Frase() {
  esborra();
}

void Frase::afegeix_paraula(string s) {
  _paraules[_nparaules] = s;
  _nparaules++;
}


void Frase::mostra(ostream& o) {
  if (_nparaules > 0) 
    o << _paraules[0];
  for (int k = 1; k < _nparaules; k++) {
    o << ' ' << _paraules[k];
  }
}

void Frase::esborra() {
  _nparaules = 0;
}

int Frase::num_paraules() const {
  return _nparaules;
}

