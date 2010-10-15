#include "textdialog.h"
#include <QGridLayout>

TextDialog::TextDialog(QWidget *parent) :
    QDialog(parent)
{
  _text = new QLineEdit;
  _boto_ok = new QPushButton("D'acord");
  _boto_cancel = new QPushButton("Cancel.la");

  QGridLayout *graella = new QGridLayout;
  graella->addWidget(_text, 0, 0, 1, 2);
  graella->addWidget(_boto_ok, 1, 0);
  graella->addWidget(_boto_cancel, 1, 1);
  setLayout(graella);

  connect(_boto_ok, SIGNAL(clicked()), this, SLOT(accept()));
  connect(_boto_cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

QString TextDialog::text() const {
  return _text->text();
}
