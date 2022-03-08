#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QMessageBox"
#include "QDirIterator"
#include "QStringList"
#include "QTableWidget"
#include "QtGlobal"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Добавленный код. Генерация таблицы на главной странице
    QStringList headers;
    headers << "Статус заявки" << "Адрес клиента" << "Дата и время" << "Описание";

    /*
     * Фомирируем заголовок таблицы
     *      Назначаем размер полей
     *      Обработка директории с файлами
    */
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnHidden(5, true);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tableWidget->setColumnHidden(4, true);

    fillTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   adddataapp adddata;
   adddata.setModal(true);
   adddata.exec();
}


void MainWindow::on_tableWidget_itemSelectionChanged()
{
    qDebug() << ui->tableWidget->selectionModel()->selectedRows(4).value(0).data().toString();
}


void MainWindow::on_pushButton_4_clicked()
{
     QString pathName = ui->tableWidget->selectionModel()->selectedRows(4).value(0).data().toString();
     QDir dir;

     if (!dir.exists(pathName)){
         QMessageBox::warning(this, "Ошибка", "Такого файла не существует !");
     } else {
         QMessageBox msgBox;
         msgBox.setWindowTitle("Предупреждение");
         msgBox.setText("Вы действительно хотите удалить файл ?");
         msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
         msgBox.setButtonText(QMessageBox::Yes, tr("Да"));
         msgBox.setButtonText(QMessageBox::Cancel, tr("Нет"));
         msgBox.setDefaultButton(QMessageBox::Cancel);

         if(msgBox.exec() == QMessageBox::Yes){
            dir.remove(pathName);
         }
     }
}

void MainWindow::fillTable()
{
    qDebug() << "FILTABLE";

    QDir dir;

    QString statusApp;
    QString addressClient;
    QString dateTime;
    QString description;
    QColor color;
    QString toolTip;

    int row = 0;

    QDirIterator iterator(dir.currentPath() + "/files/", QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        QFile file(iterator.next());
        if ( file.open(QIODevice::ReadOnly) ) {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);


            QString fileName = file.fileName();
            QStringList list = fileName.split("status");

            statusApp = list[1].split("-")[1];
            if (statusApp == "1"){
                statusApp = "Новая заявка";
                toolTip = "Новая заявка необходимо обработать!";
                color = Qt::green;
            } else if (statusApp == "2") {
                statusApp = "Заявка выполнена";
                toolTip = "Заявка была выполнена!";
                color = Qt::gray;
            } else if (statusApp == "3"){
                statusApp = "Заявка отклонена";
                toolTip = "Заявка была отклонена!";
                color = Qt::yellow;
            } else {
                statusApp = "Не определен";
                toolTip = "Статус заявки не определен!";
                color = Qt::red;
            }

            QString dataFile = file.readAll();
            QStringList objectList = dataFile.split("|");

            QStringList flutList = objectList[1].split(",");
            addressClient = flutList[4];

            QStringList appList = objectList[2].split(",");
            dateTime = appList[2];
            description = appList[4];

            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(statusApp));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(addressClient));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(dateTime));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(description));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(fileName));

            ui->tableWidget->item(row, 0)->setBackground(QBrush(color));
            ui->tableWidget->item(row, 0)->setToolTip(toolTip);
            ui->tableWidget->item(row, 1)->setBackground(QBrush(color));
            ui->tableWidget->item(row, 2)->setBackground(QBrush(color));
            ui->tableWidget->item(row, 3)->setBackground(QBrush(color));

            row++;
        } else {
            qDebug() << "Can't open " << file.fileName() << file.errorString();
        }
    }

    row = 0;
}

