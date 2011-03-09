
// #include "taula.h"

// 1+
Taula::Taula() {
  _p_reals = 0;
  _tamany = 0;    
}
// 1-

// 2+
Taula::Taula(int tamany) {
  _tamany = tamany;
  _p_reals = new double[_tamany];
  for (int i = 0; i < _tamany; i++) {
    _p_reals[i] = 0.0;
  }    
}
// 2-

// 3+
Taula::Taula(int tamany, double valor) {
  _tamany = tamany;
  _p_reals = new double[_tamany];
  for (int i = 0; i < _tamany; i++) {
    _p_reals[i] = valor;
  }    
}
// 3-

// 4+
Taula::Taula(const Taula& altra) {
  _tamany = altra._tamany;
  _p_reals = new double[_tamany];
  for (int i = 0; i < _tamany; i++) {
    _p_reals[i] = altra._p_reals[i];
  }    
}
// 4-

// 5+
int Taula::tamany() const {
  return _tamany;
}
// 5-

// 6+
double Taula::get(int n) const {
  // Falta comprovar que _p_reals no és 0
  // i que n està en el rang correcte.
  return _p_reals[n];
}

void Taula::set(int n, double valor) {
  // Falta comprovar que _p_reals no és 0
  // i que n està en el rang correcte.
  _p_reals[n] = valor;
}
// 6-

