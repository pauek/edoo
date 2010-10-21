
#include "transformacio.h"

//+1
void Inversio::executa(QImage &I) const {
  I.invertPixels();
}
//-1

//+2
void Rotacio::executa(QImage &I) const {
  QMatrix m;
  m.rotate(90.0);
  I = I.transformed(m);
}
//-2
