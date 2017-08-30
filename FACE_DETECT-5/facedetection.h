#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include <QThread>
#include <QObject>
#include <QImage>
#include <QDialog>


#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <map>

// pour openCV
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/contrib/contrib.hpp"

#include "detection.h"

using namespace cv;
using namespace std;

struct Face;
class detection;

struct Values_Statistique
{
    float NbFrame;
    float NbDetection;
    double TauxDeDetection;

    double NbReconnaissanceOkIdOK;
    double NbReconnaissanceOkIdKo;
    double NbReconnaissanceKoIdInconnu;
    double NbReconnaissanceKoIdConnu;
    double TauxDeReconnaissance;

    double TempsTraitement;
};

class Facedetection : public QThread
{
    Q_OBJECT

    public:

        Facedetection();
        CvCapture* video;

        void run();
        void traite_image(Mat& frame);

        inline void set_dim_screen(int w, int h){width_screen=w;height_screen=h;}
        inline void set_flip_cam(bool option){flip_cam=option;}
        inline void set_display_screen(bool option){display_stat=option;}
        inline Mat get_MatImage(void){return frame;}
        inline void set_nameToTest(string name){NomInVideoTest=name;}
        inline vector<Face> get_FaceTracked(void){return facetracked;}
        void reset_stats(Values_Statistique *stat);
        bool check_nameinDB(string name);
        QImage mat2qimage(Mat &mat);

        detection *detect;

        QMutex muteximg,mutexlist;

        string NomInVideoTest;

        Mat frame;
        Mat img;
        Mat result;

        bool flip_cam;
        bool display_stat;

        int width_screen;
        int height_screen;




        //Tracking

        int result_cols,result_rows;
        double minVal;
        double maxVal;
        struct Values_Statistique Stat;
        vector<Face> facetracked;

    signals:
        void envoimage(QImage image);
        void display_windowStat();

};

#endif // FACEDETECTION_H
