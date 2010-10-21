#ifndef FINESTRA_H
#define FINESTRA_H

#include <QtGui/QWidget>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>

class Finestra : public QWidget
{
  Q_OBJECT
  QComboBox *_seleccio;
  QListWidget *_llista;
  QPushButton *_afegeix, *_esborra, *_executa;

  void _executa_un(QString nomfitxer);

public:
  Finestra(QWidget *parent = 0);
  ~Finestra();

public slots:
  void afegeix();
  void esborra();
  void executa();
  void doble_clic(QListWidgetItem *item);
};

#endif // FINESTRA_H
