#ifndef WINMANAGER_H
#define WINMANAGER_H

#include <QObject>
#include <QWidget>

class WinManager : public QWidget
{
    Q_OBJECT
public:
    explicit WinManager(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // WINMANAGER_H