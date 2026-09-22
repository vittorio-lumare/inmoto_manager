#include "inmotomanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InMotoManager w;
    w.show();

    return a.exec();
}
