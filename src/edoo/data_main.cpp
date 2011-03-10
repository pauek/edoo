
#include <iostream>
using namespace std;

#include "data.h"

// Canvia una d'aquestes funcions al nom 'main' i recompila...

string VF(bool b) {
  if (b) return "true";
  else return "false";
}

int main() {
  Data d1(28, 2, 1896); 
  Data d2(31, 12, 1999); 
  d1 += 1;              // Avancem 1 dia
  cout << d1 << endl;   // Mostrem el resultat
  cout << d2 + 1 << endl;
  cout << d2 + 31 << endl;

  Data d3(1, 1, 2000);
  cout << (d2 + 1 == d3) << endl;
  cout << (d2 == d3 - 1) << endl;

  Data d4(1, 1, 1886);
  d4 += 365;
  cout << d4 << endl;  

  Data d5(31, 12, 2005);
  d5 -= 31 + 30 + 31; // retrocedim Des + Nov + Oct
  cout << d5 << endl;

  cout << d5 << " > "  << d4 << ": " << VF(d5 > d4)  << endl;
  cout << d5 << " < "  << d4 << ": " << VF(d5 < d4)  << endl;
  cout << d5 << " >= " << d4 << ": " << VF(d5 >= d4) << endl;
  cout << d5 << " <= " << d4 << ": " << VF(d5 <= d4) << endl;
  cout << d5 << " == " << d4 << ": " << VF(d5 == d4) << endl;
  cout << d5 << " != " << d4 << ": " << VF(d5 != d4) << endl;

  Data d6(1, 1, 2000), d7(31, 12, 2000);
  while (d6 <= d7) {
	 cout << d6 << ' ';
	 d6 += 14; // Cada 2 setmanes
  }
  cout << endl;
}
