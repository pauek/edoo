#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

/************************************************
 *                                              *
 *          Fase 2: Fem el TAD Imatge           *
 *                                              *
 ************************************************/


const int XMAX = 500, YMAX = 500;
const int BLANC = 255;

// Pixel (TAD) ///////////////////////////////////

struct Pixel {
  float valor;

  void llegeix(istream& i, int nmax);
  void inverteix();
  void escriu(ostream &o) const;
};

void Pixel::llegeix(istream& i, int nmax) {
  int px;
  i >> px;
  valor = float(px) / float(nmax);
}

void Pixel::inverteix() {
  valor = 1.0 - valor;
}

void Pixel::escriu(ostream &o) const {
  o << int(valor * float(BLANC)) << ' ';
}

// Imatge (TAD) //////////////////////////////////

struct Imatge {
  int tamx, tamy;
  Pixel pixel[XMAX][YMAX];

  void llegeix(istream& i);
  void inverteix();
  void escriu(ostream& o) const;
};

void Imatge::llegeix(istream& in) {
  // Comprova capçalera
  string s;
  getline(in, s);
  if (s[0] != 'P' || s[1] != '2') {
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
  o << "P2" << endl;
  o << tamx << ' ' << tamy << endl;
  o << BLANC << endl;
  for (int j = 0; j < tamy; j++) {
	 for (int i = 0; i < tamx; i++) {
		pixel[i][j].escriu(o);
	 }
	 o << endl;
  }
}

// main //////////////////////////////////////////

int main() {
  string nomfin, nomfout;
  cout << "Fitxer entrada? ";
  cin >> nomfin;
  cout << "Fitxer sortida? ";
  cin >> nomfout;

  Imatge I;

  ifstream fin(nomfin.c_str());
  I.llegeix(fin);

  I.inverteix();

  ofstream fout(nomfout.c_str());
  I.escriu(fout);

}

// Local variables:
// compile-command: "gcc -Wall -o i2 inverteix2.cpp -lstdc++"
// End:
