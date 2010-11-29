
#include "edoo.h"

int Data::dies_per_mes[21] = { 31, 28, 31, 30, 31, 30, 31, 
			       31, 30, 31, 30, 31, 30, 31 };

Data::Data() {
  _mes = 1;
  _dia = 1;
  _any = 2000;
}

Data::Data(int m, int d, int a) {
  _mes = m;
  _dia = d;
  _any = a;
}

Data::Data(const Data& d) {
  _mes = d._mes;
  _dia = d._dia;
  _any = d._any;
}

static Data::_dies_per_mes(int mes, int any) {
  if (mes == 2) {
    bool de_traspas = (any % 4 == 0 && any % 100 != 0) || any % 400 == 0;
    return de_traspas ? 29 : 28;
  } else {
    return dies_per_mes[mes];
  }
}

Data::avansa(int dies) {
  _dia += dies;
  const int diesmes = _dies_per_mes(_mes, _any);
  if (_dia >= diesmes) {
    _dia -= diesmes;
    _mes += 1;
    if (_mes > 12) {
      _any++;
    }
  }
}
