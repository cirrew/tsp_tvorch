#include <QApplication>
#include "interface.h"
#include "canvas.h"
#include "sample.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TInterface w;
    w.show();

    return a.exec();
}
