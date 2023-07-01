#include "IpcCameraApplication.h"
#include "ApplicationContext.h"
#include "WinManager.h"
#include "DeclarativeWindow.h"
#include <QDebug>
#include <QTimer>
#include <QDesktopWidget>

IpcCameraApplication::IpcCameraApplication(int &argc, char **argv)
  : m_app(argc, argv)
{
    QRect rect = qApp->desktop()->screenGeometry();
    WinManager::instance()->setGeometry((rect.width()-1024)/2, (rect.height()-600)/2, 1024, 600);
    WinManager::instance()->setWindowArea(QRect(0, 0, 1024, 600));

    createWindow();
    setApplicationContext();

    QTimer::singleShot(1000, this, [] {
        WinManager::instance()->gotoWin("Main");
    });
}

void IpcCameraApplication::setApplicationContext()
{
    ApplicationContext::instance()->setContext("winManager", WinManager::instance());
}

void IpcCameraApplication::createWindow()
{
    WinManager::instance()->addWin(new DeclarativeWindow("MainWin", QUrl("qrc:/main.qml")));
}

int IpcCameraApplication::run()
{
    return m_app.exec();
}
