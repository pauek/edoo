
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
using namespace std;

struct Data { int dia, mes, any; };
struct Hora { int hores, minuts, segons; };

struct Truc { 
  Data data; 
  Hora inici, final; 
};

class Trucades {
  map<string, list<Truc> > _dades;
public:
  bool buit() { return _dades.empty(); }
  void comensa(string usuari, Data d, Hora h);
  void acaba(string usuari, Hora h);
  void mostra();
};

void dos_digits(ostream& o, int x) {
  if (x < 10) o << '0' << x;
  else o << x;
}

istream& operator>>(istream& i, Data& d) {
  char c;
  return i >> d.any >> c >> d.mes >> c >> d.dia;
}

ostream& operator<<(ostream& o, Data& d) {
  o << d.any << '/'; 
  dos_digits(o, d.mes);
  o << '/';
  dos_digits(o, d.dia);
  return o;
}

bool operator!=(const Data& a, const Data& b) {
  return a.dia != b.dia || a.mes != b.mes || a.any != b.any;
}

istream& operator>>(istream& i, Hora& h) {
  char c;
  return i >> h.hores >> c >> h.minuts >> c >> h.segons;
}

ostream& operator<<(ostream& o, const Hora& h) {
  dos_digits(o, h.hores);
  o << ':';
  dos_digits(o, h.minuts);
  o << ':';
  dos_digits(o, h.segons);
  return o;
}

void Trucades::comensa(string usuari, Data d, Hora h) {
  map<string, list<Truc> >::iterator i = _dades.find(usuari);
  Truc t;
  t.data = d;
  t.inici = h;
  if (i != _dades.end()) {
    i->second.push_back(t);
  }
  else {
    list<Truc> l;
    l.push_back(t);
    _dades[usuari] = l;
  }
}

void Trucades::acaba(string usuari, Hora h) {
  map<string, list<Truc> >::iterator i = _dades.find(usuari);
  // suposem que el troba segur
  i->second.back().final = h;
}

void Trucades::mostra() {
  map<string, list<Truc> >::iterator i = _dades.begin();
  while (i != _dades.end()) {
    list<Truc>::iterator j;
    cout << "    " << i->first;
    for (j = i->second.begin(); j != i->second.end(); j++) {
      cout << ' ' << j->data << "[" << j->inici << "--" << j->final << "]";
    }
    cout << endl;
    i++;
  }
}

void mostra_dades(vector<Trucades>& T) {
  for (int k = 0; k < T.size(); k++) {
    if (!T[k].buit()) {
      cout << "Ext " << k + 10 << ":" << endl;
      T[k].mostra();
    }
  }
}

int main() {
  vector<Trucades> T(80); // Cada casella és una extensió
  char t; Hora h; Data d; string u; int ext;
  ifstream fin("tel.txt");

  fin >> t >> d >> h >> ext >> u;
  while (!fin.eof()) {
    // Afegeix dades
    int idx = ext - 10; // 10 - 140 ==> 0 - 130
    if (t == '+') 
      T[idx].comensa(u, d, h);
    else if (t == '-') 
      T[idx].acaba(u, h);

    fin >> t >> d >> h >> ext >> u;
  }

  mostra_dades(T);
}
