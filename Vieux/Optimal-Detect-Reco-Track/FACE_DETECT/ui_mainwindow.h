/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue May 21 15:03:47 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuitter;
    QAction *actionA_propos;
    QWidget *centralWidget;
    QPushButton *buttonAdd;
    QPushButton *buttonBrowser;
    QPushButton *buttonRun;
    QPushButton *buttonPause;
    QTextBrowser *textBrowser;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFace_tracker;
    QMenu *menuAide;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(714, 497);
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionA_propos = new QAction(MainWindow);
        actionA_propos->setObjectName(QString::fromUtf8("actionA_propos"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        buttonAdd = new QPushButton(centralWidget);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        buttonAdd->setGeometry(QRect(620, 420, 71, 31));
        buttonBrowser = new QPushButton(centralWidget);
        buttonBrowser->setObjectName(QString::fromUtf8("buttonBrowser"));
        buttonBrowser->setGeometry(QRect(290, 420, 51, 31));
        buttonRun = new QPushButton(centralWidget);
        buttonRun->setObjectName(QString::fromUtf8("buttonRun"));
        buttonRun->setGeometry(QRect(430, 420, 87, 31));
        buttonPause = new QPushButton(centralWidget);
        buttonPause->setObjectName(QString::fromUtf8("buttonPause"));
        buttonPause->setGeometry(QRect(530, 420, 71, 31));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 420, 271, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 631, 361));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 714, 25));
        menuFace_tracker = new QMenu(menuBar);
        menuFace_tracker->setObjectName(QString::fromUtf8("menuFace_tracker"));
        menuAide = new QMenu(menuBar);
        menuAide->setObjectName(QString::fromUtf8("menuAide"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFace_tracker->menuAction());
        menuBar->addAction(menuAide->menuAction());
        menuFace_tracker->addAction(actionQuitter);
        menuAide->addAction(actionA_propos);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("MainWindow", "quitter", 0, QApplication::UnicodeUTF8));
        actionA_propos->setText(QApplication::translate("MainWindow", "A propos", 0, QApplication::UnicodeUTF8));
        buttonAdd->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        buttonBrowser->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        buttonRun->setText(QApplication::translate("MainWindow", "Run", 0, QApplication::UnicodeUTF8));
        buttonPause->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        menuFace_tracker->setTitle(QApplication::translate("MainWindow", "fichier", 0, QApplication::UnicodeUTF8));
        menuAide->setTitle(QApplication::translate("MainWindow", "aide", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
