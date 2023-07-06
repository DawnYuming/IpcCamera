#ifndef IPCCAMERAAPPLICATION_H
#define IPCCAMERAAPPLICATION_H

#include <QObject>
#include <QApplication>
#include <QQmlEngine>
#include <QDebug>
#include <QTimer>
#include <QDesktopWidget>

#include "LoginModel.h"
#include "ApplicationContext.h"
#include "WinManager.h"
#include "DeclarativeWindow.h"

class IpcCameraApplication : public QObject
{
    Q_OBJECT
public:
    explicit IpcCameraApplication(int &argc, char **argv);

    void createWindow();
    void registerQmlTypes();
    void setApplicationContext();

    int run();
signals:

public slots:

private:
    QApplication m_app;
};

#endif // IPCCAMERAAPPLICATION_H
