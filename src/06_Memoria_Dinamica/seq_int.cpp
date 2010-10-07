#include <iostream>
using namespace std;

struct Element {
  int num;
  Element *anterior;
};

int main() {
  Element *actual = NULL;
  int n;

  // Llegim la seqüència
  cin >> n;
  while (n != -1) {
    Element *nou = new Element;
    nou->num = n;
    nou->anterior = actual;
    actual = nou;
    cin >> n;
  }

  // Mostrem la seqüència
  while (actual != NULL) {
    cout << actual->num << ' ';
    actual = actual->anterior;
  }
  cout << endl;
}
