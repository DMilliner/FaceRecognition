#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QDialog>
#include "facedetection.h"

struct Values_Statistique;

namespace Ui
{
    class statistique;
}

class statistique : public QDialog
{
    Q_OBJECT
public:

    explicit statistique(QWidget *parent = 0);
    void set_stats(Values_Statistique stats);
    ~statistique();

    Ui::statistique *ui;
};

#endif // STATISTIQUE_H
