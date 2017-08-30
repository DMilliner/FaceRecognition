/*******************************/
/*        Les Includes         */
/*******************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_visage.h"

#include "QMessageBox"
#include "statistique.h"
#include "facedetection.h"
#include "detection.h"

/*******************************/
/*    Les Variables globales   */
/*******************************/

Mat frame;

/*******************************/
/*           Le Code           */
/*******************************/

/*
 *  Méthode  : Constructeur de la fenêtre principale.
 *  Arguments: la fentre parent de type QWidget
 *           : la fonction de facedetection de type Facedetection
 *  Hérite de: d'une fenêtre de type QMainWindow
 *             ui objet de classe MainWindow
 */
MainWindow::MainWindow(QWidget *parent,Facedetection *facedetect) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Récupère les dimensions du cadre d'affichage des images
    QRect cadre = ui->label->geometry();
    cadre.getRect(&x,&y,&width_screen,&heigth_screen);

    facedetection=facedetect;
    facedetection->set_dim_screen(width_screen,heigth_screen);// Met à jour les dimensions du cadre dans facedetection

    // Création d'une image de background
    Mat background;

    background = imread("./Menu/BW.jpg");
    cv::resize(background,background,Size(width_screen,heigth_screen),0,0,INTER_LINEAR);
    QImage Qbackground = facedetection->mat2qimage(background);
    ui->label->setPixmap(QPixmap::fromImage(Qbackground));

    ui->buttonAdd->setEnabled(false);
    ui->buttonPause->setEnabled(false);

    thread_paused=false;

    // On connecte les signaux à leurs fonctions
    connect(facedetection,SIGNAL(envoimage(QImage)),this,SLOT(updateimage(QImage)));

    connect(ui->buttonRun,SIGNAL(clicked()),this,SLOT(in_Video()));
    connect(ui->buttonAdd,SIGNAL(clicked()),this,SLOT(addminiature()));
    connect(ui->buttonBrowser,SIGNAL(clicked()),this,SLOT(on_bouton_browser_cliked()));
    connect(ui->buttonPause,SIGNAL(clicked()),this,SLOT(pause_thread()));

    connect(facedetection,SIGNAL(display_windowStat()),this,SLOT(statistique_display()));
}

/*
 *  Méthode  :  Destructeur de la fenêtre principale.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*
 *  Méthode  :  Mise en Pause du thread
 */
void MainWindow::pause_thread()
{
    if(!thread_paused)
    {
        facedetection->muteximg.lock();
        facedetection->mutexlist.lock();
        thread_paused=true;
    }
    else
    {
        facedetection->muteximg.unlock();
        facedetection->mutexlist.unlock();
        thread_paused=false;
    }


}

/*
 *  Méthode  :  Signal qui s'execute à la lecture d'une video.
 */
void MainWindow::in_Video()
{
    ui->buttonAdd->setEnabled(true);
    ui->buttonPause->setEnabled(true);
    facedetection->start();
}

/*
 *  Méthode  :  Mise à jour de l'image.
 *  Argument :  une image de type QImage
 */
void MainWindow::updateimage(QImage image)
{
    ui->label->setPixmap(QPixmap::fromImage(image));
}

/*
 *  Méthode  :  Affichage de la fenetre de statistique.
 */
void MainWindow::statistique_display()
{
    ui->buttonBrowser->setEnabled(false);
    ui->buttonAdd->setEnabled(false);
    ui->buttonPause->setEnabled(false);
    ui->buttonRun->setEnabled(false);

    statistique *window_stat = new statistique();
    window_stat->set_stats(facedetection->Stat);
    window_stat->exec();

    ui->buttonBrowser->setEnabled(true);
    ui->buttonAdd->setEnabled(true);
    ui->buttonPause->setEnabled(true);
    ui->buttonRun->setEnabled(true);
}

/*
 *  Méthode  :  Affichage de la fenetre d'e statistique d'ajout de visage.
 */
void MainWindow::addminiature()
{       
    int i=0;
    Mat frame;
    vector<Rect> faces_added;
    vector<Face> faces_tracked;

    facedetection->muteximg.lock();
    facedetection->mutexlist.lock();

    frame = facedetection->get_MatImage();
    faces_added= facedetection->detect->get_FacesDetected();
    faces_tracked = facedetection->get_FaceTracked();

    add_visage *Qaddbox = new add_visage();

    if(faces_added.size() != 0)
        {
                QMessageBox::information(this, "Visage(s) trouve(s)", "Visage(s) trouve(s)");

                for( vector<Rect>::const_iterator r = faces_added.begin(); r != faces_added.end(); r++)
                    {
                        Mat face(frame,*r);
                        cv::resize(face, face, cv::Size(160, 160), 1.0, 1.0, cv::INTER_CUBIC);
                        QImage Qface = facedetection->mat2qimage(face);

                        Qaddbox->setImage(Qface);
                        Qaddbox->exec();

                    }
                facedetection->detect->update_facerecognizer();
                facedetection->muteximg.unlock();
                facedetection->mutexlist.unlock();
        }
        else if(faces_tracked.size() != 0)
        {
            QMessageBox::information(this, "Visage(s) trouve(s)", "Visage(s) trouve(s)");

            for( vector<Face>::const_iterator s = faces_tracked.begin(); s != faces_tracked.end(); s++,i++)
                {
                    Face temp_Face = *s;

                    Point null(0,0);
                    Point min_temp = temp_Face.minLoc;
                    Size  window_size = temp_Face.windowsize;

                    if(min_temp != null)
                        {
                        Rect temp_Rect(min_temp,Point(min_temp.x+window_size.width,min_temp.y+window_size.height));
                        Mat face_tracked(frame,temp_Rect);

                        cv::resize(face_tracked, face_tracked, cv::Size(160, 160), 1.0, 1.0, cv::INTER_CUBIC);
                        QImage Qface_tracked = facedetection->mat2qimage(face_tracked);

                        Qaddbox->setImage(Qface_tracked);
                        Qaddbox->exec();
                        }
                }
            facedetection->detect->update_facerecognizer();
            facedetection->muteximg.unlock();
            facedetection->mutexlist.unlock();
        }
    else
        QMessageBox::information(this, "Erreur", "Aucun visages trouves");
        facedetection->muteximg.unlock();
        facedetection->mutexlist.unlock();
}


/*
 *  Méthode  :  Affichage de la fenetre pour naviguer dans l'arborescence des dossiers.
 */
void MainWindow::on_bouton_browser_cliked()
{

    // Détruis le thread en cours si il y en a un
    facedetection->muteximg.lock();
    facedetection->mutexlist.lock();

    // On libere le precedent flux si il y en a un
    cvReleaseCapture( &facedetection->video);
    facedetection->reset_stats(&facedetection->Stat);

    // On lance le navigateur de fichier pour récupérer l'avi
    ui->textBrowser->clear();
    QString fichier = QFileDialog::getOpenFileName(0, "Ouvrir un fichier", QString(), "Avi (*.avi)");
    ui->textBrowser->setText(fichier);

    std::string avi_name;
    avi_name = fichier.toStdString(); // Convertit un Qstring en std::string
    facedetection->video = cvCaptureFromAVI( avi_name.c_str() ); // Convertit un std::string en char

    if(fichier.contains("Test"))
        {
            //QString name_test;
            facedetection->set_display_screen(true);

            string path;
            path = fichier.toStdString();
            unsigned taille = path.find_last_of("/");
            path.substr(0, taille);
            path.substr(taille+1);
            QString temp(path.substr(taille+1).c_str());

           string name = temp.toStdString();
           unsigned size = name.find("_");

           QString nametoSave(name.substr(0,size).c_str());

           facedetection->set_nameToTest(nametoSave.toStdString());

        }

    // Une preview de la vidéo
    if(facedetection->video)
        {

                facedetection->set_flip_cam(false);

            // Affiche la preview de la video
            Mat preview;
            preview = cvQueryFrame(facedetection->video);
            cv::resize(preview,preview,Size(width_screen,heigth_screen),0,0,INTER_LINEAR);

            updateimage(facedetection->mat2qimage(preview));
        }
        else
        {
            facedetection->video = cvCaptureFromCAM( 0 );
            facedetection->set_flip_cam(true);
        }
    facedetection->muteximg.unlock();
    facedetection->mutexlist.unlock();
}
