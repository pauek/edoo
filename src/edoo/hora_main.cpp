#include <iostream>
#include <fstream>
#include "Hora.h"
using namespace std;

int main() {
  string fitxer;
  cout << "Fitxer? ";
  cin >> fitxer;

  ifstream is(fitxer.c_str());
  if (!is.is_open()) {
    cout << "No s'ha pogut obrir el fitxer '" << fitxer << "'" << endl;
    exit(1);
  }
  
  int nIntervals;
  Hora hInici, hFinal, hTotal;
  is >> nIntervals;
  for (int i = 0; i < nIntervals; i++) {
    is >> hInici >> hFinal;
    hTotal = hTotal + (hFinal - hInici);
  }
  hTotal = hTotal / nIntervals;
  cout << "Temps mig d'interval " << hTotal << endl;
}

