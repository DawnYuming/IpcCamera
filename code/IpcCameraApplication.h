#ifndef IPCCAMERAAPPLICATION_H
#define IPCCAMERAAPPLICATION_H

#include <QObject>
#include <QApplication>

class IpcCameraApplication : public QObject
{
    Q_OBJECT
public:
    explicit IpcCameraApplication(int &argc, char **argv);

    void setApplicationContext();
    void createWindow();
    int run();
signals:

public slots:

private:
    QApplication m_app;
};

#endif // IPCCAMERAAPPLICATION_H
