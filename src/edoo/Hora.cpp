
#include "Hora.h"

Hora::Hora() {
  _hores = 0; _minuts = 0; _segons = 0;
}
            
Hora::Hora(int h, int m, int s) {
  _hores = h; _minuts = m; _segons = s;
  _ajusta();
}

Hora::Hora(int segons) {
  _hores = 0; _minuts = 0; _segons = segons;
  _ajusta();
}
            
Hora::Hora(const Hora &h) {
  _hores  = h._hores;
  _minuts = h._minuts;
  _segons = h._segons;
}

int Hora::hores()  const { return _hores; }
int Hora::minuts() const { return _minuts; }
int Hora::segons() const { return _segons; }
   
int Hora::total_segons() const {
  return (_hores * 60 + _minuts) * 60 + _segons;
}

// '_ajusta' posa la hora a valors correctes
// però preserva la quantitat de segons:
// 
//   13:27:90  -> 13:28:30 (0)
//   13:00:125 -> 13:02:05 (0)
//   25:05:-40 -> 01:04:20 (1)
//   00:00:-30 -> 23:59:30 (-1)
//   etc.
//
// Retorna el número de dies que hi havia
//
int Hora::_ajusta() {
  const int UN_DIA = 24 * 60 * 60;

  // Ajuntem les parts (T: Total)
  int T = total_segons();
  
  // traiem els dies
  int dies = T / UN_DIA;
  T = T % UN_DIA;

  if (T < 0) {
    T += UN_DIA;
    // el dia que hem afegit a 'total' el trec de dies.
    dies = dies - 1; 
  }
  
  // Dividim en parts
  _hores  = T / 3600; 
  T = T % 3600;
  _minuts = T / 60;   
  T = T % 60;
  _segons = T;

  return dies;
}

int Hora::avansa(int seg) {
  _segons += seg;
  return _ajusta();
}

Hora Hora::operator+(int segons) const {
  Hora resultat;
  resultat.avansa(segons);
  return resultat;
}
            
Hora Hora::operator-(int segons) const {
  return operator+(-segons);
}

void Hora::operator+=(int segons) { avansa( segons); }
void Hora::operator-=(int segons) { avansa(-segons); }

bool Hora::operator==(const Hora &h) const {
  return total_segons() == h.total_segons();
}

bool Hora::operator!=(const Hora& h) const {
  return !operator==(h);
}

bool Hora::operator<(const Hora &h)  const { return total_segons() <  h.total_segons(); }
bool Hora::operator<=(const Hora &h) const { return total_segons() <= h.total_segons(); }
bool Hora::operator>(const Hora &h)  const { return total_segons() >  h.total_segons(); }
bool Hora::operator>=(const Hora &h) const { return total_segons() >= h.total_segons(); }

void Hora::llegeix(istream& i) {
  char c;
  i >> _hores >> c >> _minuts >> c >> _segons;
}

void Hora::escriu(ostream& o) const {
  if (_hores < 10) cout << 0;
  o << _hores << ':';
  if (_minuts < 10) cout << 0;
  o << _minuts << ':';
  if (_segons < 10) cout << 0;
  o << _segons;
}

istream& operator>>(istream &is, Hora &h) {
  h.llegeix(is);
  return is;
}
            
ostream& operator<<(ostream &os, const Hora &h) {
  h.escriu(os);
  return os;
}
