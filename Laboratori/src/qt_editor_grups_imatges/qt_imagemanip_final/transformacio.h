#ifndef TRANSFORMACIO_H
#define TRANSFORMACIO_H

#include <QImage>
#include <QListWidgetItem>

class Transformacio : public QListWidgetItem {
public:
  Transformacio(QString nom);
  virtual QImage executa(QImage& imatge) const = 0;
  bool es_configurable();
  virtual void configura();
};

class Inversio : public Transformacio {
public:
  Inversio();
  QImage executa(QImage& image) const;
};

class Escalat : public Transformacio {
  double _escala;
  void actualitzaText();
public:
  Escalat();
  QImage executa(QImage& imatge) const;
  void configura();
};

class Girat : public Transformacio {
  double _angle;
public:
  Girat();
  QImage executa(QImage& imatge) const;
  void configura();
};

#endif // TRANSFORMACIO_H
