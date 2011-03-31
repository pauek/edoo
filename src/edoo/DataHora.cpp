
#include "DataHora.h"

DataHora::DataHora() {}

DataHora::DataHora(int d, int m, int a, int H, int M, int S) 
  : _data(d, m, a), _hora(H, M, S)
{}

DataHora::DataHora(const Data& d, const Hora& h)
  : _data(d), _hora(h)
{}

DataHora::DataHora(const DataHora& D) 
  : _data(D._data), _hora(D._hora)
{}


void DataHora::avansa(int segons) {
  int dies = _hora.avansa(segons);
  _data += dies;
}

bool DataHora::operator==(const DataHora& D) const {
  return _data == D._data && _hora == D._hora;
}

bool DataHora::operator!=(const DataHora& D) const {
  return ! operator==(D);
}

bool DataHora::operator<(const DataHora& D) const {
  if (_data != D._data) {
	 return _data < D._data;
  } else {
	 return _hora < D._hora;
  }
}

bool DataHora::operator>=(const DataHora& D) const {
  return ! operator<(D);
}

bool DataHora::operator>(const DataHora& D) const {
  if (_data != D._data) {
	 return _data > D._data;
  } else {
	 return _hora > D._hora;
  }
}

bool DataHora::operator<=(const DataHora& D) const {
  return ! operator>(D);
}

void DataHora::llegeix(istream& i) {
  char c;
  i >> _data >> c >> _hora;
}

void DataHora::escriu(ostream& o) const {
  o << _data << '-' << _hora;
}

istream& operator>>(istream& i, DataHora& D) {
  D.llegeix(i);
  return i;
}

ostream& operator<<(ostream& o, const DataHora& D) {
  D.escriu(o);
  return o;
}

