
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;

int dorsal_guanyador(const vector< list<double> >& temps) {
  float millor = temps[0].back();
  int guanyador = 0;
  for (int k = 1 ; k < 25; k++) {
    if (temps[k].back() < millor) {
      guanyador = k;
      millor = temps[k].back();
    }
  }
  return guanyador;
}

double millor_volta(const list<double>& cronos) {
  double millor = cronos.front(), anterior;
  list<double>::const_iterator i = cronos.begin();
  anterior = *i;
  for (i++; i != cronos.end(); i++) {
    double volta = *i - anterior;
    if (volta < millor) millor = volta;
    anterior = *i;
  }
  return millor;
}

int main() {
  vector< list<double> > temps(25);
  int dorsal;
  double crono;

  ifstream fin("cursa.txt");
  fin >> dorsal >> crono;
  while (!fin.eof()) {
    temps[dorsal].push_back(crono);
    fin >> dorsal >> crono;
  }

  int guanyador = dorsal_guanyador(temps);
  double volta = millor_volta(temps[guanyador]);

  cout << "Dorsal guanyador: " << guanyador << endl
       << "Millor volta: " << volta << endl;
}
