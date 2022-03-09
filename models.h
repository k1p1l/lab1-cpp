#ifndef MODELS_H
#define MODELS_H

#include "QString"
#include "QDateTime"

//  Обьект Диспетчер
struct strucDispetcher {
    QString code; // Код диспетчера
    QString fullName; // ФИО диспетчера
    QString codePasport; // Код паспорта
    QString numberPasport; // Номер паспорта
    QString address; // Адрес
};

// Обьект Квартира
struct structClient {
    QString code; // Код человека
    QString fullName; // ФИО человека
    QString codePasport; // Код паспорта
    QString numberPassport; // Номер паспорта
    QString address; // Адрес
};

// Обьект Заявка
struct structApplication {
    QString codeDispetcher;
    QString codePeople;
    QDateTime dateTime;
    QString comment;
    QString status;
};

class Models
{
public:
    Models();
};

#endif // MODELS_H
