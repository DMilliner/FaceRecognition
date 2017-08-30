#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_visage.h"


#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent,Facedetection *facedetect) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Récupère les dimensions du cadre d'affichage des images
    QRect cadre = ui->label->geometry();
    cadre.getRect(&x,&y,&width_screen,&heigth_screen);

    facedetection=facedetect;
    facedetection->set_dim_screen(width_screen,heigth_screen);// Met à jour les dimensions du cadre dans facedetection

    // Création d'une image de présentation
    Mat background;
    background = imread("./Menu/BW.jpg");
    cv::resize(background,background,Size(width_screen,heigth_screen),0,0,INTER_LINEAR);
    QImage Qbackground = facedetection->mat2qimage(background);
    ui->label->setPixmap(QPixmap::fromImage(Qbackground));

    // On connecte les signaux à leurs fonctions
    connect(facedetection,SIGNAL(envoimage(QImage)),this,SLOT(updateimage(QImage)));
    connect(ui->buttonRun,SIGNAL(clicked()),facedetection,SLOT(start()));

    connect(ui->buttonAdd,SIGNAL(clicked()),this,SLOT(addminiature()));
    connect(ui->buttonBrowser,SIGNAL(clicked()),this,SLOT(on_bouton_browser_cliked()));
    connect(ui->buttonPause,SIGNAL(clicked()),facedetection,SLOT(terminate()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateimage(QImage image)
{
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::addminiature()
{       
    //Quelques beugs à régler

    Mat frame;
    vector<Rect> faces_added;

    facedetection->terminate();

    frame = facedetection->get_MatImage();
    faces_added= facedetection->get_FacesDetected();

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
            facedetection->update_facerecognizer();
            facedetection->start();
      }
      else
        QMessageBox::information(this, "Erreur", "Aucun visages trouvés");
        facedetection->start();
}

void MainWindow::on_bouton_browser_cliked()
{

    // Détruis le thread en cours si il y en a un
    facedetection->terminate();

    // On libere le precedent flux si il y en a un
    cvReleaseCapture( &facedetection->video);

    // On lance le navigateur de fichier pour récupérer l'avi
    QString fichier = QFileDialog::getOpenFileName(0, "Ouvrir un fichier", QString(), "Avi (*.avi)");

    std::string avi_name;
    avi_name = fichier.toStdString(); // Convertit un Qstring en std::string
    facedetection->video = cvCaptureFromAVI( avi_name.c_str() ); // Convertit un std::string en char

    // Une preview de la vidéo
    if(facedetection->video)
    {
        facedetection->set_flip_cam(false);

        // Affiche la preview de la video
        Mat preview;
        preview = cvQueryFrame(facedetection->video);
        cv::resize(preview,preview,Size(width_screen,heigth_screen),0,0,INTER_LINEAR);

        updateimage(facedetection->mat2qimage(preview));
    }else
        {
            facedetection->video = cvCaptureFromCAM( 0 );
            facedetection->set_flip_cam(true);
        }
}
