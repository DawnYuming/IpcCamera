#ifndef CAMERACLIENT_H
#define CAMERACLIENT_H

#include <QObject>

class CameraClient : public QObject
{
    Q_OBJECT
public:
    explicit CameraClient(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CAMERACLIENT_H