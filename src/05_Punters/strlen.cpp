
#include <iostream>
using namespace std;

int longitud(char *par) {
  int L = 0;
  while (*par != 0) {
    L++;
    par++;
  }
  return L;
}

int main() {
  cout << longitud("Supercalifragilísticorl!") << endl;
}
