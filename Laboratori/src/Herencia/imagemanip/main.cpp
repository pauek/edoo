
#include <QApplication>
#include <QListWidget>
#include "finestra.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Finestra f;
  f.show();
  app.exec();
}
