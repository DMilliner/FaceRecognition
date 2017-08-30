/*******************************/
/*        Les Includes         */
/*******************************/

#include "facedetection.h"
#include "mainwindow.h"

#include <QImage>
#include <omp.h>


/*******************************/
/*           Le Code           */
/*******************************/


/*
 *  Méthode  :  Constructeur de Facedetection qui va reconnaitre et suivre les visages.
 */
Facedetection::Facedetection()
{

    // On lance par défaut la caméra au démarage
    video = cvCaptureFromCAM( 0 );

    // On initialise toutes les variables qui ne changeront pas
    // On en profite pour entrainer le model qui va nous servir à devenir les nom
    facetracked.clear();
    reset_stats(&Stat);

}

/*
 *  Méthode  : Analyse et traitement de l'image qui est un visage.
 *  Arguments: l'image de type Matrice
 */
void Facedetection::traite_image(Mat& frame)
{

    int size=facetracked.size();
    frame.copyTo( img );

    for(int i=0; i<size; i++) // On parcourt tous les visags à tracker
        {

            facetracked[i].minLoc=Point();

            // Crée un matrice résultat
            result_cols = 1 + img.cols - facetracked[i].img.cols;
            result_rows = 1 + img.rows - facetracked[i].img.rows;

            result=Mat();
            result .create( result_cols, result_rows, CV_32FC1 );

            //Fait la correspondance et normalise l'image
            Mat gris,gris2;
            cvtColor( img, gris, CV_BGR2GRAY );
            cvtColor( facetracked[i].img, gris2, CV_BGR2GRAY );

            matchTemplate( gris , gris2, result, CV_TM_SQDIFF );
            normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

            //Pour cette méthode plus la valeur sera basse plus la correspondance sera importante.
            facetracked[i].matchLoc = facetracked[i].minLoc;

            //Repère la meilleur correspondance avec minMaxLoc
            minMaxLoc( result, &minVal, &maxVal, &facetracked[i].minLoc, &facetracked[i].maxLoc, Mat() );

            double x= facetracked[i].minLoc.x;
            double y= facetracked[i].minLoc.y;

            rectangle(img, Rect(facetracked[i].minLoc,Point(x+facetracked[i].windowsize.width,y+facetracked[i].windowsize.height)), CV_RGB(0, 255,0), 1);

            cv::putText(img, facetracked[i].name ,facetracked[i].minLoc, cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 1);

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

                }
            else
                {
                    facetracked[i].prevLoc=Point(x,y);
                }

        }
    // On envoie ce signal à un slot qui va se charger d'afficher l'image
    emit envoimage(mat2qimage(img));

}


/*
 *  Méthode  : Fonction de lancement de Facedetection.
 *  Arguments: -
 */
void Facedetection::run()
{
    detection detector(&frame,&facetracked,&muteximg,&mutexlist, &Stat, &NomInVideoTest);

    detect=&detector;
    muteximg.lock();
    mutexlist.lock();


    // On récupère une première image pour rentrer dans la boucle
    facetracked.clear();
    frame = cvQueryFrame(video);
        detector.start();



    bool lock_image=false,lock_list=false;


    while(!frame.empty()) // On continue tant que l'on est pas arriver à la fin de la vidéo
        {
            Stat.NbFrame++;

            if(flip_cam == true)
                flip(frame,frame,1); // Evite l'effet miroir avec une caméra

            // On redimensionne l'image à la taille du cadre d'affichage (Utile pour des avi de taille différente)
             cv::resize(frame,frame,Size(width_screen,height_screen),0,0,INTER_LINEAR);

            if(lock_image)
                muteximg.lock();
            else
                lock_image=true;

            muteximg.unlock();

            if(lock_list)
                mutexlist.lock();
            else
                lock_list=true;

            double t = (double)cvGetTickCount();

            traite_image(frame); // On détecte les visages et on gère l'aspect graphique
            t = (double)cvGetTickCount() - t;
            t = t/((double)cvGetTickFrequency()*1000);
            Stat.TempsTraitement+=t;

            //Garantit une lecture à vitesse normale de la vidéo
            if(t<40)
                msleep(40-t);

            mutexlist.unlock();

            // Quand on arrive à la fin de la vidéo la matrice récupérée est vide
            frame = cvQueryFrame( video );
        }

     sleep(1);
     detect->terminate();

     if(display_stat)
         {

             if (Stat.NbDetection == 0)
                 {
                    Stat.TauxDeReconnaissance =  0;
                 }
             else
                 {
                     Stat.TauxDeReconnaissance = (Stat.NbReconnaissanceOkIdOK/Stat.NbDetection)*100;
                 }
             Stat.TempsTraitement/=Stat.NbFrame;
             Stat.TauxDeDetection = (Stat.NbDetection/Stat.NbFrame)*100;

/*           cout << "Test"                           << endl;
             cout << "Statistiques"                   << endl;
             cout << Stat.NbDetection                 << endl;
             cout << Stat.NbFrame                     << endl;
             cout << Stat.TauxDeDetection             << endl;
             cout << "Valeurs"                        << endl;
             cout << Stat.NbReconnaissanceOkIdOK      << endl;
             cout << Stat.NbReconnaissanceOkIdKo      << endl;
             cout << Stat.NbReconnaissanceKoIdInconnu << endl;
             cout << Stat.NbReconnaissanceKoIdConnu   << endl;
             cout << "Taux de Reco"                   << endl;
             cout << Stat.TauxDeReconnaissance        << endl;
             cout << "Temps"                          << endl;
             cout << Stat.TempsTraitement             << endl;
             cout << "Fin"                            << endl;
*/
             emit display_windowStat();

         }

     /****************************************************/
     video = cvCaptureFromCAM( 0 );
     set_flip_cam(true);
     set_display_screen(false);

}

/*
 *  Méthode  : Transforme une Mat en QImage.
 *  Arguments: l'image de type Mat
 *  retour   : l'image de type en QImage
 */
QImage Facedetection::mat2qimage(Mat& frame)
{
    // Seul une Qimage peut etre afficher dans la fenetre du programme
    // On convertit donc la Mat en QImage
    QImage frame_convert((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    frame_convert = frame_convert.rgbSwapped();

    return frame_convert;
}

/*
 *  Méthode  : Fonction de remise à zéro des variables de statistique.
 *  Arguments: Les Valeurs de statistique
 */
void Facedetection::reset_stats(Values_Statistique *stat)
{
    stat->NbDetection=0;
    stat->NbFrame=0;
    stat->NbReconnaissanceKoIdConnu=0;
    stat->NbReconnaissanceKoIdInconnu=0;
    stat->NbReconnaissanceOkIdKo=0;
    stat->NbReconnaissanceOkIdOK=0;
    stat->TauxDeDetection=0;
    stat->TauxDeReconnaissance=0;
    stat->TempsTraitement=0;
}
