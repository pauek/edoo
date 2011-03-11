
#include <iostream>
using namespace std;

#include "matriu2d.h"

// Constructors //////////////////////////////////////////////////////

Matriu2D::Matriu2D() {
  _x00 = 0.0;
  _x01 = 0.0;
  _x10 = 0.0;
  _x11 = 0.0;
}

Matriu2D::Matriu2D(double x00, double x01, double x10, double x11) {
  _x00 = x00;
  _x01 = x01;
  _x10 = x10;
  _x11 = x11;
}

Matriu2D::Matriu2D(const Matriu2D& M) {
  _x00 = M._x00;
  _x01 = M._x01;
  _x10 = M._x10;
  _x11 = M._x11;
}

// Mètodes Consultors ////////////////////////////////////////////////

double Matriu2D::get00() const { return _x00; }
double Matriu2D::get01() const { return _x01; }
double Matriu2D::get10() const { return _x10; }
double Matriu2D::get11() const { return _x11; }

// Mètodes Modificadors //////////////////////////////////////////////

void Matriu2D::set00(double x) { _x00 = x; }
void Matriu2D::set01(double x) { _x01 = x; }
void Matriu2D::set10(double x) { _x10 = x; }
void Matriu2D::set11(double x) { _x11 = x; }

// Operadors /////////////////////////////////////////////////////////

void Matriu::operator+=(const Matriu& M) {
  _x00 += M._x00;
  _x01 += M._x01;
  _x10 += M._x10;
  _x11 += M._x11;
}

void Matriu::operator-=(const Matriu& M) {
  _x00 -= M._x00;
  _x01 -= M._x01;
  _x10 -= M._x10;
  _x11 -= M._x11;
}

/*

  ( a b ) * ( e f ) = (  a*e + b*g   a*f + b*h  )
  ( c d )   ( g h )   (  c*e + d*g   c*f + d*h  )

 */

void Matriu::operator*=(const Matriu& M) {
  double a = _x00, b = _x01, c = _x10, d = _x11;
  double e = M._x00, f = M.x01, g = M._x10, h = M._x11;
  _x00 = a*e + b*g;
  _x01 = a*f + b*h;
  _x10 = c*e + d*g;
  _x11 = c*f + d*h;
}

Matriu Matriu::operator+(const Matriu& M) const {
  Matriu2D resultat(_x00, _x01, _x10, _x11);
  resultat += M;
  return resultat;
}

Matriu Matriu::operator-(const Matriu& M) const {
  Matriu2D resultat(_x00, _x01, _x10, _x11);
  resultat -= M;
  return resultat;
}

Matriu Matriu::operator*(const Matriu& M) const {
  Matriu2D resultat(_x00, _x01, _x10, _x11);
  resultat *= M;
  return resultat;
}

bool Matriu::operator==(const Matriu& M) const {
  return 
    _x00 == M._x00 && _x01 == M._x01 && 
    _x10 == M._x10 && _x11 == M._x11;
}

bool Matriu::operator!=(const Matriu& M) const {
  return !operator==(M);
}

// Entrada/Sortida ///////////////////////////////////////////////////

// Format (tipus Matlab): 
//
//    [ a, b; c, d ]
//

istream& operator>>(istream& i, Matriu2D& M) {
  double a, b, c, d;
  char _;
  //     [    a    ,    b    ;    c    ,    d    ]
  cin >> _ >> a >> _ >> b >> _ >> c >> _ >> d >> _;
  // ... no comprovem que els caracters siguin 
  // els que tocaria a cada lloc...
  M.set00(a); M.set01(b);
  M.set10(c); M.set11(d);
  return i;
}

ostream& operator<<(ostream& o, const Matriu2D& M) {
  o << "[ " << M.get00() << ", " << M.get01() 
    << "; " << M.get10() << ", " << M.get11() << "]";
  return o;
}
