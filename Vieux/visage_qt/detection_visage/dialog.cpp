#include "dialog.h"
#include "ui_dialog.h"

#include <QTimer>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    video = NULL;

    this->setWindowTitle("detection de visages par Arthur");

    face_cascade_name = "haarcascade_frontalface_alt.xml";
    eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";

    if( !face_cascade.load( face_cascade_name ) )
    {
        ui->txt_erreur->appendPlainText("erreur chargement cascade visage");
        ui->bouton_pause->setText("quitter");
    }
    else
        if( !eyes_cascade.load( eyes_cascade_name ) )
        {
            ui->txt_erreur->appendPlainText("erreur chargement cascade yeux");
            ui->bouton_pause->setText("quitter");
        }
        else
        {
            video = cvCaptureFromAVI( "blade.avi" );
            if(video)
            {
                temporisation = new QTimer(this);
                connect(temporisation, SIGNAL(timeout()), this, SLOT(traitement()));
                temporisation->start(20);
            }
            else
            {
                ui->txt_erreur->appendPlainText("erreur lecture AVI");
                ui->bouton_pause->setText("quitter");
            }
        }

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Dialog::traitement()
{
    matOriginale = cvQueryFrame( video );

    if( matOriginale.empty() )
    {
        ui->txt_erreur->appendPlainText("fin video");
        cvReleaseCapture( &video );
        temporisation->stop();
        ui->bouton_pause->setText("quitter");
    }
    else
    {
        QImage imageOriginale((uchar*)matOriginale.data, matOriginale.cols, matOriginale.rows, matOriginale.step, QImage::Format_RGB888);
        imageOriginale = imageOriginale.rgbSwapped();
        ui->label_avant->setPixmap(QPixmap::fromImage(imageOriginale));

        detection(matOriginale);
    }
}

void Dialog::on_bouton_pause_clicked()
{
    if(ui->bouton_pause->text() == "quitter")
        this->close();

    if(temporisation->isActive() == true)
    {
        temporisation->stop();
        ui->bouton_pause->setText("reprendre");
    }
    else
    {

        temporisation->start(20);
        ui->bouton_pause->setText("pause");
    }
}

void Dialog::detection(Mat frame)
{
    RNG rng(12345);
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));

    for( size_t i = 0; i < faces.size(); i++ )
    {
       Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
       ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );

       Mat faceROI = frame_gray( faces[i] );
       std::vector<Rect> eyes;

       eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

       for( size_t j = 0; j < eyes.size(); j++ )
        {
          Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
          int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
          circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 3, 8, 0 );
        }
    }

    matAnalysee = frame;
    QImage imageAnalysee((uchar*)matAnalysee.data, matAnalysee.cols, matAnalysee.rows, matAnalysee.step, QImage::Format_RGB888);
    imageAnalysee = imageAnalysee.rgbSwapped();
    ui->label_apres->setPixmap(QPixmap::fromImage(imageAnalysee));

}
