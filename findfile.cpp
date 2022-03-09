#include "findfile.h"
#include "ui_findfile.h"

#include "QMessageBox"

findfile::findfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findfile)
{
    ui->setupUi(this);
}

findfile::~findfile()
{
    delete ui;
}

QString findfile::getSearchString()
{
    return ui->textEdit->toPlainText();
}

void findfile::on_findBut_clicked()
{
    QMessageBox::information(this, "Предупреждение", "Возможна небольшая задержка. Мы ищем нужные файлы");
    this->hide();
}


void findfile::on_cancelBut_clicked()
{
    ui->textEdit->setText("Clear filter");
    this->hide();
}

