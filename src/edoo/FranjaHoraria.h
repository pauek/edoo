
#ifndef FRANJAHORARIA_H
#define FRANJAHORARIA_H

#include "DataHora.h"

class FranjaHoraria {
  DataHora _ini, _fin;
public:
  FranjaHoraria();
  FranjaHoraria(const FranjaHoraria& F);
  FranjaHoraria(const DataHora& ini, const DataHora& fin);

  void avansa(int segons);
  
  bool operator==(const FranjaHoraria& F) const;
  bool operator!=(const FranjaHoraria& F) const;  
  bool operator< (const FranjaHoraria& F) const;  
  bool operator<=(const FranjaHoraria& F) const;  
  bool operator> (const FranjaHoraria& F) const;  
  bool operator>=(const FranjaHoraria& F) const;  

  bool a_dins(const DataHora& D) const;

  void llegeix(istream& i);
  void escriu(ostream& o) const;

  FranjaHoraria interseccio(const FranjaHoraria& F) const;
};

istream& operator>>(istream& i, FranjaHoraria& F);
ostream& operator<<(ostream& o, const FranjaHoraria& F);

#endif
