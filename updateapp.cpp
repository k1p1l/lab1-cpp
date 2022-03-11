#include "updateapp.h"
#include "ui_updateapp.h"

#include "QMessageBox"
#include "QDir"

QString originalNameFile;

updateapp::updateapp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateapp)
{
    ui->setupUi(this);
}

updateapp::~updateapp()
{
    delete ui;
}

/**
 * Заполнение данных на странице
 *      Полученные данные из файла, передаются в параметре метода
 *          Заполняем поля данными
 *
 * @brief updateapp::updateApp
 * @param text
 */
void updateapp::updateApp(const QString &text){
    QString message;

    QStringList listData = text.split("|");
    QString dispData = listData[0];
    QString clientData = listData[1];
    QString appData = listData[2];

    QStringList dispList = dispData.split(",");
    ui->codeTextEdit->setPlainText(dispList[0]);
    ui->fullNameTextEdit->setPlainText(dispList[1]);
    ui->codePasportTextEdit->setPlainText(dispList[2]);
    ui->numbetPasportTextEdit->setPlainText(dispList[3]);
    ui->addressTextEdit->setPlainText(dispList[4]);

    QStringList clientList = clientData.split(",");
    ui->codeFlutTextEdit->setPlainText(clientList[0]);
    ui->fullNameFlutTextEdit->setPlainText(clientList[1]);
    ui->codePasportFlutTextEdit->setPlainText(clientList[2]);
    ui->numbetPasportFlutTextEdit->setPlainText(clientList[3]);
    ui->addressFlutTextEdit->setPlainText(clientList[4]);

    QStringList appList = appData.split(",");
    ui->codeDispAppTextEdit->setPlainText(dispList[0]);
    ui->codeFlutAppTextEdit->setPlainText(clientList[0]);
    ui->dateTimeAppEdit->setDateTime(QDateTime::fromString(appList[2], "yyyy-MM-dd"));

    if (appList[3] == "1"){
        ui->newStatusBox->setChecked(true);
    } else if (appList[3] == "2"){
        ui->successStatusBox->setChecked(true);
    } else if (appList[3] == "3"){
        ui->rejectStatusBox->setChecked(true);
    } else {
        ui->rejectStatusBox->setChecked(true);
    }

    ui->commentTextEdit->setPlainText(appList[4]);

    originalNameFile = "status" + appList[3] + "-" + dispList[0] + "-" + clientList[0] + "-" + appList[2] + ".txt";
}

/**
 * Сохраняем данные из полей в структуру
 *      Записываем данные из стркутры в файл
 *
 * @brief updateapp::on_saveAppBut_clicked
 */
void updateapp::on_saveAppBut_clicked()
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
    }

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

        QMessageBox msgBox;

        if (!dir.exists("files/"+originalNameFile)){
            QMessageBox::warning(this, "Ошибка", "Такого файла не существует !");
        } else {
            msgBox.setWindowTitle("Предупреждение");
            msgBox.setText("Вы действительно хотите удалить файл ?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
            msgBox.setButtonText(QMessageBox::Yes, tr("Да"));
            msgBox.setButtonText(QMessageBox::Cancel, tr("Нет"));
            msgBox.setDefaultButton(QMessageBox::Cancel);
        }

        if (file.exists()){
            QMessageBox::warning(this, "Ошибка", "Файл уже существует с таким кодом!");
        } else {
            if (!file.open(QIODevice::WriteOnly)){
                QMessageBox::warning(this, "Ошибка", "Не удается открыть файл!");
            } else {
                if(msgBox.exec() == QMessageBox::Yes){
                    QString entryAbsPath = dir.absolutePath() + "/files/" + originalNameFile;
                    QFile::setPermissions(entryAbsPath, QFile::ReadOwner | QFile::WriteOwner);
                    QFile::remove(entryAbsPath);
                }

                QTextStream stream(&file);
                QString dataFile;

                dataFile = disp.code + "," + disp.fullName + "," + disp.codePasport + "," + disp.numberPasport + "," + disp.address + "|";
                dataFile += cleint.code + "," + cleint.fullName + "," + cleint.codePasport + "," + cleint.numberPassport + "," + cleint.address + "|";
                dataFile += app.codeDispetcher + "," + app.codePeople + "," + app.dateTime.toString("yyyy-MM-dd") + "," + app.status + "," + app.comment + "\n";
                 //todo Дописать
                stream << dataFile;

                QMessageBox::information(this, "Успешно", "Даныне успешно сохранены");
                file.close();

                this->hide();
            }
        }
    }
}


void updateapp::on_successStatusBox_stateChanged(int arg1)
{
    if (ui->newStatusBox->isChecked()){
        ui->rejectStatusBox->setChecked(false);
        ui->successStatusBox->setChecked(false);
    }
}


void updateapp::on_newStatusBox_stateChanged(int arg1)
{
    if (ui->newStatusBox->isChecked()){
        ui->rejectStatusBox->setChecked(false);
        ui->successStatusBox->setChecked(false);
    }
}


void updateapp::on_rejectStatusBox_stateChanged(int arg1)
{
    if (ui->rejectStatusBox->isChecked()){
        ui->successStatusBox->setChecked(false);
        ui->newStatusBox->setChecked(false);
    }
}

