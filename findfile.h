#ifndef FINDFILE_H
#define FINDFILE_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class findfile;
}

class findfile : public QDialog
{
    Q_OBJECT

public:
    explicit findfile(QWidget *parent = nullptr);
    ~findfile();

    QString getSearchString();

private slots:
    void on_findBut_clicked();

    void on_cancelBut_clicked();

private:
    Ui::findfile *ui;
};

#endif // FINDFILE_H
