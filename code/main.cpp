#include <QGuiApplication>
#include "IpcCameraApplication.h"
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    IpcCameraApplication app(argc, argv);

    return app.run();
}
