#include "adddataapp.h"
#include "ui_adddataapp.h"
#include "mainwindow.h"

#include "models.h"

#include <QApplication>
#include "QMessageBox"
#include "QDir"

adddataapp::adddataapp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adddataapp)
{
    ui->setupUi(this);
    ui->dateTimeAppEdit->setDateTime(QDateTime::currentDateTime());
}

adddataapp::~adddataapp()
{
    delete ui;
}

void adddataapp::on_saveAppBut_clicked()
{
    struct strucDispetcher disp;
    struct structClient cleint;
    struct structApplication app;

    disp.code = ui->codeTextEdit->toPlainText();
    disp.fullName = ui->fullNameTextEdit->toPlainText();
    disp.codePasport = ui->codePasportTextEdit->toPlainText();
    disp.numberPasport = ui->numbetPasportTextEdit->toPlainText();
    disp.address = ui->addressTextEdit->toPlainText();

    cleint.code = ui->codeFlutTextEdit->toPlainText();
    cleint.fullName = ui->fullNameFlutTextEdit->toPlainText();
    cleint.codePasport = ui->codePasportFlutTextEdit->toPlainText();
    cleint.numberPassport = ui->numbetPasportFlutTextEdit->toPlainText();
    cleint.address = ui->addressFlutTextEdit->toPlainText();

    app.codeDispetcher = ui->codeDispAppTextEdit->toPlainText();
    app.codePeople = ui->codeFlutAppTextEdit->toPlainText();
    app.comment = ui->commentTextEdit->toPlainText();
    app.dateTime = ui->dateTimeAppEdit->dateTime();

    if (ui->newStatusBox->isChecked()){
        app.status = "1";
    } else if (ui->successStatusBox->isChecked()){
        app.status = "2";
    } else if (ui->rejectStatusBox->isChecked()){
        app.status = "3";
    }


    if (app.codeDispetcher != disp.code or app.codePeople != cleint.code){
        QMessageBox::warning(this, "Ошибка", "Данные не корректные !");
    } else {
        if (disp.code.isEmpty() or disp.address.isEmpty() or cleint.code.isEmpty() or cleint.address.isEmpty()){
            QMessageBox::warning(this, "Ошибка", "Данные не могут быть пустыми ! Заполните все поля", QMessageBox::Cancel);
        } else {
            QString path("/files/");
            QDir dir;

            if (!dir.exists(path)){
                dir.mkdir(path);
            }

            QString fileName = "status" + app.status + "-" + disp.code + "-" + cleint.code + "-" + app.dateTime.toString("yyyy-MM-dd");
            QFile file ("files/" + fileName + ".txt");

            if (file.exists()){
                QMessageBox::warning(this, "Ошибка", "Файл уже существует с таким кодом!");
            }

            if (!file.open(QIODevice::WriteOnly)){
                QMessageBox::warning(this, "Ошибка", "Не удается открыть файл!");
            } else {
                QTextStream stream(&file);
                QString dataFile;

                dataFile = disp.code + "," + disp.fullName + "," + disp.codePasport + "," + disp.numberPasport + "," + disp.address + "|";
                dataFile += cleint.code + "," + cleint.fullName + "," + cleint.codePasport + "," + cleint.numberPassport + "," + cleint.address + "|";
                dataFile += app.codeDispetcher + "," + app.codePeople + "," + app.dateTime.toString("yyyy-MM-dd") + "," + app.status + "," + app.comment + "\n";

                stream << dataFile;
                file.close();

                this->hide();

                QMessageBox::information(this, "Успешно", "Даныне успешно сохранены");
            }
    }
    }

}

void adddataapp::on_newStatusBox_stateChanged(int arg1)
{
    if (ui->newStatusBox->isChecked()){
        ui->rejectStatusBox->setChecked(false);
        ui->successStatusBox->setChecked(false);
    }
}

void adddataapp::on_successStatusBox_stateChanged(int arg1)
{
    if (ui->successStatusBox->isChecked()){
        ui->rejectStatusBox->setChecked(false);
        ui->newStatusBox->setChecked(false);
    }
}


void adddataapp::on_rejectStatusBox_stateChanged(int arg1)
{
    if (ui->rejectStatusBox->isChecked()){
        ui->successStatusBox->setChecked(false);
        ui->newStatusBox->setChecked(false);
    }
}

void adddataapp::on_codeTextEdit_modificationChanged(bool arg1)
{
    QString codeDisp = ui->codeTextEdit->toPlainText();
    ui->codeDispAppTextEdit->setPlainText(codeDisp);
    ui->codeTextEdit->redo();
}


void adddataapp::on_codeFlutTextEdit_modificationChanged(bool arg1)
{
    QString codeDisp = ui->codeFlutTextEdit->toPlainText();
    ui->codeFlutAppTextEdit->setPlainText(codeDisp);
    ui->codeTextEdit->redo();
}
