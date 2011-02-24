#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

/************************************************
 *                                              *
 *          Fase 1: Fem el TAD Pixel            *
 *                                              *
 ************************************************/

// Tamany màxim de la imatge 
// (si no compila, poseu un valor més petit)
const int XMAX = 500, YMAX = 400;
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

// Imatge ////////////////////////////////////////

struct Imatge {
  int tamx, tamy;
  Pixel pixel[XMAX][YMAX];
};

// main //////////////////////////////////////////

int main() {
  string nomfin, nomfout;
  cout << "Fitxer entrada? ";
  cin >> nomfin;
  cout << "Fitxer sortida? ";
  cin >> nomfout;

  Imatge I;

  // Llegim la imatge en el format PGM
  ifstream fin(nomfin.c_str());

  // Comprova capçalera
  string s;
  getline(fin, s);
  if (s[0] != 'P' || s[1] != '2') {
    cout << "Format incorrecte!" << endl;
    exit(1); // aborta el programa amb codi 1
  }
  getline(fin, s); // línia de comentari (Gimp)
  
  int nmax;
  fin >> I.tamx >> I.tamy >> nmax;
  for (int j = 0; j < I.tamy; j++) {
	 for (int i = 0; i < I.tamx; i++) {
		I.pixel[i][j].llegeix(fin, nmax);
	 }
  }
  
  // Invertim la imatge
  for (int j = 0; j < I.tamy; j++) {
    for (int i = 0; i < I.tamx; i++) {
      I.pixel[i][j].inverteix();
    }
  }

  // Guardem la imatge
  ofstream fout(nomfout.c_str());
  fout << "P2" << endl;
  fout << I.tamx << ' ' << I.tamy << endl;
  fout << BLANC << endl;
  for (int j = 0; j < I.tamy; j++) {
	 for (int i = 0; i < I.tamx; i++) {
		I.pixel[i][j].escriu(fout);
	 }
	 fout << endl;
  }
}

// Local variables:
// compile-command: "gcc -Wall -o i1 inverteix1.cpp -lstdc++"
// End:
