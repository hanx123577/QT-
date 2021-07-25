#include "mainsense.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainSense w;
    w.show();
    return a.exec();
}
