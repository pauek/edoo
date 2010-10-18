
#include <QApplication>
#include <QPixmap>
#include <QPainter>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QPixmap dibuix(500, 500);
  {
    QPainter painter(&dibuix);
    painter.fillRect(0, 0, 500, 500, Qt::white);
    painter.drawLine(0, 0, 100, 100);
    painter.drawText(50, 50, "Mola molt");
  }
  dibuix.save("test.png");
}
