/*******************************/
/*        Les Includes         */
/*******************************/

#include "add_visage.h"
#include "ui_add_visage.h"
#include "facedetection.h"


/*******************************/
/*           Le Code           */
/*******************************/

using namespace std;


/*
 *  Méthode  :  Constructeur de la fenêtre d'ajout de Visage.
 */
add_visage::add_visage(QWidget *parent) : QDialog(parent), ui(new Ui::add_visage)
{
    ui->setupUi(this);
}

/*
 *  Méthode  :  Destructeur de la fenêtre d'ajout de Visage.
 */
add_visage::~add_visage()
{
    delete ui;
}

/*
 *  Méthode  : Initialise l'image du visage
 *  Arguments: Une image de type QImage
 */
void add_visage::setImage(QImage frame)
{
    image=frame;
    ui->image->setPixmap(QPixmap::fromImage(image));
}

/*
 *  Méthode  : Actions réalisées lors du clique sur OK
 *  Arguments: -
 */
void add_visage::on_buttonOk_clicked()
{
    QString name;
    QString path;

    QString id;
    QDir dir;

    name = ui->lineEdit->text();
    id = ui->spinBox->text();

    if(!name.isEmpty())
        {
            // Créer le dossier
            dir.mkpath("./BaseDeDonnee/"+id);
            path="./BaseDeDonnee/"+id+"/"+name+".png";

            // Sauvegarde l'image
            image.save(path);

            // Sauvegarde du chemin + id dans "./Database.txt"
            save_database("./Database.txt",path,id);
            save_databaseName("./DatabaseName.txt",name,id,';');

            close();

        }
    else
        close();
}

/*
 *  Méthode  : Actions réalisées lors du clique sur Annuler
 *  Arguments: -
 */
void add_visage::on_buttonCancel_clicked()
{
    close();
}

/*
 *  Méthode  : Sauvegarde de la Base de Donnée
 *  Arguments: le nom du fichier de type string
 *             le chemin pour la sauvegarde de type Qstring
 *             l'id de type Qstring
 */
void add_visage::save_database(const string& filename,QString path_toSave,QString id)
{
    // Sauvegarde le chemin dans la database.txt
    QFile file(filename.c_str());

    file.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream flux(&file);

    flux.setCodec("UTF-8");

    path_toSave = path_toSave+";"+id;
    flux << path_toSave << endl;

    file.close();

}

/*
 *  Méthode  : Sauvegarde de le nom dans la Base de Donnée
 *  Arguments: le nom du fichier de type string
 *             le chemin pour la sauvegarde de type Qstring
 *             l'id de type Qstring
 *             le caractère de séparation de type char
 */
void add_visage::save_databaseName(const std::string& filename,QString name_toSave,QString id_toSave, char separator)
{
    string line;
    bool save=true;

    //Supprime le _# à la fin du nom
    int taille = name_toSave.toStdString().find('_');
    QString temp(name_toSave.toStdString().substr(0,taille).c_str());
    name_toSave = temp;


    //Ouverture du fichier DatabaseName
    std::ifstream file(filename.c_str(), ifstream::in);

    if (!file)
        {
            string error_message = "No valid input file was given, please check the given filename.";
            CV_Error(CV_StsBadArg, error_message);
        }

    string name, id;

    //On regarde si une ligne correspond
    while (getline(file, line))
        {
            stringstream liness(line);
            getline(liness, name, separator);
            getline(liness, id);
            if(!name.empty() && !id.empty())
                {
                    if(id == id_toSave.toStdString())
                        {
                            save=false;
                        }
                }
        }
    // On a pas trouvé de ligne identique, on l'ajoute à la fin du fichier.
    if(save)
        save_database("./DatabaseName.txt",name_toSave,id_toSave);
}
