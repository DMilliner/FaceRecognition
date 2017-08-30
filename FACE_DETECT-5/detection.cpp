/*******************************/
/*        Les Includes         */
/*******************************/

#include "detection.h"




/*******************************/
/*           Le Code           */
/*******************************/

/*
 *  Méthode  : Constructeur du principe de detection
 *  Arguments: l'image de type Mat
 *             la liste des visages suivis de type vector de Face
 *             muteximg  de type Qmutex
 *             mutexlist de type Qmutex
 *             les valeurs statistiques contenues dans la structure
 *             le nom de la video de type string
 */
detection::detection(Mat *frame,vector<Face> *listfacetracked,QMutex *muteximg,QMutex *mutexlist, Values_Statistique *stat,string *NomInVideoTest)
{
    this->frame=frame;
    this->listfacetracked=listfacetracked;
    this->muteximg=muteximg;
    this->mutexlist=mutexlist;
    this->stat=stat;
    this->NomInVideoTest=NomInVideoTest;

    // On charge la cascade qui va nous servir à détecter les visages
    if(!haar_cascade.load("haarcascade_frontalface_alt.xml"))
        exit(-1);
    if(!haar_cascade_profil.load("haarcascade_profileface.xml"))
        exit(-1);

    im_width  = 160;
    im_height = 160;

    // On créer le FaceRecognizer
    model = cv::createLBPHFaceRecognizer();
    update_facerecognizer();

    //Initialisation des variables de statistiques
    stat->NbDetection =0;
    stat->NbReconnaissanceOkIdOK =0;
    stat->NbReconnaissanceOkIdKo =0;
    stat->NbReconnaissanceKoIdInconnu=0;
    stat->NbReconnaissanceKoIdConnu =0;

}

/*
 *  Méthode  : Mis à jour du visage reconnue
 *  Arguments: -
 */
void detection::update_facerecognizer()
{
    // Ouverture des Basse de Données contenant les noms et les visages
    try
        {
            read_csv("Database.txt","DatabaseName.txt",faceimages,facelabels,';');
        }
    catch (cv::Exception& e)
        {
            std::cout << "Error opening file \"" << "database.txt" << "\". Reason: " << e.msg << std::endl;
            exit(-1);
        }


    model->train(faceimages, facelabels);

}


/*
 *  Méthode  : La fonction qui lance la detection
 *  Arguments: -
 */
void detection::run()
{
    while(!(*frame).empty())
        {
            double t = (double)cvGetTickCount();

            Mat gray,img;
            int prediction=0,i=0,j=0;
            double confidence=0.0;


            // On convertit en gris et on égalise l'histogramme
            muteximg->lock();
            (*frame).copyTo(img);
            muteximg->unlock();

            cvtColor(img, gray, CV_BGR2GRAY);
            equalizeHist( gray, gray);

            haar_cascade.detectMultiScale(gray, facedetected,2.0);

            mutexlist->lock();
            int size=(*listfacetracked).size(); // on stock le nombre de visage tracké
            mutexlist->unlock();

            for( vector<Rect>::const_iterator r = facedetected.begin(); r != facedetected.end(); r++,j++)
                {
                    stat->NbDetection++;

                    Mat face(img,*r); // On récupère l'image du visage

                    // Recupère les données des rectangles
                    Rect temp_rec;
                    temp_rec=*r;
                    int width=temp_rec.width;
                    int height=temp_rec.height;

                    // On copie le visage à la taille détectée pour le tracking
                    Mat temp;
                    face.copyTo(temp);

                    cv::resize(face, face, cv::Size(im_width, im_height), 1.0, 1.0, cv::INTER_CUBIC);
                    cvtColor( face, templ, CV_BGR2GRAY ); // On la redimensionne et on la convertit en gris

                    model->predict(templ,prediction,confidence); // On devine l'id d'un nom inclus dans notre Base de données + distance de confidence

                    if(base_name[prediction] == *NomInVideoTest)
                        {
                            stat->NbReconnaissanceOkIdOK++;
                        }
                    else
                        {
                            stat->NbReconnaissanceOkIdKo++;
                        }

                    cout << confidence << endl;

                    if(size==0) // si aucun visage tracké
                        {

                            mutexlist->lock();
                            nouveau = Face(); // on remet a 0 la variable nouveau
                            temp.copyTo(nouveau.img);

                            if ((confidence)> 190)
                                {
                                    nouveau.name="";
                                    if(check_nameinDB(*NomInVideoTest))
                                        {
                                            stat->NbReconnaissanceKoIdConnu++;
                                        }
                                    else
                                        {
                                            stat->NbReconnaissanceKoIdInconnu++;
                                        }

                                }
                            else
                                {   nouveau.name = base_name[prediction];
                                    if(check_nameinDB(*NomInVideoTest) )
                                        {
                                            stat->NbReconnaissanceKoIdConnu++;
                                        }
                                    else
                                        {
                                            stat->NbReconnaissanceKoIdInconnu++;
                                        }
                                }

                            nouveau.windowsize=Size(width,height);
                            nouveau.trackingup=false;
                            nouveau.prevLoc=Point(facedetected[j].x,facedetected[j].y);

                            (*listfacetracked).push_back(nouveau);
                            mutexlist->unlock();
                        }
                else // si 1 visage ou + est tracké
                    {

                        int xi = facedetected[j].x;
                        int yi = facedetected[j].y;
                        int count=0;

                        mutexlist->lock();

                        for( i=0; i < size ; i++) // on test si le visage n'est pas le meme que les autres deja tracké
                            if(( (xi<((*listfacetracked)[i].prevLoc.x-50))||(xi>((*listfacetracked)[i].prevLoc.x+200))|| (yi<((*listfacetracked)[i].prevLoc.y-50)) || (yi>((*listfacetracked)[i].prevLoc.y+200)))&&(*listfacetracked)[i].trackingup)
                                count++;


                        if(count==size) // si count == size alors il est different de tous les visages tracké, donc on le rajoute a la liste de track
                            {
                                nouveau = Face(); // on remet a 0 la variable nouveau

                                temp.copyTo(nouveau.img);

                                if ((confidence)> 190)
                                    {
                                        nouveau.name="";
                                        if(check_nameinDB(*NomInVideoTest))
                                            {
                                                stat->NbReconnaissanceKoIdConnu ++;
                                            }
                                        else
                                            {
                                                stat->NbReconnaissanceKoIdInconnu++;
                                            }

                                    }
                                else
                                    {   nouveau.name = base_name[prediction];
                                        if(check_nameinDB(*NomInVideoTest) )
                                            {
                                                stat->NbReconnaissanceKoIdConnu ++;
                                            }
                                        else
                                            {
                                                stat->NbReconnaissanceKoIdInconnu++;
                                            }
                                    }
                                nouveau.windowsize=Size(width,height);
                                nouveau.trackingup=false;
                                nouveau.prevLoc=Point(xi,yi);
                                (*listfacetracked).push_back(nouveau);
                            }

                    mutexlist->unlock();
                }
            }

            t = (double)cvGetTickCount() - t;
            t = t/((double)cvGetTickFrequency()*1000);
            stat->TempsTraitement+=t;
        }
}
/*
 *  Méthode  : Lecture du fichier csv pour mettre à jour la base de donnée
 *  Arguments: le nom du fichier de type string
 *             le nom du visage correspondant de type string
 *             l'image de type vector Mat
 *             les labels de type vector de int
 *             caractère de séparation de type char
 */
void detection::read_csv(const string& filename,const string& dataname, vector<Mat>& images, vector<int>& labels, char separator)
{
    string line;

    //Ouverture du fichier database
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file)
        {
            string error_message = "No valid input file was given, please check the given filename.";
            CV_Error(CV_StsBadArg, error_message);
        }

    //Remplis les vecteurs à partir des lignes
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

    //Ouverture du fichier database_name
    std::ifstream file_name(dataname.c_str(), ifstream::in);
    if (!file_name)
        {
            string error_message = "No valid input file was given, please check the given filename.";
            CV_Error(CV_StsBadArg, error_message);
        }

    //Remplis la map à partir des lignes
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
/*
 * Methode  : Un drapeaud de vérification de la base donnée
 * Argument : le nom de type char
 */
bool detection::check_nameinDB(string name)
{
    int i=0;
    while(name != base_name[i])
        i++;
    int taille = base_name.size();
    if(i == taille)
        return false;
    else
        return true;

}
