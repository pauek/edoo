
#include <iostream>
using namespace std;

struct Dada {
  int   elem;
  Dada *prev;
};

int main() {
  Dada *actual = NULL;
  int n;

  // Llegim la seqüència
  cin >> n;
  while (n != -1) {
    Dada *nova = new Dada;
    nova->elem = n;
    nova->prev = actual;
    actual = nova;
    cin >> n;
  }

  // Mostrem la seqüència
  while (actual != NULL) {
    cout << actual->elem << ' ';
    actual = actual->prev;
  }
  cout << endl;
}
