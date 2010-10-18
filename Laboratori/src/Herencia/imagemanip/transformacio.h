#ifndef TRANSFORMACIO_H
#define TRANSFORMACIO_H

#include <QImage>
#include <QListWidgetItem>

class Transformacio : public QListWidgetItem {
public:
  Transformacio(QString nom);
  virtual QImage executa(QImage& imatge) const = 0;
};

class Inversio : public Transformacio {
public:
  Inversio();
  QImage executa(QImage& image) const;
};

class Escalat : public Transformacio {
public:
  Escalat();
  QImage executa(QImage& imatge) const;
};

class Girat : public Transformacio {
public:
  Girat();
  QImage executa(QImage& imatge) const;
};

#endif // TRANSFORMACIO_H
