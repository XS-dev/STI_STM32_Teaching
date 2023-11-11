#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //qputenv("QT_SCALE_FACTOR", "0.65");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
