
#include <QApplication>
#include <QMessageBox>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "textdialog.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  TextDialog td("El teu nom?");

  if (td.exec()) {
    QString missatge = "Com estas, ";
    missatge += td.text();
    missatge += ", ets un gran programador";

    QMessageBox box;
    box.setWindowTitle("Salutacio");
    box.setText(missatge);
    box.exec();
  }
}
