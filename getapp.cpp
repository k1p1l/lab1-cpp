#include "getapp.h"
#include "ui_getapp.h"

getapp::getapp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getapp)
{
    ui->setupUi(this);
}

getapp::~getapp()
{
    delete ui;
}

void getapp::setTextBrowser(const QString &text){
    QString message;

    QStringList listData = text.split("|");
    QString dispData = listData[0];
    QString clientData = listData[1];
    QString appData = listData[2];

    QStringList dispList = dispData.split(",");
    QStringList clientList = clientData.split(",");
    QStringList appList = appData.split(",");

    QString statusApp;
    if (appList[3] == "1"){
        statusApp = "Новая заявка";
    } else if (appList[3] == "2") {
        statusApp = "Заявка выполнена";
    } else if (appList[3] == "3"){
        statusApp = "Заявка отклонена";
    } else {
        statusApp = "Не определен";
    }

    message = "<html>";
    message += "<h3 align=\"right\">Код заявки" + appList[0] + " - " + appList[1] +"</h3> <h3 align=\"right\">Заявка создана от: " +  appList[2] + "</h3>";
    message += "<h3 align=\"right\">Статус заявки: " + statusApp + "</h3>";

    message += "<h2 align=\"center\"> Заявление </h2>";
    message += "<h3 align=\"center\"> Постпиуло обращение от квартиросьемщика " + clientList[1] + ", проживайюший по адресу (" + clientList[4] + ") </h3>";
    message += "<h3 align=\"center\"> Описание обращения: " + appList[4] + "</h3>";

    message += "<div>";
    message += "<table width=\"100%\">";

        message += "<tr> <td align=\"left\">Исполнитель: " + dispList[1] + "</td>";
        message += "<td align=\"right\">Заказчик: " + clientList[1] + "</td></tr>";

        message += "<tr> <td align=\"left\"> Серия паспорта: " + dispList[2] + "</td>";
        message += "<td align=\"right\"> Серия паспорта:  " + appList[2] + "</td>";

        message += "<tr> <td align=\"left\"> Номер паспорта: " + dispList[3] + "</td>";
        message += "<td align=\"right\"> Номер паспорта:  " + appList[3] + "</td>";

        message += "<tr> <td align=\"left\"> Подпись: ___________________ </td>";
        message += "<td align=\"right\"> Подпись: ___________________ </td>";

    message += "</table>";
    message += "</div>";
    message += "</html>";


    ui->textBrowser->setText(message);
}
