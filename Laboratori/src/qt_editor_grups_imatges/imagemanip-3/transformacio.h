#ifndef TRANSFORMACIO_H
#define TRANSFORMACIO_H

#include <QImage>
#include <QListWidgetItem>

class Transformacio : public QListWidgetItem {
public:
  virtual void executa(QImage& I) const = 0;
  virtual bool configura();
};

//+1
class Inversio : public Transformacio {
public:
  void executa(QImage& I) const;
};
//-1

//+2
class Rotacio : public Transformacio {
  double _angle;
public:
  Rotacio();
  void executa(QImage& I) const;
  bool configura();
};
//-2

class MirallH : public Transformacio {
public:
  void executa(QImage& I) const;
};

class MirallV : public Transformacio {
public:
  void executa(QImage& I) const;
};

class Escalat : public Transformacio {
  double _escala;
public:
  void executa(QImage& I) const;
  bool configura();
};


#endif // TRANSFORMACIO_H
