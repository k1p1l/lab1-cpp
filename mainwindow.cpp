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
    ui->tableWidget->setColumnHidden(4, true); // Скрытый столбец, для хранения пути к файлу

    fillTable(NULL);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Метод для отображения окна (Добавление новой заявки)
 *      Кнопка на экране (Добавить заявку)
 *
 * @brief MainWindow::on_pushButton_clicked
 */
void MainWindow::on_pushButton_clicked()
{
   adddataapp adddata;
   adddata.setModal(true);
   adddata.exec();
}


/**
 * Метод для тестирования
 *      Ищется название файал, имеется сркытый столбец, который хранит путь к файлу
 *
 * @brief MainWindow::on_tableWidget_itemSelectionChanged
 */
void MainWindow::on_tableWidget_itemSelectionChanged()
{
    qDebug() << ui->tableWidget->selectionModel()->selectedRows(4).value(0).data().toString();
}

/**
 * Удаление файла и удаление строчки из файла
 *      Кнопка на экране (Удалить заявку)
 *
 * @brief MainWindow::on_pushButton_4_clicked
 */
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

            QModelIndexList selection = ui->tableWidget->selectionModel()->selectedRows();
            for(int i=0; i< selection.count(); i++)
            {
                QModelIndex index = selection.at(i);
                ui->tableWidget->removeRow(index.row() - 1);
            }
         }
     }
}

/**
 * Метод для вывод информации в таблицу
 *
 * @brief MainWindow::fillTable
 */
void MainWindow::fillTable(QString searchParam = NULL)
{
    qDebug() << "FILTABLE";

    QDir dir;

    // Обьявление переменных
    QString statusApp;
    QString addressClient;
    QString dateTime;
    QString description;
    QColor color;
    QString toolTip;

    int row = 0;  

    // Пробегаемся по директории с файлами
    QDirIterator iterator(dir.currentPath() + "/files/", QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        QFile file(iterator.next());
        // Открываем каждый файл в отдельности. Цикл.
        if ( file.open(QIODevice::ReadOnly) ) {

            if (!file.exists()){
                return;
            }

            if (!searchParam.isEmpty()){
                QString fileName = file.fileName();
                if (!fileName.contains(searchParam)){
                    continue;
                }
            }

            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

            // Формируем данные
            QString fileName = file.fileName();
            QStringList list = fileName.split("status");
            statusApp = list[1].split("-")[0];

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

            // Заполняем данные таблицы
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

            file.close();
        } else {
            qDebug() << "Can't open " << file.fileName() << file.errorString();
        }
    }

    row = 0;
}

/**
 * Метод для генерации окна, детальная информация по заявке
 *      Кнопка на экране (Распечатать заявку)
 *
 * @brief MainWindow::on_pushButton_5_clicked
 */
void MainWindow::on_pushButton_5_clicked()
{
    QString pathName = ui->tableWidget->selectionModel()->selectedRows(4).value(0).data().toString();
    QDir dir;

    if (!dir.exists(pathName)){
        QMessageBox::warning(this, "Ошибка", "Выберите заявку");
    } else {
        QFile file(pathName);

        if ( file.open(QIODevice::ReadOnly) ) {
             QString data = file.readAll();
             file.close();

             getapp windowGetApp;
             windowGetApp.setTextBrowser(data);
             windowGetApp.exec();
        } else {
           QMessageBox::warning(this, "Ошибка", "Не удалось прочитать файл");
        }
    }
}

/**
 * Обновление таблицы.
 *      Кнопка на экране (Обновить таблицу)
 *
 * @brief MainWindow::on_pushButton_6_clicked
 */
void MainWindow::on_pushButton_6_clicked()
{
     fillTable();
}

/**
 * Обновление данных по заявке.
 *      Кнопка на экране (Обновить заявку)
 *
 * @brief MainWindow::on_pushButton_2_clicked
 */
void MainWindow::on_pushButton_2_clicked()
{
    QString pathName = ui->tableWidget->selectionModel()->selectedRows(4).value(0).data().toString();
    QDir dir;

    if (!dir.exists(pathName)){
        QMessageBox::warning(this, "Ошибка", "Выберите заявку");
    } else {
        QFile file(pathName);

        if ( file.open(QIODevice::WriteOnly|QIODevice::ReadOnly) ) {
             QString data = file.readAll();
             file.close();

             qDebug() << "Select file: " + file.fileName();
             qDebug() << "Status file: " + QString::number(file.isOpen());

             updateapp windowUpdateApp;
             windowUpdateApp.updateApp(data);
             windowUpdateApp.exec();
        } else {
           QMessageBox::warning(this, "Ошибка", "Не удалось прочитать файл");
        }
    }
}

/**
 * Поиск файлов по фильтру
 *      Кнопка на экране (Найти заявку)
 *
 * @brief MainWindow::on_pushButton_3_clicked
 */
void MainWindow::on_pushButton_3_clicked()
{
    findfile windowFindFile;
    windowFindFile.exec();

    QString searchString = windowFindFile.getSearchString();
    QString trimSearchString = searchString.trimmed().toLower().replace(" ", "");
    QString statusSearch;

    if (trimSearchString == "clearfilter"){
        ui->tableWidget->clear();

        this->fillTable(NULL);
        return;
    }

    if (trimSearchString.contains("новаязаявка")){
        statusSearch = "status1";
    } else if (trimSearchString.contains("заявкаотклонена")){
        statusSearch = "status3";
    } else if (trimSearchString.contains("заявкавыполнена")){
        statusSearch = "status2";
    }

    qDebug() << "TRIM: " + trimSearchString;
    qDebug() << "Status: " + statusSearch;

    QDir dir;
    QDirIterator iterator(dir.currentPath() + "/files/", QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        iterator.next();
        QString fileName = iterator.fileName();

        qDebug() << "String: " + fileName;

        if (!statusSearch.isEmpty() and fileName.contains(statusSearch)){
            ui->tableWidget->clear();

            this->fillTable(statusSearch);
        }
    }
}

