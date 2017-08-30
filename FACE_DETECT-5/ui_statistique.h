/********************************************************************************
** Form generated from reading UI file 'statistique.ui'
**
** Created: Tue May 28 15:13:14 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTIQUE_H
#define UI_STATISTIQUE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_statistique
{
public:
    QLineEdit *lineEdit_7;
    QLabel *label_5;
    QProgressBar *progressBar;
    QLineEdit *lineEdit_5;
    QLabel *label;
    QLabel *label_6;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_2;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_8;
    QLineEdit *lineEdit;
    QProgressBar *progressBar_2;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_6;
    QLabel *label_10;

    void setupUi(QDialog *statistique)
    {
        if (statistique->objectName().isEmpty())
            statistique->setObjectName(QString::fromUtf8("statistique"));
        statistique->resize(320, 374);
        lineEdit_7 = new QLineEdit(statistique);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(170, 330, 113, 25));
        label_5 = new QLabel(statistique);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 80, 161, 21));
        progressBar = new QProgressBar(statistique);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(170, 80, 111, 21));
        progressBar->setValue(24);
        lineEdit_5 = new QLineEdit(statistique);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(170, 160, 113, 25));
        label = new QLabel(statistique);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 140, 111, 21));
        label_6 = new QLabel(statistique);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 50, 161, 21));
        lineEdit_3 = new QLineEdit(statistique);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(170, 130, 113, 25));
        lineEdit_2 = new QLineEdit(statistique);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(170, 50, 113, 25));
        label_7 = new QLabel(statistique);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 20, 131, 21));
        label_4 = new QLabel(statistique);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 170, 111, 21));
        label_8 = new QLabel(statistique);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 330, 131, 21));
        lineEdit = new QLineEdit(statistique);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(170, 20, 113, 25));
        progressBar_2 = new QProgressBar(statistique);
        progressBar_2->setObjectName(QString::fromUtf8("progressBar_2"));
        progressBar_2->setGeometry(QRect(170, 260, 111, 21));
        progressBar_2->setValue(24);
        label_9 = new QLabel(statistique);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 260, 161, 21));
        label_11 = new QLabel(statistique);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 230, 111, 21));
        label_3 = new QLabel(statistique);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 200, 111, 21));
        lineEdit_4 = new QLineEdit(statistique);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(170, 190, 113, 25));
        lineEdit_6 = new QLineEdit(statistique);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(170, 220, 113, 25));
        label_10 = new QLabel(statistique);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(290, 330, 21, 21));

        retranslateUi(statistique);

        QMetaObject::connectSlotsByName(statistique);
    } // setupUi

    void retranslateUi(QDialog *statistique)
    {
        statistique->setWindowTitle(QApplication::translate("statistique", "Statistiques", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("statistique", "Taux de d\303\251tection", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("statistique", "Vrais positifs", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("statistique", "Nombre de frames", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("statistique", "Nombre de d\303\251tection", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("statistique", "Faux positifs", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("statistique", "Temps de traitement", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("statistique", "Taux de Reconnaissance", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("statistique", "Faux n\303\251gatifs", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("statistique", "Vrais n\303\251gatifs", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("statistique", "ms", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class statistique: public Ui_statistique {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTIQUE_H
