#ifndef FINESTRA_H
#define FINESTRA_H

#include <QWidget>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>
#include <QComboBox>

class Finestra : public QWidget
{
  Q_OBJECT

  QComboBox   *_seleccio;
  QListWidget *_llista;
  QPushButton *_afegeix, *_executa, *_esborra;

public:
    explicit Finestra(QWidget *parent = 0);


signals:

public slots:
    void opera();
    void afegir();
    void esborrar();
    void dobleclic(QListWidgetItem *item);

private:
    void manipula_un_sol_fitxer(QString nomfitxer);
};

#endif // FINESTRA_H
