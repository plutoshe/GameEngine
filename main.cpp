#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setTitle("Opengl test");
    w.resize(800, 600);
    w.show();

    return a.exec();
}
