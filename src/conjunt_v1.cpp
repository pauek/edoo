
#include <iostream>
using namespace std;

class Conjunt {
  int _elem[1000];
  int _nelem;

  void _inserta(int n, int pos);
  void _esborra(int pos);
  int  _cerca(int n) const;

public:
  Conjunt(); // c. per defecte
  Conjunt(const Conjunt& C); // c. de còpia

  void afegeix(int n);
  void elimina(int n);
  bool pertany(int n) const;
  int  tamany() const;
  void afegeix_tots(const Conjunt& C);
  void elimina_tots(const Conjunt& C);
  bool igual(const Conjunt& C) const;
};

Conjunt::Conjunt() {
  _nelem = 0;
}

Conjunt::Conjunt(const Conjunt& C) {
  for (int i = 0; i < C._nelem; i++) {
    _elem[i] = C._elem[i];
  }
  _nelem = C._nelem;
}

void Conjunt::_inserta(int n, int pos) {
  for (int k = _nelem; k > pos; k--) {
    _elem[k+1] = _elem[k];
  }
  _elem[pos] = n;
  _nelem++;
}

void Conjunt::_esborra(int pos) {
  for (int k = pos; k < _nelem - 1; k++) {
    _elem[k] = _elem[k+1];
  }
  _nelem--;
}

// Retornem la posició de l'element major o igual que 'n'
// [Cerca linial, potser podria ser binària]
int Conjunt::_cerca(int n) const {
  int k = 0;
  while (k < _nelem && _elem[k] < n) {
    k++;
  }
  return k;
}

void Conjunt::afegeix(int n) {
  int pos = _cerca(n);
  if (_elem[pos] != n) {
    _inserta(n, pos);
  }
}

void Conjunt::elimina(int n) {
  int pos = _cerca(n);
  if (_elem[pos] == n) {
    _esborra(pos);
  }
}

bool Conjunt::pertany(int n) const {
  int pos = _cerca(n);
  return _elem[pos] == n;
}

int Conjunt::tamany() const {
  return _nelem;
}

void Conjunt::afegeix_tots(const Conjunt& C) {
  for (int i = 0; i < C._nelem; i++)
    afegeix(C._elem[i]);
}

void Conjunt::elimina_tots(const Conjunt& C) {
  for (int i = 0; i < C._nelem; i++)
    elimina(C._elem[i]);
}

bool Conjunt::igual(const Conjunt& C) const {
  bool iguals = true;
  int k = 0;
  while (k < _nelem && k < C._nelem && iguals) {	
    if (_elem[k] != C._elem[k]) {	 
      iguals = false;
    }
    else k++;
  }
  return iguals;
}

// Programa principal per provar

int main() {
  Conjunt C, D;
  C.afegeix(5);
  C.afegeix(10);
  C.afegeix(15);

  D.afegeix_tots(C);

  cout << C.igual(D) << endl;
  cout << D.igual(C) << endl;

  cout << C.pertany(5) << C.pertany(10) << C.pertany(15) << endl;
  cout << D.pertany(5) << D.pertany(10) << D.pertany(15) << endl;

  cout << C.pertany(2) << C.pertany(4) << C.pertany(20) << endl;
  cout << D.pertany(2) << D.pertany(4) << D.pertany(20) << endl;
}
