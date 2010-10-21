#include <QApplication>
#include <QFileDialog>
#include <QImage>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QFileDialog F;
  F.setFileMode(QFileDialog::ExistingFiles);
  if (F.exec()) {
    QStringList fitxers = F.selectedFiles();
    for (int i = 0; i < fitxers.size(); i++) {
      QString nom = fitxers.at(i);
      QImage I(nom);
      I.invertPixels();
      nom.replace(".", "_i.");
      I.save(nom);
    }
  }
}
