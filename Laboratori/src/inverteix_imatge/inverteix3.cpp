#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

/************************************************
 *                                              *
 *          Fase 3: Passem a color              *
 *                                              *
 ************************************************/


const int XMAX = 500, YMAX = 500;
const int BLANC = 255;

// Pixel en color (TAD) //////////////////////////

// canvis: posar 3 camps, retocar tots els mètodes

struct Pixel {
  float red, green, blue;

  void llegeix(istream& i, int nmax);
  void inverteix();
  void escriu(ostream &o) const;
};

void Pixel::llegeix(istream& i, int nmax) {
  int r, g, b;
  i >> r >> g >> b;
  red = float(r) / float(nmax);
  red = float(g) / float(nmax);
  red = float(b) / float(nmax);
}

void Pixel::inverteix() {
  red   = 1.0 - red;
  green = 1.0 - green;
  blue  = 1.0 - blue;
}

void Pixel::escriu(ostream &o) const {
  o << int(red   * float(BLANC)) << ' '
	 << int(green * float(BLANC)) << ' '
	 << int(blue  * float(BLANC)) << "  ";
}

// Imatge (TAD) //////////////////////////////////

// canvis: - "P2" ==> "P3" (lectura i escriptura)

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
// compile-command: "gcc -Wall -o i3 inverteix3.cpp -lstdc++"
// End:
