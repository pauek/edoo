
#include <iostream>
using namespace std;

#include "pixel.h"

void Pixel::llegeix(istream& i, int nmax) {
  int r, g, b;
  i >> r >> g >> b;
  red   = float(r) / float(nmax);
  green = float(g) / float(nmax);
  blue  = float(b) / float(nmax);
}

void Pixel::inverteix() {
  red   = 1.0 - red;
  green = 1.0 - green;
  blue  = 1.0 - blue;
}

void Pixel::escriu(ostream &o) const {
  o << int(red   * float(BLANC)) << ' '
    << int(green * float(BLANC)) << ' '
    << int(blue  * float(BLANC)) << "  ";
}
