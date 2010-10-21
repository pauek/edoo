
#include "transformacio.h"
#include "textdialog.h"

bool Transformacio::configura() {
  return true;
}

Rotacio::Rotacio() {
  _angle = 0.0;
}

void Inversio::executa(QImage &I) const {
  I.invertPixels();
}

void Rotacio::executa(QImage &I) const {
  QMatrix m;
  m.rotate(_angle);
  I = I.transformed(m);
}

bool Rotacio::configura() {
//+1
  TextDialog td("Posa un angle");
  if (td.exec()) {
    _angle = td.text().toDouble();
    QString text = "Rotacio (%1 graus)";
    setText(text.arg(_angle));
    return true;
  } else {
    return false;
  }
//-1
}

void MirallV::executa(QImage &I) const {
  I = I.mirrored(false, true);
}

void MirallH::executa(QImage &I) const {
  I = I.mirrored(true, false);
}

void Escalat::executa(QImage &I) const {
  QSize sz = I.size();
  sz *= _escala;
  I = I.scaled(sz);
}

bool Escalat::configura() {
  TextDialog td("Factor d'escala");
  if (td.exec()) {
    _escala = td.text().toDouble();
    if (_escala > 1.0) _escala = 1.0;
    QString text = "Escalat (factor %1)";
    setText(text.arg(_escala));
    return true;
  } else {
    return false;
  }
}
