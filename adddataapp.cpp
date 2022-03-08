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
    struct structFlat flat;
    struct structApplication app;

    disp.code = ui->codeTextEdit->toPlainText();
    disp.fullName = ui->fullNameTextEdit->toPlainText();
    disp.codePasport = ui->codePasportTextEdit->toPlainText();
    disp.numberPasport = ui->numbetPasportTextEdit->toPlainText();
    disp.address = ui->addressTextEdit->toPlainText();

    flat.code = ui->codeFlutTextEdit->toPlainText();
    flat.fullName = ui->fullNameFlutTextEdit->toPlainText();
    flat.codePasport = ui->codePasportFlutTextEdit->toPlainText();
    flat.numberPassport = ui->numbetPasportFlutTextEdit->toPlainText();
    flat.address = ui->addressFlutTextEdit->toPlainText();

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


    if (app.codeDispetcher != disp.code or app.codePeople != flat.code){
        QMessageBox::warning(this, "Ошибка", "Данные не корректные !");
    }

    if (disp.code.isEmpty() or disp.address.isEmpty() or flat.code.isEmpty() or flat.address.isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Данные не могут быть пустыми ! Заполните все поля", QMessageBox::Cancel);
    } else {
        QString path("/files/");
        QDir dir;

        if (!dir.exists(path)){
            dir.mkdir(path);
        }

        QString fileName = "status" + app.status + "-" + disp.code + "-" + flat.code + "-" + app.dateTime.toString("yyyy-MM-dd");
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
            dataFile += flat.code + "," + flat.fullName + "," + flat.codePasport + "," + flat.numberPassport + "," + flat.address + "|";
            dataFile += app.codeDispetcher + "," + app.codePeople + "," + app.dateTime.toString("yyyy-MM-dd") + "," + app.status + "," + app.comment + "\n";
             //todo Дописать
            stream << dataFile;

            QMessageBox::information(this, "Успешно", "Даныне успешно сохранены");
            file.close();

            this->hide();

            qDebug() << "KEK";

            this->updateTable();

            qDebug() << "PET";
        }
    }

}

void adddataapp::on_newStatusBox_stateChanged(int arg1)
{
    if (ui->newStatusBox->isChecked()){
        ui->rejectStatusBox->setCheckState(Qt::Unchecked);
        ui->successStatusBox->setCheckState(Qt::Unchecked);
    }
}

void adddataapp::on_successStatusBox_stateChanged(int arg1)
{
    if (ui->successStatusBox->isChecked()){
        ui->rejectStatusBox->setCheckState(Qt::Unchecked);
        ui->newStatusBox->setCheckState(Qt::Unchecked);
    }
}


void adddataapp::on_rejectStatusBox_stateChanged(int arg1)
{
    if (ui->rejectStatusBox->isChecked()){
        ui->successStatusBox->setCheckState(Qt::Unchecked);
        ui->newStatusBox->setCheckState(Qt::Unchecked);
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

void adddataapp::updateTable()
{
    qDebug() << "USE";

    MainWindow mv = new MainWindow();
    mv.fillTable();
}
