#ifndef DETECTION_H
#define DETECTION_H

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
#include <QMutex>

// pour openCV
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/contrib/contrib.hpp"

#include "facedetection.h"

using namespace cv;
using namespace std;

struct Values_Statistique;

struct Face
{
    Size windowsize;
    string name;
    Point prevLoc;
    Mat img;
    bool trackingup;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;
};

class detection : public QThread
{

        Q_OBJECT

    public:

        detection(Mat *frame,vector<Face> *listfacetracked,QMutex *muteximg,QMutex *mutexlist, Values_Statistique *stat,string *NomInVideoTest);
        void run();
        inline vector<Rect> get_FacesDetected(void){return facedetected;}
        void update_facerecognizer();
        void read_csv(const string& filename,const string& dataname, vector<Mat>& images, vector<int>& labels, char separator);
        bool check_nameinDB(string name);

        QMutex *muteximg,*mutexlist;

        cv::CascadeClassifier haar_cascade;
        cv::CascadeClassifier haar_cascade_profil;

        Ptr<cv::FaceRecognizer> model;
        vector<cv::Mat> faceimages;
        vector<int> facelabels;
        Mat templ;

        vector<Rect> facedetected;
        vector<Rect> profildetected;
        map<int,string> base_name;

        int im_width;
        int im_height;

        struct Face nouveau;
        struct Values_Statistique *stat;
        string *NomInVideoTest;

        Mat *frame;
        vector<Face> *listfacetracked;

};

#endif // DETECTION_H
