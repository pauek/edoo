
#include <iostream>
using namespace std;

#include "Data.h"

// Utilitats /////////////////////////////////////////////////////////

bool de_traspas(int any) {
  return (any % 4 == 0 && any % 100 != 0) || any % 400 == 0;
}

int dies_mes(int mes, int any) {
  // Taula amb els dies precalculats
  int T_dies_mes[12] = { 
	 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
  };
  int resultat = T_dies_mes[mes - 1];
  if (mes == 2 && de_traspas(any)) {
	 resultat = 29;
  }
  return resultat;
}

void mes_anterior(int& mes, int& any) {
  if (mes > 1) {
	 mes--;
  } else {
	 mes = 12;
	 any--;
  }
}

// Constructors //////////////////////////////////////////////////////

Data::Data() {
  _dia = 1;
  _mes = 1;
  _any = 2000;
}

Data::Data(int d, int m, int a) {
  // S'hauria de mirar si 0 < m <= 12 i 0 < d <= 31
  _dia = d;
  _mes = m;
  _any = a;
}

Data::Data(const Data& d) {
  _dia = d._dia;
  _mes = d._mes;
  _any = d._any;
}

// Mètodes consultors ///////////////////////////////////////////////

int Data::dia() const { return _dia; }
int Data::mes() const { return _mes; }
int Data::any() const { return _any; }

// Mètodes modificadors /////////////////////////////////////////////

void Data::reset(int d, int m, int a) {
  // 'reset' és com el constructor 
  // però l'objecte ja existia...
  _dia = d;
  _mes = m;
  _any = a;
  // Per evitar duplicació es podria cridar 'reset' al constructor...
}

// Operadors /////////////////////////////////////////////////////////

// Avancem una data un número de dies
Data Data::operator+(int dies) const {
  // Fem copia dels valors dels atributs (per no canviar-los)
  int d = _dia, m = _mes, a = _any;
  d += dies; 
  int max = dies_mes(m, a);
  while (d > max) {
    d -= max;
    m++;
    if (m > 12) {
      m = 1;
      a++;
    }
    max = dies_mes(m, a);
  }
  Data resultat(d, m, a); 
  return resultat;
}

// Retrocedim una data un número de dies
Data Data::operator-(int dies) const {
  int d = _dia, m = _mes, a = _any;
  d -= dies;
  while (d < 1) {
	 mes_anterior(m, a);
	 d += dies_mes(m, a);
  }
  Data resultat(d, m, a);
  return resultat;
}

bool Data::operator>(const Data& altra) const {
  if (_any != altra._any) {
    return (_any > altra._any);
  } else if (_mes != altra._mes) {
    return (_mes > altra._mes);
  } else {
    return (_dia > altra._dia);
  }  
}

bool Data::operator==(const Data& altra) const {
  return 
    _any == altra._any && 
    _mes == altra._mes && 
    _dia == altra._dia;
}

// A partir d'aquí podem aprofitar els operadors '+', '-', '>' i '==' 
// que ja tenim per fer els que queden...

void Data::operator+=(int dies) {
  Data res = operator+(dies);
  _dia = res._dia;
  _mes = res._mes;
  _any = res._any;
} 

void Data::operator-=(int dies) {
  Data res = operator-(dies);
  _dia = res._dia;
  _mes = res._mes;
  _any = res._any;
}

bool Data::operator<(const Data& altra) const {
  return !operator>(altra) && !operator==(altra);
}

bool Data::operator>=(const Data& altra) const {
  return operator>(altra) || operator==(altra);
}

bool Data::operator<=(const Data& altra) const {
  return operator<(altra) || operator==(altra);
}

bool Data::operator!=(const Data& altra) const {
  return !operator==(altra);
}

// Entrada/Sortida ///////////////////////////////////////////////////

istream& operator>>(istream& i, Data& data) {
  // Format: 20/11/1975
  int d, m, a;
  char barra; // per llegir la barra: '/'
  i >> d >> barra >> m >> barra >> a;
  data.reset(d, m, a);
  return i;
}

ostream& operator<<(ostream& o, const Data& d) {
  o << d.dia() << '/' << d.mes() << '/' << d.any();
  return o;
}
