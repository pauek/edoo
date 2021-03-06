#ifndef TRANSFORMACIO_H
#define TRANSFORMACIO_H

#include <QImage>
#include <QListWidgetItem>

class Transformacio : public QListWidgetItem {
public:
  virtual void executa(QImage& I) const = 0;
};

//+1
class Inversio : public Transformacio {
public:
  void executa(QImage& I) const;
};
//-1

//+2
class Rotacio : public Transformacio {
public:
  void executa(QImage& I) const;
};
//-2



#endif // TRANSFORMACIO_H
