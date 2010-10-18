#include "transformacio.h"

Transformacio::Transformacio(QString nom)
  : QListWidgetItem(nom)
{
}

QImage Inversio::executa(QImage &I) const {
  I.invertPixels();
  return I;
}

QImage Escalat::executa(QImage &I) const {
  QSize sz = I.size();
  sz *= .5;
  return I.scaled(sz);
}

QImage Girat::executa(QImage &I) const {
  QMatrix m;
  m.rotate(90.0f);
  return I.transformed(m);
}

Inversio::Inversio() : Transformacio("Inversio") {}
Escalat::Escalat() : Transformacio("Escalat") {}
Girat::Girat() : Transformacio("Girat") {}
