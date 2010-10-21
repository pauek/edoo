#include "finestra.h"
#include <QGridLayout>
#include <QFileDialog>

Finestra::Finestra(QWidget *parent)
    : QWidget(parent)
{
//+1
  _seleccio = new QComboBox;
  _llista   = new QListWidget;
  _afegeix  = new QPushButton("Afegeix...");
  _esborra  = new QPushButton("Esborra");
  _executa  = new QPushButton("Executa");
//-1

//+2
  QGridLayout *L = new QGridLayout;
  L->addWidget(_seleccio, 0, 0);
  L->addWidget(_afegeix, 0, 1);
  L->addWidget(_esborra, 1, 1);
  L->addWidget(_llista, 1, 0, 4, 1);
  L->addWidget(_executa, 4, 1);
  setLayout(L);
//-2

//+3
  _seleccio->addItem("Inverteix");
  _seleccio->addItem("Gira");
//-3

//+7
  connect(_afegeix, SIGNAL(clicked()), this, SLOT(afegeix()));
  connect(_esborra, SIGNAL(clicked()), this, SLOT(esborra()));
  connect(_executa, SIGNAL(clicked()), this, SLOT(executa()));
//-7
}

Finestra::~Finestra()
{}


//+4
void Finestra::afegeix() {
  _llista->addItem(_seleccio->currentText());
}
//-4

//+5
void Finestra::esborra() {
  _llista->takeItem(_llista->currentRow());
}
//-5

void Finestra::executa() {
//+6
  QFileDialog F;
  F.setFileMode(QFileDialog::ExistingFiles);
  if (F.exec()) {
    QStringList fitxers = F.selectedFiles();
    for (int j = 0; j < fitxers.size(); j++) {
      _executa_un(fitxers.at(j));
    }
  }
//-6
}

void Finestra::_executa_un(QString nomfitxer) {
//+8
  QImage I(nomfitxer);
  for (int i = 0; i < _llista->count(); i++) {
    QString operacio = _llista->item(i)->text();
    if (operacio == "Inverteix") {
      I.invertPixels();
    } else if (operacio == "Gira"){
      QMatrix m;
      m.rotate(90.0f);
      I = I.transformed(m);
    }
  }
  int j = nomfitxer.lastIndexOf(".");
  if (j != -1) {
    nomfitxer.replace(j, 1, "_m.");
  } else {
    nomfitxer += "_m";
  }
  I.save(nomfitxer);
//-8
}
