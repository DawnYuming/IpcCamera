#include "LoginModel.h"

const QMap<QString, LoginModel::AccountType> accountTypeTable = {{QString("ema"), LoginModel::GENERAL}};
const QMap<QString, QString> accountTable = {{QString("ema"), QString("ematech")},
                                            {QString("root"), QString("180318li")}} ;

LoginModel::LoginModel(QObject *parent)
    : QObject(parent)
{
    m_account = "";
    m_passwd = "";
}

QString LoginModel::account() const
{
    return m_account;
}

QString LoginModel::passwd() const
{
    return m_passwd;
}

LoginModel::AccountType LoginModel::login(QString account, QString passwd)
{
    if (accountTable[account] == "") {
        return LoginModel::UNKNOW;
    }

    if (accountTable[account] != passwd) {
        return LoginModel::UNKNOW;
    }

    return accountTypeTable[account];
}
