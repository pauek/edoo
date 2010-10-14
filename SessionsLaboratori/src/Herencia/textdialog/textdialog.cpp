
// <incl>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "textdialog.h"
// </incl>

TextDialog::TextDialog(QString titol, QWidget *parent) :
    QDialog(parent)
{
  setWindowTitle(titol);

  _edit = new QLineEdit;
  _ok = new QPushButton("D'acord");
  _cancel = new QPushButton("Cancel.la");

  QGridLayout *graella = new QGridLayout;
  graella->addWidget(_edit, 0, 0, 1, 2);
  graella->addWidget(_ok, 1, 0);
  graella->addWidget(_cancel, 1, 1);
  setLayout(graella);

  connect(_ok, SIGNAL(clicked()), this, SLOT(accept()));
  connect(_cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

QString TextDialog::text() const {
  return _edit->text();
}
