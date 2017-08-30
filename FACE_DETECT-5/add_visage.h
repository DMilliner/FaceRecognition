#ifndef ADD_VISAGE_H
#define ADD_VISAGE_H

#include <QDialog>
#include <iostream>

#include "QMessageBox"

#include "QDir"
#include "QTextStream"

namespace Ui
{
    class add_visage;
}

class add_visage : public QDialog
{
    Q_OBJECT
    
    public:
        explicit add_visage(QWidget *parent = 0);
        ~add_visage();
        void setImage(QImage frame);
        void save_database(const std::string& filename,QString path_toSave,QString id);
        void save_databaseName(const std::string& filename,QString name_toSave,QString id_toSave, char separator);
        Ui::add_visage *ui;
        QImage image;



    public slots:
        void on_buttonOk_clicked();
        void on_buttonCancel_clicked();
};

#endif // ADD_VISAGE_H
