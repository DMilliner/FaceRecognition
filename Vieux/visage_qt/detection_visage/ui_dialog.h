/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Thu Feb 7 19:08:05 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label_avant;
    QLabel *label_apres;
    QPushButton *bouton_pause;
    QPlainTextEdit *txt_erreur;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(981, 460);
        Dialog->setAutoFillBackground(true);
        label_avant = new QLabel(Dialog);
        label_avant->setObjectName(QString::fromUtf8("label_avant"));
        label_avant->setGeometry(QRect(8, 8, 480, 360));
        label_avant->setMinimumSize(QSize(480, 360));
        label_avant->setMaximumSize(QSize(480, 360));
        label_avant->setAutoFillBackground(false);
        label_apres = new QLabel(Dialog);
        label_apres->setObjectName(QString::fromUtf8("label_apres"));
        label_apres->setGeometry(QRect(496, 8, 480, 360));
        label_apres->setMinimumSize(QSize(480, 360));
        label_apres->setMaximumSize(QSize(480, 360));
        label_apres->setAutoFillBackground(false);
        bouton_pause = new QPushButton(Dialog);
        bouton_pause->setObjectName(QString::fromUtf8("bouton_pause"));
        bouton_pause->setGeometry(QRect(156, 400, 106, 29));
        txt_erreur = new QPlainTextEdit(Dialog);
        txt_erreur->setObjectName(QString::fromUtf8("txt_erreur"));
        txt_erreur->setGeometry(QRect(496, 372, 477, 84));
        txt_erreur->setReadOnly(true);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_avant->setText(QString());
        label_apres->setText(QString());
        bouton_pause->setText(QApplication::translate("Dialog", "pause", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
