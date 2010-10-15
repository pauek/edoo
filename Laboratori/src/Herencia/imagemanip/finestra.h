#ifndef FINESTRA_H
#define FINESTRA_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>

class Finestra : public QWidget
{
  Q_OBJECT

  QPushButton *_boto_afegir, *_boto_operar, *_boto_esborrar;
  QListWidget *_llista;

public:
    explicit Finestra(QWidget *parent = 0);


signals:

public slots:
    void opera();
    void afegir();
    void esborrar();

private:
    void manipula_un_sol_fitxer(QString nomfitxer);
};

#endif // FINESTRA_H
