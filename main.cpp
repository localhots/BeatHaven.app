#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("BeatHaven");
    a.setOrganizationDomain("beathaven.org");
    a.setApplicationName("BeatHaven.app");

    MainWindow w;
    w.show();

    return a.exec();
}
