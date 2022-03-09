#ifndef ADDDATAAPP_H
#define ADDDATAAPP_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class adddataapp;
}

class adddataapp : public QDialog
{
    Q_OBJECT

public:
    explicit adddataapp(QWidget *parent = nullptr);
    ~adddataapp();

    void updateTable();

signals:

private slots:
    void on_saveAppBut_clicked();

    void on_newStatusBox_stateChanged(int arg1);

    void on_successStatusBox_stateChanged(int arg1);

    void on_rejectStatusBox_stateChanged(int arg1);

    void on_codeTextEdit_modificationChanged(bool arg1);

    void on_codeFlutTextEdit_modificationChanged(bool arg1);

private:
    Ui::adddataapp *ui;
};

#endif // ADDDATAAPP_H
