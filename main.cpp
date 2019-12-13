#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QVector<QVector<float>> >("QVector<QVector<float>>");
    MainWindow w;
    w.show();
    return a.exec();
}
