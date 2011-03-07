#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

#include "pixel.h"
#include "imatge.h"

// Utilitats ////////////////////////////////////

string nom_fitxer_de_sortida(string nom) {
  string copia = nom;
  size_t pos = copia.find_last_of(".");
  if (pos != string::npos) {
    copia.insert(pos, "_i");
  }
  return copia;
}

bool es_fitxer_ppm(string nom) {
  size_t pos = nom.find_last_of(".");
  if (pos == string::npos) {
    return false;
  }
  return nom.find("ppm", pos + 1) != 0;
}

// main //////////////////////////////////////////

int main() {
  string nomfin;
  cout << "Fitxer entrada? ";
  cin >> nomfin;

  // Comproba que el fitxer és PPM
  if (!es_fitxer_ppm(nomfin)) {
    cout << "El fitxer '" << nomfin 
	 << "' no és un PPM" << endl;
    exit(1);
  }

  Imatge I;

  ifstream fin(nomfin.c_str());
  if (!fin.is_open()) {
    cout << "No s'ha pogut llegir el fitxer \"" 
	 << nomfin << "\"" << endl;
    exit(1);
  }
  I.llegeix(fin);

  I.inverteix();

  string nomfout = nom_fitxer_de_sortida(nomfin);
  ofstream fout(nomfout.c_str());
  if (!fout.is_open()) {
    cout << "No s'ha pogut escriure el fitxer \"" 
	 << nomfout << "\"" << endl;
    exit(1);
  }
  I.escriu(fout);
}

// Local variables:
// compile-command: "gcc -Wall -o i5 inverteix.cpp  -lstdc++"
// End:
