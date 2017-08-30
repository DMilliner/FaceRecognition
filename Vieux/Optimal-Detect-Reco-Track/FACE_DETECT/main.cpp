#include <QApplication>
#include "mainwindow.h"
#include "facedetection.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Facedetection *facedetect = new Facedetection();

    MainWindow w(0,facedetect);
    w.show();

    a.exec();
    facedetect->terminate();

    return 0;
}
