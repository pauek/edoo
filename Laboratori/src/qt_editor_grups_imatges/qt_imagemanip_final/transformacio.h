#ifndef TRANSFORMACIO_H
#define TRANSFORMACIO_H

#include <QImage>
#include <QListWidgetItem>

class Transformacio : public QListWidgetItem {
public:
  Transformacio();
  virtual QImage executa(QImage& imatge) const = 0;
  virtual bool configura() = 0;
};

class Invertir : public Transformacio {
public:
  Invertir();
  QImage executa(QImage& image) const;
  bool configura();
};

class Escalar : public Transformacio {
  double _escala;
public:
  Escalar();
  QImage executa(QImage& imatge) const;
  bool configura();
};

class Girar : public Transformacio {
  double _angle;
public:
  Girar();
  QImage executa(QImage& imatge) const;
  bool configura();
};

#endif // TRANSFORMACIO_H
