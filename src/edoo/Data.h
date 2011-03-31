
#ifndef DATA_H
#define DATA_H

#include <iostream>
using namespace std;

class Data {
  int _dia, _mes, _any;

public:
  Data();
  Data(int d, int m, int a);
  Data(const Data& d);

  // Mètodes consultors
  int dia() const;
  int mes() const;
  int any() const;

  // Mètodes modificadors
  void reset(int d, int m, int a); // canvia els 3 alhora

  // Operadors
  Data operator+(int i) const; // sumar  un enter a una data
  Data operator-(int i) const; // restar un enter a una data
  void operator+=(int i); // suma modificadora
  void operator-=(int i); // resta modificadora

  bool operator>(const Data& d) const;
  bool operator<(const Data& d) const;
  bool operator>=(const Data& d) const;
  bool operator<=(const Data& d) const;
  bool operator==(const Data& d) const;
  bool operator!=(const Data& d) const;
};

istream& operator>>(istream& i, Data& d);
ostream& operator<<(ostream& o, const Data& d);

#endif
