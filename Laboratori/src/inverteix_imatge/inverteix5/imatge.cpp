
#include <iostream>
#include <cstdlib>
using namespace std;

#include "pixel.h"
#include "imatge.h"

void Imatge::llegeix(istream& in) {
  // Comprova capçalera
  string s;
  getline(in, s);
  if (s[0] != 'P' || s[1] != '3') {
    cout << "Format incorrecte!" << endl;
    exit(1); // aborta el programa amb codi 1
  }
  getline(in, s); // línia de comentari (Gimp)
  
  int nmax;
  in >> tamx >> tamy >> nmax;
  for (int j = 0; j < tamy; j++) {
	 for (int i = 0; i < tamx; i++) {
		pixel[i][j].llegeix(in, nmax);
	 }
  }
}

void Imatge::inverteix() {
  for (int j = 0; j < tamy; j++) {
    for (int i = 0; i < tamx; i++) {
      pixel[i][j].inverteix();
    }
  }
}

void Imatge::escriu(ostream& o) const {
  o << "P3" << endl;
  o << tamx << ' ' << tamy << endl;
  o << BLANC << endl;
  for (int j = 0; j < tamy; j++) {
	 for (int i = 0; i < tamx; i++) {
		pixel[i][j].escriu(o);
	 }
	 o << endl;
  }
}
