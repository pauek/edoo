
#include <iostream>
using namespace std;

#include "Racional.h"

string VF(bool b) {
  if (b) return "true";
  else return "false";
}

int main() {
  Racional r1(1, 2), r2(3, 4);

  cout << r1 << ' ' << r2 << endl;
  
  cout << r1 << " + " << r2 << " = " << r1 + r2 << endl;
  cout << r1 << " - " << r2 << " = " << r1 - r2 << endl;
  cout << r1 << " * " << r2 << " = " << r1 * r2 << endl;
  cout << r1 << " / " << r2 << " = " << r1 / r2 << endl;

  cout << r1 << " == " << r2 << " -> " << VF(r1 == r2) << endl;
  cout << r1 << " != " << r2 << " -> " << VF(r1 != r2) << endl;
  cout << r1 << " > " << r2 << "  -> " << VF(r1 > r2) << endl;
  cout << r1 << " >= " << r2 << " -> " << VF(r1 >= r2) << endl;
  cout << r1 << " < " << r2 << "  -> " << VF(r1 < r2) << endl;
  cout << r1 << " <= " << r2 << " -> " << VF(r1 <= r2) << endl;

  cout << r1 << " + " << 2 << " = " << r1 + 2 << endl;
  cout << r1 << " - " << 2 << " = " << r1 - 2 << endl;
  cout << r1 << " * " << 5 << " = " << r1 * 5 << endl;
  cout << r1 << " / " << 5 << " = " << r1 / 5 << endl;
}
