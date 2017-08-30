/********************************************************************************
** Form generated from reading UI file 'stastisque.ui'
**
** Created: Thu May 23 15:58:44 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STASTISQUE_H
#define UI_STASTISQUE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_stastisque
{
public:
    QLabel *label_7;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_6;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_7;
    QProgressBar *progressBar;
    QLabel *label_2;
    QLabel *label_8;
    QLabel *label;
    QLabel *label_6;

    void setupUi(QDialog *stastisque)
    {
        if (stastisque->objectName().isEmpty())
            stastisque->setObjectName(QString::fromUtf8("stastisque"));
        stastisque->resize(357, 445);
        label_7 = new QLabel(stastisque);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 90, 171, 21));
        plainTextEdit = new QPlainTextEdit(stastisque);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(80, 20, 191, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Abyssinica SIL"));
        font.setPointSize(20);
        plainTextEdit->setFont(font);
        label_3 = new QLabel(stastisque);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 280, 111, 21));
        lineEdit_3 = new QLineEdit(stastisque);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(210, 190, 113, 25));
        lineEdit_5 = new QLineEdit(stastisque);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(210, 270, 113, 25));
        lineEdit = new QLineEdit(stastisque);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(210, 90, 113, 25));
        lineEdit_2 = new QLineEdit(stastisque);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(210, 120, 113, 25));
        lineEdit_6 = new QLineEdit(stastisque);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(210, 300, 113, 25));
        label_4 = new QLabel(stastisque);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 310, 111, 21));
        label_5 = new QLabel(stastisque);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 150, 161, 21));
        pushButton = new QPushButton(stastisque);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(230, 400, 87, 27));
        lineEdit_4 = new QLineEdit(stastisque);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(210, 220, 113, 25));
        lineEdit_7 = new QLineEdit(stastisque);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(210, 350, 113, 25));
        progressBar = new QProgressBar(stastisque);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(210, 150, 111, 21));
        progressBar->setValue(24);
        label_2 = new QLabel(stastisque);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 230, 111, 21));
        label_8 = new QLabel(stastisque);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 360, 161, 21));
        label = new QLabel(stastisque);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 200, 111, 21));
        label_6 = new QLabel(stastisque);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 120, 161, 21));

        retranslateUi(stastisque);

        QMetaObject::connectSlotsByName(stastisque);
    } // setupUi

    void retranslateUi(QDialog *stastisque)
    {
        stastisque->setWindowTitle(QApplication::translate("stastisque", "Dialog", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("stastisque", "Nombre de reconnaissance", 0, QApplication::UnicodeUTF8));
        plainTextEdit->setPlainText(QApplication::translate("stastisque", "STATISTIQUES", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("stastisque", "Vrais n\303\251gatifs", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("stastisque", "Faux n\303\251gatifs", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("stastisque", "Taux de reconnaissance", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("stastisque", "OK", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("stastisque", "Faux positifs", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("stastisque", "Temps de traitement", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("stastisque", "Vrais positifs", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("stastisque", "Nombre de frames", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class stastisque: public Ui_stastisque {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STASTISQUE_H
