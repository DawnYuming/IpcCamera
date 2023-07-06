#ifndef LOGINMODEL_H
#define LOGINMODEL_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QDebug>

class LoginModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString account  READ account NOTIFY accountChanged)
    Q_PROPERTY(QString passwd   READ passwd  NOTIFY accountChanged)

public:
    typedef enum {
        MANAGER,
        GENERAL,
        UNKNOW = -1,
    }AccountType;

     Q_ENUM(AccountType)

public:
    explicit LoginModel(QObject *parent = nullptr);

    QString account() const;
    QString passwd() const;

    Q_INVOKABLE LoginModel::AccountType login(QString account, QString passwd);

signals:
    void accountChanged();

private:
    QString m_account;
    QString m_passwd;
};

#endif // LOGINMODEL_H
