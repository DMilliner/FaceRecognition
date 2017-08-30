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

using namespace cv;
using namespace std;

class Facedetection : public QThread
{
    Q_OBJECT

public:
    Facedetection();
    CvCapture* video;

    void run();
    void traite_image(Mat& frame,bool flip_cam);

    inline void set_dim_screen(int w, int h){width_screen=w;height_screen=h;}
    inline void set_flip_cam(bool option){flip_cam=option;}
    inline Mat get_MatImage(void){return frame;}
    inline vector<Rect> get_FacesDetected(void){return facedetected;}

    QImage mat2qimage(Mat &mat);
    void read_csv(const string& filename,const string& dataname, vector<Mat>& images, vector<int>& labels, char separator);
    void update_facerecognizer();

private:
    cv::CascadeClassifier haar_cascade;
    cv::CascadeClassifier haar_cascade_profil;

    Ptr<cv::FaceRecognizer> model;
    vector<cv::Mat> faceimages;
    vector<int> facelabels;

    Mat frame;
    Mat img;
    Mat templ;
    Mat result;

    vector<Rect> facedetected;
    vector<Rect> profildetected;
    bool flip_cam;
    map<int,string> base_name;

    int width_screen;
    int height_screen;

    int im_width;
    int im_height;

    //Tracking

    struct Face{

    Point windowsize;
    string name;
    Point prevLoc;
    Mat img;
    bool trackingup;

    };

    struct Face nouveau;

    int result_cols,result_rows;
    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;

    vector<Face> facetracked;

    Point matchLoc;



signals:
    void envoimage(QImage image);
public slots:
    void test();


};

#endif // FACEDETECTION_H
