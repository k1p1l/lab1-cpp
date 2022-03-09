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

private:
    Ui::updateapp *ui;
};

#endif // UPDATEAPP_H
