
#include <QApplication>
#include <QWidget>
#include <QLabel>

int main(int argc, char *argv[]) {
  QApplication A(argc, argv);
  QWidget finestra;
  finestra.setWindowTitle("Hola Món");
  QLabel etiqueta("Hola, món!", &finestra);
  finestra.show();
  A.exec();
}
