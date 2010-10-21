#include "transformacio.h"
#include "textdialog.h"

Transformacio::Transformacio()
{}

bool Transformacio::configura() {
  setText(text());
  return true;
}

QImage Invertir::executa(QImage &I) const {
  I.invertPixels();
  return I;
}

QImage Escalar::executa(QImage &I) const {
  QSize sz = I.size();
  sz *= _escala;
  return I.scaled(sz);
}

QImage Girar::executa(QImage &I) const {
  QMatrix m;
  m.rotate(90.0f);
  return I.transformed(m);
}

Invertir::Invertir() {}

bool Invertir::configura() {
  setText("Invertir");
  return true;
}

Escalar::Escalar() {
  _escala = .5;
}

bool Escalar::configura() {
  TextDialog td("Factor escala");
  if (td.exec()) {
    _escala = td.text().toDouble();
    QString t("Escalar %1");
    setText(t.arg(_escala));
    return true;
  } else {
    return false;
  }
}

Girar::Girar() {
  _angle = 90.0f;
}

bool Girar::configura() {
  TextDialog td("Angle de gir");
  if (td.exec()) {
    _angle = td.text().toDouble();
    QString t("Girar %1 graus");
    setText(t.arg(_angle));
    return true;
  } else {
    return false;
  }
}
