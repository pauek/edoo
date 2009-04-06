
#include <sstream>
using namespace std;

#include "imatge.h"


Imatge::Imatge() {
  _pixels = NULL;
  _xtam = _ytam = 0;
}

Imatge::Imatge(int xtam, int ytam) {
  _redimensiona(xtam, ytam);
  _omple_zeros();
}

Imatge::Imatge(const Imatge& I) {
  _copia(I);
}

void Imatge::_redimensiona(int xtam, int ytam) {
  if (_pixels != NULL) {
    delete[] _pixels;
  }
  _pixels = new float[xtam * ytam];
  _xtam = xtam;
  _ytam = ytam;
}

void Imatge::_omple_zeros() {
  int tam = _xtam * _ytam;
  float *p = _pixels;
  for (int k = 0; k < tam; k++) {
    *p = 0.0;
    p++;
  }
}

void Imatge::_copia_pixels(float *pixs, int tam) {
  float *pdest = _pixels, *porig = pixs;
  for (int k = 0; k < tam; k++) {
    *pdest = *porig;
    pdest++; porig++;
  }
}

void Imatge::_copia(const Imatge& I) {
  _redimensiona(I._xtam, I._ytam);
  _copia_pixels(I._pixels, _xtam * _ytam);
}

void Imatge::operator=(const Imatge& I) {
  _copia(I);
}

float Imatge::get_pixel(int x, int y) const {
  return *(_pixels + y * _xtam + x);
}

void Imatge::set_pixel(int x, int y, float val) {
  *(_pixels + y * _xtam + x) = val;
}

void Imatge::inverteix() {
  for (int x = 0; x < _xtam; x++) {
    for (int y = 0; y < _ytam; y++) {
      set_pixel(x, y, 1.0 - get_pixel(x, y));
    }
  }
}

ostream& operator<<(ostream& o, const Imatge& I) {
  // Format PGM
  o << "P2" << endl;
  o << I.tamany_x() << " " << I.tamany_y() << endl;
  o << I._resolucio << endl;

  for (int x = 0; x < I.tamany_x(); x++)
    for (int y = 0; y < I.tamany_y(); y++) 
      o << int(I.get_pixel(x, y) * I._resolucio) << ' ';
}

string llegeix_linia(istream& i) {
  char linia[1000];
  i.getline(linia, 1000);
  // Salta els comentaris (línies que comencen amb '#')
  while (linia[0] == '#') { 
    i.getline(linia, 1000);
  }
  return string(linia);
}

istream& operator>>(istream& i, Imatge& I) {
  string L = llegeix_linia(i);
  if (L == "P2") {
    L = llegeix_linia(i);
    {
      int xtam, ytam;
      istringstream sin(L);
      sin >> xtam >> ytam;
      I._redimensiona(xtam, ytam);
    }

    L = llegeix_linia(i);
    {
      istringstream sin(L);
      sin >> I._resolucio;
    }

    int val;
    for (int x = 0; x < I._xtam; x++) {
      for (int y = 0; y < I._ytam; y++) {
	i >> val;
	I.set_pixel(x, y, float(val) / float(I._resolucio));
      }
    }
  }
}

