
#include <iostream>
#include <fstream>
#include <cstdlib> // per a 'exit'
using namespace std;

// Aquestes són les dimensions màximes de la imatge
// que el programa pot manipula (compte!)
const int XMAX = 200, YMAX = 320;

// Suposem que sempre escrivim amb 255 nivells de gris
const int BLANC = 255;

struct Imatge {
  int tamx, tamy;
  float pixel[XMAX][YMAX];
};

int main() {
  string nomfin, nomfout;
  cout << "Fitxer entrada? ";
  cin >> nomfin;
  cout << "Fitxer sortida? ";
  cin >> nomfout;
  
  Imatge I;
  
  // Llegim la imatge en el format PGM
  ifstream fin(nomfin.c_str());
  
  // Comprova capçalera ("P2")
  string s;
  getline(fin, s);
  if (s[0] != 'P' || s[1] != '2') {
    cout << "Format incorrecte!" << endl;
    exit(1); // aborta el programa amb codi 1
  }
  getline(fin, s); // línia de comentari (Gimp)

  int nmax, px;
  fin >> I.tamx >> I.tamy >> nmax;
  for (int j = 0; j < I.tamy; j++) {
    for (int i = 0; i < I.tamx; i++) {
      fin >> px;
      I.pixel[i][j] = float(px) / float(nmax);
    }
  }
   
  // Invertim la imatge
  for (int j = 0; j < I.tamy; j++) {
    for (int i = 0; i < I.tamx; i++) {
      I.pixel[i][j] = 1.0 - I.pixel[i][j];
    }
  }
   
  // Guardem la imatge
  ofstream fout(nomfout.c_str());
  fout << "P2" << endl;
  fout << I.tamx << ' ' << I.tamy << endl;
  fout << BLANC << endl;
  for (int j = 0; j < I.tamy; j++) {
    for (int i = 0; i < I.tamx; i++) {
      fout << int(I.pixel[i][j] * float(BLANC)) << ' ';
    }
    fout << endl;
  }
}

// Local variables:
// compile-command: "gcc -Wall -o i0 inverteix0.cpp -lstdc++"
// End:
