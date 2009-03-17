#ifndef _HORA_INCLUDE
#define _HORA_INCLUDE

#include <iostream>
using namespace std;

class Hora {
  int hores, minuts, segons;
      
public:
  Hora();
  Hora(int h, int m, int s);
  Hora(const Hora &hora);
       
  friend Hora operator+(const Hora &h1, const Hora &h2);
  friend Hora operator-(const Hora &h1, const Hora &h2);
  friend Hora operator/(const Hora &h1, const int s);
       
  friend bool operator==(const Hora &h1, const Hora &h2);
  friend bool operator!=(const Hora &h1, const Hora &h2);
  friend bool operator<(const Hora &h1, const Hora &h2);
  friend bool operator>(const Hora &h1, const Hora &h2);
       
  friend istream& operator>>(istream &is, Hora &h);
  friend ostream& operator<<(ostream &os, Hora &h);
       
private:
  void AjustaHora();     
};

#endif // _HORA_INCLUDE

