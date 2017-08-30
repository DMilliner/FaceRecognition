/*******************************/
/*        Les Includes         */
/*******************************/

#include <QApplication>
#include "mainwindow.h"
#include "facedetection.h"

/*******************************/
/*           Le Code           */
/*******************************/

int main(int argc, char *argv[])
{

    QApplication application(argc, argv);

    Facedetection *facedetect = new Facedetection();

    MainWindow window(0,facedetect);
    window.show();

    application.exec();

    return 0;
}
