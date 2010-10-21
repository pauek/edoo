#include "finestra.h"
#include "transformacio.h"
#include <QGridLayout>
#include <QFileDialog>

Finestra::Finestra(QWidget *parent)
    : QWidget(parent)
{
  _seleccio = new QComboBox;
  _llista   = new QListWidget;
  _afegeix  = new QPushButton("Afegeix...");
  _esborra  = new QPushButton("Esborra");
  _executa  = new QPushButton("Executa");

  QGridLayout *L = new QGridLayout;
  L->addWidget(_seleccio, 0, 0);
  L->addWidget(_afegeix, 0, 1);
  L->addWidget(_esborra, 1, 1);
  L->addWidget(_llista, 1, 0, 4, 1);
  L->addWidget(_executa, 4, 1);
  setLayout(L);

  _seleccio->addItem("Inversio");
  _seleccio->addItem("Rotacio");
  _seleccio->addItem("Mirall Horitzontal");
  _seleccio->addItem("Mirall Vertical");
  _seleccio->addItem("Escalat");

  connect(_afegeix, SIGNAL(clicked()), this, SLOT(afegeix()));
  connect(_esborra, SIGNAL(clicked()), this, SLOT(esborra()));
  connect(_executa, SIGNAL(clicked()), this, SLOT(executa()));
  connect(_llista, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
          this, SLOT(doble_clic(QListWidgetItem*)));
}

Finestra::~Finestra()
{}

//+2
void Finestra::afegeix() {
  QString sel = _seleccio->currentText();
  Transformacio *nova;
  if (sel == "Inversio") {
    nova = new Inversio;
  } else if (sel == "Rotacio") {
    nova = new Rotacio;
  } else if (sel == "Mirall Horitzontal") {
    nova = new MirallH;
  } else if (sel == "Mirall Vertical") {
    nova = new MirallV;
  } else if (sel == "Escalat") {
    nova = new Escalat;
  }
  nova->setText(sel);
  if (nova->configura()) {
    _llista->addItem(nova);
  }
}
//-2

void Finestra::esborra() {
  _llista->takeItem(_llista->currentRow());
}

void Finestra::executa() {
  QFileDialog F;
  F.setFileMode(QFileDialog::ExistingFiles);
  if (F.exec()) {
    QStringList fitxers = F.selectedFiles();
    for (int j = 0; j < fitxers.size(); j++) {
      _executa_un(fitxers.at(j));
    }
  }
}

void Finestra::doble_clic(QListWidgetItem *item) {
  Transformacio *t = dynamic_cast<Transformacio *>(item);
  t->configura();
}

void Finestra::_executa_un(QString nomfitxer) {
//+1
  QImage I(nomfitxer);
  for (int i = 0; i < _llista->count(); i++) {
    QListWidgetItem *item = _llista->item(i);
    Transformacio *t = dynamic_cast<Transformacio *>(item);
    if (t != 0) t->executa(I);
  }
  int j = nomfitxer.lastIndexOf(".");
  if (j != -1) {
    nomfitxer.replace(j, 1, "_m.");
  } else {
    nomfitxer += "_m";
  }
  I.save(nomfitxer);
//-1
}
