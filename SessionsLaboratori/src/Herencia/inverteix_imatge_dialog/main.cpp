#include <QApplication>
#include <QFileDialog>
#include <QImage>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QFileDialog F;
  F.setFileMode(QFileDialog::ExistingFiles)
  if (F.exec()) {
    QStringList fitxers = F.selectedFiles();
    QString nom = fitxers.at(0);
    QImage I(nom);
    I.invertPixels();
    nom.replace(".jpg", "_i.jpg");
    I.save(nom);
  }
}
