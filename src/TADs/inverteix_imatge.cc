
#include <iostream>
#include <fstream>
#include <cstdlib> // per a 'exit'
using namespace std;

const int XMAX = 320, YMAX = 200;
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
  
  // Comprova capçalera
  string s;
  fin >> s;
  if (s != "P2") {
	 cout << "Format incorrecte!" << endl;
	 exit(1); // aborta el programa amb codi 1
  }

  int x, y, nmax, px;
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
  fout << 255 << endl;
  for (int j = 0; j < I.tamy; j++) {
	 for (int i = 0; i < I.tamx; i++) {
		fout << int(I.pixel[i][j] * float(BLANC)) << ' ';
	 }
	 fout << endl;
  }
}

// Local variables:
// compile-command: "gcc -o ii inverteix_imatge.cc -lstdc++"
// End:
