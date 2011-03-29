
#include "hora.h"

int main() {
  const int DIA_SENCER = 86400;

  // Test 1
  Hora h1(23, 59, 59);
  cout << h1 << endl;
  int n;
  cin >> n;
  cout << h1.avansa(n) << endl;
  cout << h1 << endl;
  
  Hora h2(DIA_SENCER / 2);
  cout << h2 << endl;
}

