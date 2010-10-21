#include <QImage>

int main() {
  QImage I("test.jpg");
  QImage tros = I.copy(0, 0, 100, 100);
  tros.save("tros.jpg");
}
