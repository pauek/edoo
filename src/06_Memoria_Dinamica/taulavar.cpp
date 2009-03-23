
#include "taulavar.h"

// _1+
Taulavar::Taulavar() {
  _dades = NULL;
  _max = _tam = 0;
}
// _1-

// _2+
Taulavar::Taulavar(int tamany) {
  _dades = new int[tamany];
  _max = _tam = tamany;
  int *p = _dades;
  for (int k = 0; k < tamany; k++) {
    *p = 0;
    p++;
  }
}
// _2-

// _3+
void Taulavar::_copia_dades(int *porig, int *pdest, int N) {
  for (int k = 0; k < N; k++) {
    *pdest = *porig;
    pdest++; porig++;
  }
}

void Taulavar::_copia(const Taulavar& T) {
  _dades = new int[T._max];
  _max = T._max;
  _tam = T._tam;
  _copia_dades(T._dades, _dades, _tam);
}
// _3-

// _5+
Taulavar::Taulavar(const Taulavar& T) {
  _copia(T);
}

void Taulavar::operator=(const Taulavar& T) {
  if (_dades != NULL) delete[] _dades;
  _copia(T);
}
// _5-

// _6+
int Taulavar::tamany() const {
  return _tam;
}

int Taulavar::get(int k) const {
  if (k >= _tam) {
    cout << "get: " << k << " > tamany!" << endl;
    return -1;
  }
  return *(_dades + k);
}

int Taulavar::set(int k, int val) {
  if (k >= _tam) {
    cout << "set: " << k << " > tamany!" << endl;
  } else {
    *(_dades + k) = val;
  }
}
// _6-

// _7+
void Taulavar::redimensiona(int noutam) {
  if (noutam > _max) {
    int *novesdades = new int[noutam];
    _copia_dades(_dades, novesdades, _tam);
    delete[] _dades;
    _dades = novesdades;
    _max = noutam;
  }
  else if (_tam < noutam) {
    _tam = noutam;
  }
}
// _7-

// _8+
int Taulavar::afegeix(int val) {
  if (_tam == _max) {
    redimensiona(_max * 2);
  }
  int ult = _tam;
  _tam++;
  *(_dades + ult) = val;
  return ult;
}
// _8-
