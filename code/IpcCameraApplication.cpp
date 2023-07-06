#include "IpcCameraApplication.h"

IpcCameraApplication::IpcCameraApplication(int &argc, char **argv)
  : m_app(argc, argv)
{
    QRect rect = qApp->desktop()->screenGeometry();
    WinManager::instance()->setGeometry((rect.width()-1024)/2, (rect.height()-600)/2, 1024, 600);
    WinManager::instance()->setWindowArea(QRect(0, 0, 1024, 600));

    createWindow();
    setApplicationContext();
    registerQmlTypes();

    QTimer::singleShot(1000, this, [] {
//        WinManager::instance()->gotoWin("LoginWin");
        WinManager::instance()->gotoWin("MainWin");
    });
}

void IpcCameraApplication::setApplicationContext()
{
    ApplicationContext::instance()->setContext("winManager", WinManager::instance());
}

void IpcCameraApplication::createWindow()
{
//    WinManager::instance()->addWin(new DeclarativeWindow("LoginWin", QUrl("qrc:/Qml/LoginWin/LoginWin.qml")));
    WinManager::instance()->addWin(new DeclarativeWindow("MainWin", QUrl("qrc:/Qml/MainWin/MainWin.qml")));
}

void IpcCameraApplication::registerQmlTypes()
{
    qmlRegisterType<LoginModel> ("MyModels", 1, 0, "LoginModel");
}

int IpcCameraApplication::run()
{
    return m_app.exec();
}
