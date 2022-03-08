#ifndef DISPETCHER_H
#define DISPETCHER_H

#include <QDialog>

namespace Ui {
class Dispetcher;
}

class Dispetcher : public QDialog
{
    Q_OBJECT

public:
    explicit Dispetcher(QWidget *parent = nullptr);
    ~Dispetcher();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Dispetcher *ui;
};

#endif // DISPETCHER_H
