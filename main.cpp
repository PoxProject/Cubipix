#include "cubipix.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cubipix w;
    w.show();

    return a.exec();
}
