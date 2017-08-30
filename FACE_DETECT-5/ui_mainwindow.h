/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue May 28 15:13:14 2013
**      by: Qt User Interface Compiler version 4.8.3
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
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(714, 625);
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionA_propos = new QAction(MainWindow);
        actionA_propos->setObjectName(QString::fromUtf8("actionA_propos"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        buttonAdd = new QPushButton(centralWidget);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        buttonAdd->setGeometry(QRect(618, 560, 71, 31));
        buttonBrowser = new QPushButton(centralWidget);
        buttonBrowser->setObjectName(QString::fromUtf8("buttonBrowser"));
        buttonBrowser->setGeometry(QRect(30, 560, 51, 31));
        buttonRun = new QPushButton(centralWidget);
        buttonRun->setObjectName(QString::fromUtf8("buttonRun"));
        buttonRun->setGeometry(QRect(446, 560, 87, 31));
        buttonPause = new QPushButton(centralWidget);
        buttonPause->setObjectName(QString::fromUtf8("buttonPause"));
        buttonPause->setGeometry(QRect(540, 560, 71, 31));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(30, 520, 661, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 640, 480));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
