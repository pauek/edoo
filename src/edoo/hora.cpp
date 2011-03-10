#include "Hora.h"

Hora::Hora() {
  segons = 0;
  minuts = 0;
  hores = 0;
}
            
Hora::Hora(int h, int m, int s) {
  segons = s;
  minuts = m;
  hores = h;
  AjustaHora();
}
            
Hora::Hora(const Hora &hora) {
  segons = hora.segons;
  minuts = hora.minuts;
  hores = hora.hores;
}
            
void Hora::AjustaHora() {
  hores += segons /3600;
  segons = segons % 3600;
  minuts += segons /60;
  segons = segons % 60;
  hores += minuts / 60;
  minuts = minuts % 60;
}

Hora operator+(const Hora &h1, const Hora &h2) {
  Hora hora;
  
  hora.segons = h1.segons + h2.segons;
  hora.minuts = h1.minuts + h2.minuts;
  hora.hores = h1.hores + h2.hores;
  hora.AjustaHora();
  
  return hora;
}
            
Hora operator-(const Hora &h1, const Hora &h2) {
  Hora hora;
  
  hora.segons = 3600 * h1.hores + 60 * h1.minuts + h1.segons;
  hora.segons -= 3600 * h2.hores + 60 * h2.minuts + h2.segons;
  hora.minuts = 0;
  hora.hores = 0;
  hora.AjustaHora();
  
  return hora;
}
            
Hora operator/(const Hora &h1, const int s) {
  Hora hora;
  
  hora.segons = (3600 * h1.hores + 60 * h1.minuts + h1.segons) / s;
  hora.minuts = 0;
  hora.hores = 0;
  hora.AjustaHora();
  
  return hora;
}
            

bool operator==(const Hora &h1, const Hora &h2) {
  return (h1.segons == h2.segons) && 
    (h1.minuts == h2.minuts) && 
    (h1.hores == h2.hores);
}

bool operator!=(const Hora &h1, const Hora &h2) {
  return (h1.segons != h2.segons) || 
    (h1.minuts != h2.minuts) || 
    (h1.hores != h2.hores);
}

bool operator<(const Hora &h1, const Hora &h2) {
  return (h1.hores < h2.hores) || 
    ((h1.hores == h2.hores) && (h1.minuts < h2.minuts)) ||
    ((h1.hores == h2.hores) && (h1.minuts == h2.minuts) && (h1.segons < h2.segons));
}

bool operator>(const Hora &h1, const Hora &h2) {
  return (h1.hores > h2.hores) || 
    ((h1.hores == h2.hores) && (h1.minuts > h2.minuts)) ||
    ((h1.hores == h2.hores) && (h1.minuts == h2.minuts) && (h1.segons > h2.segons));
}

istream& operator>>(istream &is, Hora &h) {
  is >> h.hores;
  is >> h.minuts;
  is >> h.segons;
  h.AjustaHora();
  return is;
}
            
ostream& operator<<(ostream &os, Hora &h) {
  os << h.hores << " hores ";
  os << h.minuts << " minuts ";
  os << h.segons << " segons";
  return os;
}
