#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

// pour openCV
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dialog *ui;

    CvCapture* video;

    String face_cascade_name;
    String eyes_cascade_name;

    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;

    Mat matOriginale;
    Mat matAnalysee;

    //QImage imageOriginale;
    //QImage imageAnalysee;

    QTimer* temporisation;

    void detection(Mat);

public slots:
    void traitement();

private slots:
    void on_bouton_pause_clicked();
};

#endif // DIALOG_H
