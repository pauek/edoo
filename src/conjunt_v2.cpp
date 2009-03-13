
// Conjunt implementat amb una taula de Booelans

#include <iostream>
using namespace std;

const int N = 1000;

class Conjunt {
  bool _elem[N];
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
  for (int k = 0; k < N; k++) 
    _elem[k] = false;
}

Conjunt::Conjunt(const Conjunt& C) {
  for (int i = 0; i < N; i++) {
    _elem[i] = C._elem[i];
  }
}

void Conjunt::afegeix(int n) {
  if (n >= 0 && n < 1000)
    _elem[n] = true;
}

void Conjunt::elimina(int n) {
  if (n >= 0 && n < 1000)
    _elem[n] = false;
}

bool Conjunt::pertany(int n) const {
  return _elem[n];
}

int Conjunt::tamany() const {
  int k, cont = 0;
  for (k = 0; k < N; k++) {
    if (_elem[k]) cont++;
  }
  return cont;
}

void Conjunt::afegeix_tots(const Conjunt& C) {
  for (int i = 0; i < N; i++)
    if (C.pertany(i)) afegeix(i);
}

void Conjunt::elimina_tots(const Conjunt& C) {
  for (int i = 0; i < N; i++)
    if (C.pertany(i)) elimina(C._elem[i]);
}

bool Conjunt::igual(const Conjunt& C) const {
  for (int k = 0; k < N; k++) {
    if (_elem[k] != C._elem[k]) return false;
  }
  return true;
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
