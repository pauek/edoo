#include <QtGui/QApplication>
#include "finestra.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Finestra w;
    w.show();

    return a.exec();
}
