#include "servertest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerTest w;
    w.show();

    return a.exec();
}
