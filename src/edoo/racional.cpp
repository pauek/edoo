
#include <iostream>
using namespace std;

#include "racional.h"

// Utilitats /////////////////////////////////////////////////////////

// Algorisme d'Euclides: 
// http://ca.wikipedia.org/wiki/Algorisme_d'Euclides
int maxim_comu_divisor(int a, int b) {
  while (b != 0) {
	 int t = b;
	 b = a % b;
	 a = t;
  }
  return a;
}

// Constructors //////////////////////////////////////////////////////

Racional::Racional() {
  _num = 0;
  _den = 1;
}

Racional::Racional(int n, int d) {
  _num = n;
  _den = d;
  redueix();
}

Racional::Racional(const Racional& r) {
  _num = r._num;
  _den = r._den;
}

// Mètodes consultors ////////////////////////////////////////////////

int Racional::num() const { return _num; }
int Racional::den() const { return _den; }

// Mètodes modificadors //////////////////////////////////////////////

void Racional::redueix() {
  int mcd = maxim_comu_divisor(_num, _den);
  _num /= mcd;
  _den /= mcd;
  if (_den < 0 && _num > 0) {
	 _num = -_num;
	 _den = -_den;
  }
}

void Racional::set(int n, int d) {
  _num = n;
  _den = d;
  redueix();
}

void Racional::setnum(int n) {
  _num = n;
  redueix();
}

void Racional::setden(int d) {
  _den = d;
  redueix();
}

// Operadors /////////////////////////////////////////////////////////

void Racional::operator+=(const Racional& r) {
  int a = _num, b = _den, c = r._num, d = r._den;
  _num = a*d + b*c;
  _den = b*d;
  redueix();
}

void Racional::operator-=(const Racional& r) {
  int a = _num, b = _den, c = r._num, d = r._den;
  _num = a*d - b*c;
  _den = b*d;
  redueix();
}

void Racional::operator*=(const Racional& r) {
  int a = _num, b = _den, c = r._num, d = r._den;
  _num = a*c;
  _den = b*d;
  redueix();
}

void Racional::operator/=(const Racional& r) {
  int a = _num, b = _den, c = r._num, d = r._den;
  _num = a*d;
  _den = b*c;
  redueix();
}

// Fem servir '+=' per implementar '+', '-=' per fer '-', etc.

Racional Racional::operator+(const Racional& r) const {
  Racional suma(_num, _den);
  suma += r;
  return suma;
}

Racional Racional::operator-(const Racional& r) const {
  Racional suma(_num, _den);
  suma -= r;
  return suma;
}

Racional Racional::operator*(const Racional& r) const {
  Racional suma(_num, _den);
  suma *= r;
  return suma;
}

Racional Racional::operator/(const Racional& r) const {
  Racional suma(_num, _den);
  suma /= r;
  return suma;
}


// Operacions amb enters /////////////////////////////////////////////

// Creem un racional a partir de l'enter (posem denominador 1)
// i apliquem les operacions que ja tenim fetes... ;)

Racional Racional::operator+(int i) const {
  Racional r(i, 1);
  return operator+(r);
}

Racional Racional::operator-(int i) const {
  Racional r(i, 1);
  return operator-(r);
}

Racional Racional::operator*(int i) const {
  Racional r(i, 1);
  return operator*(r);
}

Racional Racional::operator/(int i) const {
  Racional r(i, 1);
  return operator/(r);
}

// Operacions de comparació //////////////////////////////////////////

bool Racional::operator<(const Racional& r) const {
  int a = _num, b = _den, c = r._num, d = r._den;
  return a*d < b*c;
}

bool Racional::operator>=(const Racional& r) const {
  return !operator<(r);
}

bool Racional::operator>(const Racional& r) const {
  int a = _num, b = _den, c = r._num, d = r._den;
  return a*d > b*c;
}

bool Racional::operator<=(const Racional& r) const {
  return !operator>(r);
}

bool Racional::operator==(const Racional& r) const {
  int a = _num, b = _den, c = r._num, d = r._den;
  return a*d == b*c;
}

bool Racional::operator!=(const Racional& r) const {
  return !operator==(r);
}

// Operacions d'Entrada/Sortida //////////////////////////////////////

istream& operator>>(istream& i, Racional& r) {
  int n, d;
  char barra;
  i >> n >> barra >> d;
  r.set(n, d);
}

ostream& operator<<(ostream& o, const Racional& r) {
  o << r.num() << '/' << r.den();
}

