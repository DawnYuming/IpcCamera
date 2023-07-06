#include "DeclarativeWindow.h"
#include "ApplicationContext.h"
#include <stdio.h>
#ifdef QT4VERSION
#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeEngine>
#else
#include <QtQml>
#include <QQuickItem>
#include <QQuickWidget>
#endif
#include <QDebug>
#include "WinManager.h"

using namespace std;

DeclarativeWindow::DeclarativeWindow()
{
    init(QUrl());
}

DeclarativeWindow::DeclarativeWindow(QString name, QUrl qmlSource)
    : Window(name),
      m_view(nullptr),
      m_createQml(this)
{
    m_qmlSource = qmlSource;
    m_createQml.setSingleShot(true);
    connect(&m_createQml,  SIGNAL(timeout()),   this,  SLOT(timeOutCreateQml()));
    m_createQml.start(1000);
}

void DeclarativeWindow::timeOutCreateQml()
{
    init(m_qmlSource);
}

void DeclarativeWindow::onResize(QSize size)
{
    this->resize(size);
    m_view->resize(size);
    emit sizeChanged();
}

void DeclarativeWindow::init(QUrl qmlSource)
{
#ifdef QT4VERSION
    m_view = new QDeclarativeView(this);
    m_view->setWindowFlags(Qt::FramelessWindowHint);
    m_view->setAttribute(Qt::WA_TranslucentBackground);
    m_view->setStyleSheet("background:transparent;");
    m_view->adjustSize();
    m_view->move(0,0);
    m_view->show();
#else
     m_view = new QQuickWidget(this);
     m_view->setWindowFlags(Qt::FramelessWindowHint);
     m_view->setAttribute(Qt::WA_AcceptTouchEvents);
     m_view->setStyleSheet("background:transparent;");
     m_view->adjustSize();
     m_view->move(0,0);
     m_view->resize(this->size());

    m_view->installEventFilter(this);
    connect(WinManager::instance(), SIGNAL(sizeChanged(QSize)), this, SLOT(onResize(QSize)));
#endif

    /*
     * Add a context so we can access current window object
     * in QML using variable 'window'
     */

    m_view->rootContext()->setContextProperty("_window", this);

    setApplicationContextProperties();

    if (! qmlSource.isEmpty())
        m_view->setSource(qmlSource);

    m_view->show();
}

DeclarativeWindow::~DeclarativeWindow()
{
    if (m_view)
        delete m_view;
}

void DeclarativeWindow::setApplicationContextProperties()
{
    map<QString,QObject*> contextMap = ApplicationContext::instance()->getContextMap();
    map<QString,QObject*>::iterator iter;

    for (iter = contextMap.begin(); iter != contextMap.end(); iter++)
    {
        m_view->rootContext()->setContextProperty(iter->first, iter->second);
    }
}

#ifdef QT4VERSION
QDeclarativeView* DeclarativeWindow::getView()
#else
QQuickWidget *DeclarativeWindow::getView()
#endif
{
    return m_view;
}

void DeclarativeWindow::enter_win()
{
    if (m_view)
        QMetaObject::invokeMethod(m_view->rootObject(), "enterWin");
}

void DeclarativeWindow::enterWin(QVariant args)
{
    if (m_view)
        QMetaObject::invokeMethod(m_view->rootObject(), "enterWinWithArgs", Q_ARG(QVariant, args));
}

void DeclarativeWindow::exit_win()
{
    if (m_view)
        QMetaObject::invokeMethod(m_view->rootObject(), "exitWin");
}

