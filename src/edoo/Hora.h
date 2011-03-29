#ifndef HORA_H
#define HORA_H

#include <iostream>
using namespace std;

class Hora {
  int _hores, _minuts, _segons;
      
public:
  Hora();
  Hora(int h, int m, int s);
  Hora(const Hora &hora);

  // Constructor per un número de segons totals
  Hora(int segons);

  // Mètodes consultors
  int hores()  const;
  int minuts() const;
  int segons() const;

  // Força uns valors concrets
  void reset(int h, int m, int s);

  // Avança un número de segons i retorna
  // quants dies han passat (també funciona per
  // segons negatius)
  int avansa(int segons); 

  // Total en segons (01:02:05 -> 3725)
  int total_segons() const;
  
  // Sumem o restem un número de segons al temps
  Hora operator+(int segons) const;
  Hora operator-(int segons) const;
  void operator+=(int segons);
  void operator-=(int segons);

  void llegeix(istream& i);
  void escriu(ostream& o) const;
       
  bool operator==(const Hora &h1) const;
  bool operator!=(const Hora &h1) const;
  bool operator<(const Hora &h1) const;
  bool operator<=(const Hora &h1) const;
  bool operator>(const Hora &h1) const;
  bool operator>=(const Hora &h1) const;
       
private:
  int _ajusta();     
};

istream& operator>>(istream &is, Hora &h);
ostream& operator<<(ostream &os, const Hora &h);

#endif // _HORA_INCLUDE
