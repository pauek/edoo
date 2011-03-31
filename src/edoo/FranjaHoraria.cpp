
#include "FranjaHoraria.h"

FranjaHoraria::FranjaHoraria() {}

FranjaHoraria::FranjaHoraria(const DataHora& ini, const DataHora& fin) 
  : _ini(ini), _fin(fin) 
{}

FranjaHoraria::FranjaHoraria(const FranjaHoraria& F) 
  : _ini(F._ini), _fin(F._fin)
{
  if (_fin < _ini) {
	 DataHora tmp = _ini;
	 _ini = _fin;
	 _fin = tmp;
  }
}

void FranjaHoraria::avansa(int segons) {
  _ini.avansa(segons);
  _fin.avansa(segons);
}

bool FranjaHoraria::operator==(const FranjaHoraria& F) const { return _ini == F._ini; }
bool FranjaHoraria::operator!=(const FranjaHoraria& F) const { return _ini != F._ini; }
bool FranjaHoraria::operator< (const FranjaHoraria& F) const { return _ini <  F._ini; }
bool FranjaHoraria::operator<=(const FranjaHoraria& F) const { return _ini <= F._ini; }
bool FranjaHoraria::operator> (const FranjaHoraria& F) const { return _ini >  F._ini; }
bool FranjaHoraria::operator>=(const FranjaHoraria& F) const { return _ini >= F._ini; }

bool FranjaHoraria::a_dins(const DataHora& D) const {
  return _ini <= D && D <= _fin;
}

void FranjaHoraria::llegeix(istream& i) {
  i >> _ini >> _fin;
}

void FranjaHoraria::escriu(ostream& o) const {
  o << _ini << ' ' << _fin;
}

FranjaHoraria FranjaHoraria::interseccio(const FranjaHoraria& F) const {
  FranjaHoraria resultat;
  if (_fin < F._ini || F._fin < _ini) {
	 // No hi ha interseccio
	 return resultat;  
  }
  
  // Màxim inici
  DataHora ini = _ini;
  if (F._ini > ini) ini = F._ini;
  // Mínim final
  DataHora fin = _fin;
  if (F._fin < fin) fin = F._fin;

  resultat._ini = ini;
  resultat._fin = fin;
  return resultat;
}

istream& operator>>(istream& i, FranjaHoraria& F) {
  F.llegeix(i);
  return i;
}

ostream& operator<<(ostream& o, const FranjaHoraria& F) {
  F.escriu(o);
  return o;
}
