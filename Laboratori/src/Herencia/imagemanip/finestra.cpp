
#include "finestra.h"
#include "transformacio.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QModelIndex>

Finestra::Finestra(QWidget *parent) :
    QWidget(parent)
{
  // Inicialitzem els elements de la finestra
  _llista   = new QListWidget;
  _seleccio = new QComboBox;
  _afegir   = new QPushButton("Afegeix...");
  _esborrar = new QPushButton("Esborra");
  _operar   = new QPushButton("Executa");

  // Omplim la selecció
  _seleccio->addItem("inverteix");
  _seleccio->addItem("gira 90");
  _seleccio->addItem("escala 100x100");

  // Creem un distribuidor
  QGridLayout *vbox = new QGridLayout;
  vbox->addWidget(_seleccio, 0, 0);
  vbox->addWidget(_llista, 1, 0, 4, 1);
  vbox->addWidget(_afegir, 0, 1);
  vbox->addWidget(_esborrar, 1, 1);
  vbox->addWidget(_operar, 4, 1);
  setLayout(vbox);

  // Connectem events
  connect(_operar, SIGNAL(clicked()), this, SLOT(opera()));
  connect(_afegir, SIGNAL(clicked()), this, SLOT(afegir()));
  connect(_esborrar, SIGNAL(clicked()), this, SLOT(esborrar()));
  connect(_llista, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
          this, SLOT(dobleclic(QListWidgetItem*)));
}

void Finestra::afegir() {
  int index = _seleccio->currentIndex();
  Transformacio *t = 0;
  switch (index) {
  case 0: t = new Inversio; break;
  case 1: t = new Girat;    break;
  case 2: t = new Escalat;  break;
  }
  if (t != 0) {
    t->configura();
    _llista->addItem(t);
  }
}

void Finestra::esborrar() {
  int actual = _llista->currentRow();
  _llista->takeItem(actual);
}

void Finestra::opera()
{
  QFileDialog F(this);
  F.setFileMode(QFileDialog::ExistingFiles);
  if (!F.exec()) return;

  QStringList fitxers = F.selectedFiles();
  for (int i = 0; i < fitxers.size(); i++) {
    manipula_un_sol_fitxer(fitxers.at(i));
  }
}

void Finestra::dobleclic(QListWidgetItem *item) {
  Transformacio *t = dynamic_cast<Transformacio *>(item);
  t->configura();
}

void Finestra::manipula_un_sol_fitxer(QString nomfitxer) {
  QImage I(nomfitxer);
  for (int i = 0; i < _llista->count(); i++) {
    Transformacio *item = dynamic_cast<Transformacio *>(_llista->item(i));
    I = item->executa(I);
  }
  nomfitxer.replace(".", "_m.");
  I.save(nomfitxer);
}
