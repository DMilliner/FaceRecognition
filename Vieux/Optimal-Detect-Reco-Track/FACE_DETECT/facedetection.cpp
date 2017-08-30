#include "facedetection.h"
#include <QImage>
#include <omp.h>


Facedetection::Facedetection()
{
    // On initialise toutes les variables qui ne changeront pas
    // On en profite pour entrainer le model qui va nous servir à devenir les noms

    // On charge la cascade qui va nous servir à détecter les visages
    if(!haar_cascade.load("haarcascade_frontalface_alt.xml"))
        exit(-1);
    if(!haar_cascade_profil.load("haarcascade_profileface.xml"))
        exit(-1);

    // On créer le FaceRecognizer
    model = cv::createFisherFaceRecognizer();
    update_facerecognizer();

    im_width = 160;
    im_height = 160;

    // On lance par défaut la caméra au démarage
    video = cvCaptureFromCAM( 0 );
    flip_cam = true;

}

void Facedetection::update_facerecognizer()
{
    // Ouverture des Basse de Données contenant les noms et les visages
    try {
        read_csv("Database.txt","DatabaseName.txt",faceimages,facelabels,';');
    } catch (cv::Exception& e) {
        std::cout << "Error opening file \"" << "database.txt" << "\". Reason: " << e.msg << std::endl;
    exit(-1);
    }
    model->train(faceimages, facelabels);
}

void Facedetection::run()
{
    // On récupère une première image pour rentrer dans la boucle
    facetracked.clear();
    frame = cvQueryFrame(video);
    while(!frame.empty()) // On continue tant que l'on est pas arriver à la fin de la vidéo
    {
        traite_image(frame,flip_cam); // On détecte les visages et on gère l'aspect graphique
        frame = cvQueryFrame( video ); // Quand on arrive à la fin de la vidéo la matrice récupérée est vide
    }
    //cvReleaseCapture(&video); // On libère le flux vidéo et le thread se termine
     video = cvCaptureFromCAM( 0 );
     set_flip_cam(true);
}

void Facedetection::traite_image(Mat& frame,bool flip_cam)
{
    Mat gray;
    int prediction=0,i=0,j=0;
    double confidence=0.0;

    if(flip_cam == true)
        flip(frame,frame,1); // Evite l'effet miroir avec une caméra

    // On convertit en gris et on égalise l'histogramme
    cvtColor(frame, gray, CV_BGR2GRAY);
    equalizeHist( gray, gray);
    frame.copyTo( img );

    haar_cascade.detectMultiScale(gray, facedetected,2.0);
    //haar_cascade_profil.detectMultiScale(gray,profildetected,2.0);


    int size=facetracked.size(); // on stock le nombre de visage tracké

    for( vector<Rect>::const_iterator r = facedetected.begin(); r != facedetected.end(); r++,j++)
    {
        Mat face(frame,*r); // On récupère l'image du visage
        cv::resize(face, face, cv::Size(im_width, im_height), 1.0, 1.0, cv::INTER_CUBIC);

        Mat templ;
        cvtColor( face, templ, CV_BGR2GRAY ); // On la redimensionne et on la convertit en gris

        model->predict(templ,prediction,confidence); // On devine l'id d'un nom inclus dans notre Base de données

        if(size==0) // si aucun visage tracké
        {
            nouveau = Face(); // on remet a 0 nouveau
            face.copyTo(nouveau.img);
            nouveau.name=base_name[prediction];
            nouveau.windowsize=Point(im_width,im_height);
            nouveau.trackingup=false;
            nouveau.prevLoc=Point(facedetected[j].x,facedetected[j].y);
            facetracked.push_back(nouveau);

        }else // si 1 visage ou + tracké
        {

        int xi = facedetected[j].x;
        int yi = facedetected[j].y;
        int count=0;

        for( i=0; i < size ; i++) // on test si le visage n'est pas le meme que les autres deja tracké
            if(( (xi<(facetracked[i].prevLoc.x-50))||(xi>(facetracked[i].prevLoc.x+200))|| (yi<(facetracked[i].prevLoc.y-50)) || (yi>(facetracked[i].prevLoc.y+200)))&&facetracked[i].trackingup)
                count++;


        if(count==size) // si count == size alors il est different de tous les visages tracké, donc on le rajoute a la liste de track
            {
            nouveau = Face(); // on remet a 0 nouveau
            face.copyTo(nouveau.img);
            nouveau.name=base_name[prediction];
            nouveau.windowsize=Point(im_width,im_height);
            nouveau.trackingup=false;
            nouveau.prevLoc=Point(xi,yi);
            facetracked.push_back(nouveau);
            }
        }
    }

    // tracking

    size=facetracked.size();

    for(i=0; i<size; i++) // on parcour tout les visage a tracker
    {

    minLoc=Point();

    // Create the result matrix
    result_cols = 1 + img.cols - facetracked[i].img.cols;
    result_rows = 1 + img.rows - facetracked[i].img.rows;

    result=Mat();
    result .create( result_cols, result_rows, CV_32FC1 );

    /// Do the Matching and Normalize

    matchTemplate( img , facetracked[i].img, result, CV_TM_SQDIFF );
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    matchLoc = minLoc;

    /// Localizing the best match with minMaxLoc

    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    double x= minLoc.x;
    double y= minLoc.y;
    rectangle(img, Rect(minLoc,Point(x+facetracked[i].windowsize.x,y+facetracked[i].windowsize.y)), CV_RGB(0, 255,0), 1);
    cv::putText(img, facetracked[i].name ,minLoc, cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 1);

    if(!facetracked[i].trackingup)
    {
        facetracked[i].prevLoc=Point(x,y);
        facetracked[i].trackingup=true;
    }

    double px= facetracked[i].prevLoc.x;
    double py= facetracked[i].prevLoc.y;

    if( (px-x)>60.0 || (px-x)<-60.0 || (py-y)>60 || (py-y)<-60 )
    {
        facetracked.erase(facetracked.begin()+i);
        i=facetracked.size();

    }else
    {
        facetracked[i].prevLoc=Point(x,y);
    }

    }
    // final

    cv::resize(img,img,Size(width_screen,height_screen),0,0,INTER_LINEAR); // On redimensionne l'image à la taille du cadre d'affichage (Utile pour des avi de taille différente)
    emit envoimage(mat2qimage(img)); // On envoie ce signal à un slot qui va se charger d'afficher l'image

}


QImage Facedetection::mat2qimage(Mat& frame)
{
    // Seul une Qimage peut etre afficher dans la fenetre du programme
    // On convertit donc la Mat en QImage
    QImage frame_convert((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    frame_convert = frame_convert.rgbSwapped();
    return frame_convert;
}

void Facedetection::read_csv(const string& filename,const string& dataname, vector<Mat>& images, vector<int>& labels, char separator)
{
    string line;

    ///////// Ouverture du fichier database
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file)
    {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }

    ///////// Remplis les vecteurs à partir des lignes
    string path, classlabel;
    while (getline(file, line))
    {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty())
        {
            images.push_back(imread(path,0));
            //cv::imshow("test",imread(path,0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }

    ////// Ouverture du fichier database_name
    std::ifstream file_name(dataname.c_str(), ifstream::in);
    if (!file_name)
    {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }

    /////////// Remplis la map à partir des lignes
    string name, id;
    while (getline(file_name, line))
    {
        stringstream liness(line);
        getline(liness, name, separator);
        getline(liness, id);
        if(!id.empty() && !name.empty())
            base_name[atoi(id.c_str())]=name;
    }

}

void Facedetection::test()
{

}
