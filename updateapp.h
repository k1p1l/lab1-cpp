#ifndef UPDATEAPP_H
#define UPDATEAPP_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class updateapp;
}

class updateapp : public QDialog
{
    Q_OBJECT

public:
    explicit updateapp(QWidget *parent = nullptr);
    ~updateapp();

    void updateApp(const QString &text);

private slots:
    void on_saveAppBut_clicked();

    void on_successStatusBox_stateChanged(int arg1);

    void on_newStatusBox_stateChanged(int arg1);

    void on_rejectStatusBox_stateChanged(int arg1);

private:
    Ui::updateapp *ui;
};

#endif // UPDATEAPP_H
