#include "dispetcher.h"
#include "ui_dispetcher.h"

#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>

Dispetcher::Dispetcher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dispetcher)
{
    ui->setupUi(this);
}

Dispetcher::~Dispetcher()
{
    delete ui;
}

void Dispetcher::on_pushButton_2_clicked()
{
    this->hide();
}


void Dispetcher::on_pushButton_clicked()
{
//     disp;

//    disp.codeText = ui->plainTextEdit->toPlainText();
//    disp.fullNameText = ui->plainTextEdit_2->toPlainText();
//    disp.codePasport = ui->plainTextEdit_3->toPlainText();
//    disp.numberPasport = ui->plainTextEdit_4->toPlainText();
//    disp.address = ui->plainTextEdit_5->toPlainText();

//    if (disp.codeText.isEmpty() or disp.fullNameText.isEmpty() or disp.address.isEmpty()){
//        QMessageBox::warning(this, "Ошибка", "Поля не заполнены!", QMessageBox::Cancel);
//    } else {
//        QString path("/files/");
//        QDir dir;

//        if (!dir.exists(path)){
//            dir.mkdir(path);
//        }

//        QString codeText = ui->plainTextEdit->toPlainText();
//        QFile file ("files/" + disp.codeText + "-" + disp.fullNameText + ".txt");

//        if (file.exists()){
//            QMessageBox::warning(this, "Ошибка", "Файл уже существует с таким кодом!");
//        }

//        if (!file.open(QIODevice::WriteOnly)){
//            QMessageBox::warning(this, "Ошибка", "Не удается открыть файл!");
//        }

//        QTextStream stream(&file);
//        stream << "Диспетчер данные \n";
//        stream << disp.codeText + "," + disp.fullNameText + "," + disp.codePasport + "," + disp.numberPasport + "," + disp.address + "\n";

//        QMessageBox::information(this, "Успешно", "Даныне успешно сохранены");

//        file.close();
//    }
}

