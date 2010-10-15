#include "finestra.h"
#include "textdialog.h"
#include <QMessageBox>
#include <QFileDialog>

Finestra::Finestra(QWidget *parent) :
    QWidget(parent)
{
  QVBoxLayout *vbox = new QVBoxLayout;
  _llista = new QListWidget;
  _boto_afegir   = new QPushButton("Afegeix...");
  _boto_esborrar = new QPushButton("Esborra");
  _boto_operar   = new QPushButton("Executa");

  vbox->addWidget(_llista);
  vbox->addWidget(_boto_afegir);
  vbox->addWidget(_boto_esborrar);
  vbox->addWidget(_boto_operar);

  _llista->addItem("inverteix");
  _llista->addItem("gira 90");

  connect(_boto_operar, SIGNAL(clicked()), this, SLOT(opera()));
  connect(_boto_afegir, SIGNAL(clicked()), this, SLOT(afegir()));
  connect(_boto_esborrar, SIGNAL(clicked()), this, SLOT(esborrar()));

  setLayout(vbox);
}

void Finestra::afegir() {
  TextDialog D;
  if (D.exec()) {
    _llista->addItem(D.text());
  }
}

void Finestra::esborrar() {
  int actual = _llista->currentRow();
  _llista->takeItem(actual);
}

void Finestra::opera()
{
  QFileDialog F(this);
  if (!F.exec()) return;

  QStringList fitxers = F.selectedFiles();
  for (int i = 0; i < fitxers.size(); i++) {
    manipula_un_sol_fitxer(fitxers.at(i));
  }
}

void Finestra::manipula_un_sol_fitxer(QString nomfitxer) {
  QImage I(nomfitxer);
  for (int i = 0; i < _llista->count(); i++) {
    QListWidgetItem *item = _llista->item(i);
    QString comanda = item->text();

    if (comanda == "inverteix") {
      I.invertPixels();
    }
    else if (comanda == "escala") {
      I = I.scaled(100, 100);
    }
    else if (comanda == "gira 90") {
      QMatrix m;
      m.rotate(90.0f);
      I = I.transformed(m);
    }
  }
  nomfitxer.replace(".", "_m.");
  I.save(nomfitxer);
}
