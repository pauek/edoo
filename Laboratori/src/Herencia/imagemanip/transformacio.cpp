#include "transformacio.h"

Transformacio::Transformacio(QString nom)
  : QListWidgetItem(nom)
{}

void Transformacio::configura() {}

QImage Inversio::executa(QImage &I) const {
  I.invertPixels();
  return I;
}

QImage Escalat::executa(QImage &I) const {
  QSize sz = I.size();
  sz *= _escala;
  return I.scaled(sz);
}

QImage Girat::executa(QImage &I) const {
  QMatrix m;
  m.rotate(90.0f);
  return I.transformed(m);
}

Inversio::Inversio() : Transformacio("Inversio") {}

Escalat::Escalat() : Transformacio("Escalat") {
  _escala = .5;
  actualitzaText();
}

void Escalat::actualitzaText() {
  QString t("Escalat %1");
  setText(t.arg(_escala));
}

void Escalat::configura() {
  actualitzaText();

}

Girat::Girat() : Transformacio("Girat") {}

void Girat::configura() {
  QString t("Girat (%1)");
  setText(t.arg(_angle));
}
