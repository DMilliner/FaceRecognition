#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "facedetection.h"
#include <QFileDialog>


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    public:
        explicit MainWindow(QWidget *parent = 0,Facedetection *facedetect= NULL);
        ~MainWindow();

        Ui::MainWindow *ui;
        Facedetection *facedetection;
        int width_screen;
        int heigth_screen;
        int x,y;
        bool thread_paused;

    public slots:
        void updateimage(QImage image);
        void addminiature();
        void on_bouton_browser_cliked();
        void statistique_display();
        void pause_thread();
        void in_Video();
};

#endif // MAINWINDOW_H
