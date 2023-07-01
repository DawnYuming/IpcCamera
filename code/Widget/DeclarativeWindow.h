#ifndef _CPP_DECLARATIVE_WINDOW_H
#define _CPP_DECLARATIVE_WINDOW_H

#include "Window.h"
#include <QTimer>
#ifdef QT4VERSION
#include <QtDeclarative/QDeclarativeView>
#else
#include <QQuickWidget>
#endif

class DeclarativeWindow : public Window
{
    Q_OBJECT
public:
    DeclarativeWindow();
    DeclarativeWindow(QString name, QUrl qmlSource);
    ~DeclarativeWindow();

    void enter_win();
    void enterWin(QVariant args);
    void exit_win();

public slots:
    void timeOutCreateQml();
    void onResize(QSize size);

protected:
#ifdef QT4VERSION
    QDeclarativeView *getView();
#else
    QQuickWidget *getView();
#endif

private:
    void init(QUrl qmlSource);
    void setApplicationContextProperties();

private:
#ifdef QT4VERSION
    QDeclarativeView *m_view;
#else
    QQuickWidget *m_view;
#endif
    QTimer  m_createQml;
    QUrl m_qmlSource;
};

#endif // DECLARATIVEWINDOW_H
