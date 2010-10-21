
#include <QMessageBox>
#include <QFileDialog>
#include <QModelIndex>
#include "finestra.h"
#include "transformacio.h"

Finestra::Finestra(QWidget *parent) :
    QWidget(parent)
{
  setWindowTitle("Manipulador de Grups d'Imatges");

  // Inicialitzem els elements de la finestra
  _llista   = new QListWidget;
  _seleccio = new QComboBox;
  _afegeix   = new QPushButton("Afegeix...");
  _esborra = new QPushButton("Esborra");
  _executa   = new QPushButton("Executa");

  // Omplim la selecció
  _seleccio->addItem("invertir");
  _seleccio->addItem("girar");
  _seleccio->addItem("escalar");

  // Creem un distribuidor
  QGridLayout *vbox = new QGridLayout;
  vbox->addWidget(_seleccio, 0, 0);
  vbox->addWidget(_llista, 1, 0, 4, 1);
  vbox->addWidget(_afegeix, 0, 1);
  vbox->addWidget(_esborra, 1, 1);
  vbox->addWidget(_executa, 4, 1);
  setLayout(vbox);

  // Connectem events
  connect(_afegeix, SIGNAL(clicked()), this, SLOT(afegir()));
  connect(_esborra, SIGNAL(clicked()), this, SLOT(esborrar()));
  connect(_executa, SIGNAL(clicked()), this, SLOT(opera()));
  connect(_llista, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
          this, SLOT(dobleclic(QListWidgetItem*)));
}

void Finestra::afegir() {
  QString text = _seleccio->currentText();
  Transformacio *t = 0;
  if (text == "invertir") {
    t = new Invertir;
  } else if (text == "girar") {
    t = new Girar;
  } else if (text == "escalar") {
    t = new Escalar;
  }
  if (t != 0) {
    if (t->configura()) _llista->addItem(t);
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
