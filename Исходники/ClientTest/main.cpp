#include "clienttest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientTest w;
    w.show();

    return a.exec();
}
