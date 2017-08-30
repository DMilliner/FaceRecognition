#ifndef FACETRACKING_H
#define FACETRACKING_H

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
#include <string>

// pour openCV
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/contrib/contrib.hpp"

using namespace cv;
using namespace std;

class facetracking : public QThread
{
        Q_OBJECT

public:
    facetracking(float cadrex,float cadrey,string name);
    void run();

private:

    Point precedent;
    bool trackingup = false;
    float cadrex,cadrey;
    string name;
};

#endif // FACETRACKING_H
