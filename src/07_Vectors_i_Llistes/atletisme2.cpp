
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct Dorsal {
  double ultim, anterior, millor;
  Dorsal() { ultim = -1.0; }
  void afegeix_crono(double crono);
};

void Dorsal::afegeix_crono(double crono) {
  if (ultim < 0.0) {
    ultim = millor = crono;
    anterior = 0.0;
  }
  else {
    anterior = ultim;
    ultim = crono;
    if (ultim - anterior < millor) {
      millor = ultim - anterior;
    }
  }
}

int main() {
  vector<Dorsal> temps(25);
  int dorsal;
  double crono;

  ifstream fin("cursa.txt");
  fin >> dorsal >> crono;
  while (!fin.eof()) {
    temps[dorsal].afegeix_crono(crono);
    fin >> dorsal >> crono;
  }

  int guanyador = 0;
  double millor = temps[0].ultim;
  for (int k = 1; k < 25; k++) {
    if (temps[k].ultim < millor) {
      millor = temps[k].ultim;
      guanyador = k;
    }
  }

  cout << "Dorsal guanyador: " << guanyador << endl
       << "Millor volta: " << temps[guanyador].millor << endl;
}
