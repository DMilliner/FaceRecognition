/********************************************************************************
** Form generated from reading UI file 'add_visage.ui'
**
** Created: Tue May 21 15:03:47 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_VISAGE_H
#define UI_ADD_VISAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_add_visage
{
public:
    QLabel *image;
    QLabel *explications;
    QLineEdit *lineEdit;
    QPushButton *buttonCancel;
    QPushButton *buttonOk;
    QSpinBox *spinBox;

    void setupUi(QDialog *add_visage)
    {
        if (add_visage->objectName().isEmpty())
            add_visage->setObjectName(QString::fromUtf8("add_visage"));
        add_visage->resize(248, 350);
        image = new QLabel(add_visage);
        image->setObjectName(QString::fromUtf8("image"));
        image->setGeometry(QRect(50, 40, 160, 160));
        explications = new QLabel(add_visage);
        explications->setObjectName(QString::fromUtf8("explications"));
        explications->setGeometry(QRect(30, 230, 201, 16));
        lineEdit = new QLineEdit(add_visage);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 260, 131, 21));
        buttonCancel = new QPushButton(add_visage);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setGeometry(QRect(130, 300, 87, 27));
        buttonOk = new QPushButton(add_visage);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setGeometry(QRect(30, 300, 87, 27));
        spinBox = new QSpinBox(add_visage);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(170, 260, 41, 25));

        retranslateUi(add_visage);

        QMetaObject::connectSlotsByName(add_visage);
    } // setupUi

    void retranslateUi(QDialog *add_visage)
    {
        add_visage->setWindowTitle(QApplication::translate("add_visage", "Dialog", 0, QApplication::UnicodeUTF8));
        image->setText(QString());
        explications->setText(QApplication::translate("add_visage", "Veuiller saisir le nom du visage :", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("add_visage", "Annuler", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("add_visage", "Ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class add_visage: public Ui_add_visage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_VISAGE_H
