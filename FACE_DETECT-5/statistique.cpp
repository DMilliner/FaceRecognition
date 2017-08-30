/*******************************/
/*        Les Includes         */
/*******************************/

#include "statistique.h"
#include "ui_statistique.h"

/*******************************/
/*           Le Code           */
/*******************************/

/*
 *  Méthode  :  Constructeur de la fenêtre de statistique.
 *  Argument :  une fentre parent de type Qwidget
 *  Hérite de:  parent une fentre de type QDialog
 *              ui un objet de la classe Statistique
 */
statistique::statistique(QWidget *parent) : QDialog(parent),ui(new Ui::statistique)
{
    ui->setupUi(this);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_5->setEnabled(false);
    ui->lineEdit_6->setEnabled(false);
    ui->lineEdit_7->setEnabled(false);
}

/*
 *  Méthode  :  Destructeur de la fenêtre d'ajout de Visage.
 */
statistique::~statistique()
{
    delete ui;
}

/*
 *  Méthode  :  Définit les valeurs de statistique.
 *  Arguments:  les valeurs de la structure Statistique
 */
void statistique::set_stats(Values_Statistique stats)
{
    QString info_1,info_2,info_3,info_4,info_5, info_6, info_7;

    info_1.sprintf("%g",stats.NbDetection);
    info_2.sprintf("%g",stats.NbFrame);
    int taux = stats.TauxDeDetection;

    info_3.sprintf("%g",stats.NbReconnaissanceOkIdOK);
    info_4.sprintf("%g",stats.NbReconnaissanceOkIdKo);
    info_5.sprintf("%g",stats.NbReconnaissanceKoIdInconnu);
    info_6.sprintf("%g",stats.NbReconnaissanceKoIdConnu);

    int taux_Reco = stats.TauxDeReconnaissance;

    info_7.sprintf("%g",stats.TempsTraitement);


    ui->lineEdit->setText(info_1);
    ui->lineEdit_2->setText(info_2);
    ui->progressBar->setValue(taux);

    ui->lineEdit_3->setText(info_3);
    ui->lineEdit_4->setText(info_4);
    ui->lineEdit_5->setText(info_5);
    ui->lineEdit_6->setText(info_6);
    ui->progressBar_2->setValue(taux_Reco);

    ui->lineEdit_7->setText(info_7);

}

