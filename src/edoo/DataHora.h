
#ifndef DATAHORA_H
#define DATAHORA_H

#include "Data.h"
#include "Hora.h"

class DataHora {
  Data _data;
  Hora _hora;
public:
  DataHora();
  DataHora(int d, int m, int a, int H, int M, int S);
  DataHora(const Data& d, const Hora& h);
  DataHora(const DataHora& D);

  void avansa(int segons);

  bool operator==(const DataHora& d) const;
  bool operator!=(const DataHora& d) const;
  bool operator< (const DataHora& d) const;
  bool operator> (const DataHora& d) const;
  bool operator<=(const DataHora& d) const;
  bool operator>=(const DataHora& d) const;
  
  void llegeix(istream& i);
  void escriu(ostream& o) const;
};

istream& operator>>(istream& i, DataHora& D);
ostream& operator<<(ostream& o, const DataHora& D);

#endif
