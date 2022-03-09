#ifndef GETAPP_H
#define GETAPP_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class getapp;
}

class getapp : public QDialog
{
    Q_OBJECT

public:
    explicit getapp(QWidget *parent = nullptr);
    ~getapp();

    void setTextBrowser(const QString &text);

private:
    Ui::getapp *ui;
};

#endif // GETAPP_H
