
#include <iostream>
#include <fstream>
using namespace std;

#include "taula.h"

int main() {
  Taula T(1000000);
  int N = 0, quants = 0;
  double x, mitjana = 0.0;

  ifstream fin("valors.txt");
  if (!fin.is_open()) {
    cout << "No he pogut obrir el fitxer" << endl;
    return 1;
  }
  fin >> x;
  while (!fin.eof()) {
    mitjana += x;
    T.set(N, x); // això seria com T[N] = x 
    N++;
    fin >> x;
  }

  // 'N' ara conté el número d'elements...
  mitjana /= double(N);

  for (int k = 0; k < N; k++) {
    // T.get(k) seria com T[k]
    cout << T.get(k) - mitjana << endl;
  }
}

#include "taula.cpp"

// Local variables:
// compile-command: "gcc -g3 -o t taula_main.cpp -lstdc++"
// End:
