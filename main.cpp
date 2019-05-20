#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setTitle("Opengl test");
    w.resize(800, 600);
    w.show();
    while(w.isVisible())
    {
        app.processEvents();

        // perform your own actions here
    }
    //return a.exec();
    return 0;
}
