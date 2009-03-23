
#include <iostream>
using namespace std;

class Frase {
  char *_inici, *_capsal;
  int _tam, _ple;
public:
  Frase(int llarg);
  ~Frase();
  void afegeix(string s);
};

Frase::Frase(int llarg) {
  _inici = _capsal = new char[llarg];
  _tam = llarg;
  _ple = 0;
}

Frase::~Frase() {
  delete[] _inici;
}

void Frase::afegeix(string s) {
  if (_ple + s.size() < _tam) {
    for (int k = 0; k < s.size(); k++) {
      *_capsal = s[k];
      _capsal++;
      _ple++;
    }
  }
}

int main() {
  Frase f1(250);
  f1.afegeix("The best way to predict the future is to invent it");
  Frase f2(f1);
}
