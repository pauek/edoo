#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

const int XMAX = 320, YMAX = 400;
const int BLANC = 255;

struct Pixel {
  float valor;

  void llegeix(istream& i, int nmax);
  void inverteix();
  void escriu(ostream &o);
};

void Pixel::llegeix(istream& i, int nmax) {
  int px;
  i >> px;
  valor = float(px) / float(nmax);
}

void Pixel::inverteix()
{
  valor = 1.0 - valor;
}

void Pixel::escriu(ostream &o)
{
  o << int(valor * float(BLANC)) << ' ';
}

struct Imatge {
  int tamx, tamy;
  Pixel pixel[XMAX][YMAX];
  
  Imatge();
  Imatge(const Imatge &img);
};

Imatge::Imatge()
{
}

Imatge::Imatge(const Imatge &img)
{
  int i, j;
  
  tamx = img.tamx;
  tamy = img.tamy;
  for(i=0; i<img.tamx; i++)
    for(j=0; j<img.tamy; j++)
      pixel[i][j].valor = img.pixel[i][j].valor;
}


int main() {
  string nomfin, nomfout;
  cout << "Fitxer entrada? ";
  cin >> nomfin;
  cout << "Fitxer sortida? ";
  cin >> nomfout;

  Imatge I;

  // Llegim la imatge en el format PGM
  {
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
        I.pixel[i][j].llegeix(fin, nmax);
      }
    }
  }
  
  Imatge img2(I);

  // Invertim la imatge
  for (int j = 0; j < I.tamy; j++) {
    for (int i = 0; i < I.tamx; i++) {
      I.pixel[i][j].inverteix();
    }
  }

  // Guardem la imatge
  {
    ofstream fout(nomfout.c_str());
    fout << "P2" << endl;
    fout << I.tamx << ' ' << I.tamy << endl;
    fout << 255 << endl;
    for (int j = 0; j < I.tamy; j++) {
      for (int i = 0; i < I.tamx; i++) {
        I.pixel[i][j].escriu(fout);
      }
      fout << endl;
    }
  }
}

