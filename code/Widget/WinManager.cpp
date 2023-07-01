/*
 * File  : WinManager.cpp
 */

#include "WinManager.h"
#include <assert.h>
#ifdef Q_OS_UNIX
#include <unistd.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <QDebug>

#include "Toast.h"

using namespace std;

const int SLIDING_TIME = 250; /* millisecond */
WinManager *WinManager::_instance = nullptr;

WinManager::WinManager(QWidget *parent)
    : QWidget(parent),
      m_stack(this),
      m_window_default_bg(),
      m_filter_mouse(false),
      m_filter_key(false)
{
//    setGeometry(QApplication::desktop()->screenGeometry());
    drawBlackBackground();

    m_stack.setGeometry(0, 0, width(), height());
    m_stack.setSpeed(SLIDING_TIME);
    m_stack.setAnimation(QEasingCurve::InOutCubic);
    m_stack.show();
    connect(&m_stack, SIGNAL(animationFinished()), this, SLOT(onSwitchWinDone()));

//    Toast::setDefaultFontSize(18);
}

WinManager::~WinManager() {
}

void WinManager::drawBlackBackground() {
//    setAutoFillBackground(true);
//    QPalette pal(palette());
//    pal.setColor(QPalette::Window, QColor(Qt::black));
//    setPalette(pal);
    show();
}

void WinManager::setWindowArea(QRect rect) {
    m_stack.resize(rect.width(), rect.height());
    m_stack.move(rect.x(), rect.y());
}

QRect WinManager::getWindowArea() {
    return QRect(m_stack.x(), m_stack.y(), m_stack.width(), m_stack.height());
}

void WinManager::setWindowDefaultBackgroud(QString background_path) {
    m_window_default_bg = background_path;
}

void WinManager::onSwitchWinDone() {
    assert(m_stack.count() > 0);
}

WinManager *WinManager::instance() {
    if (_instance == nullptr) {
        _instance = new WinManager();
    }
    return _instance;
}

void WinManager::addWin(DeclarativeWindow *win) {
    assert(win);

    win->setIndex(m_stack.count());
    m_stack.addWidget(win);

    if (! m_window_default_bg.isEmpty())
        win->setBackground(m_window_default_bg);
}

void WinManager::gotoWin(int winIndex) {
    if (m_stack.isSliding()) {
        return;
    }

    if (winIndex >= 0 && winIndex < m_stack.count() ) {
        Window * win = (Window *)m_stack.widget(winIndex);
        win->setFocus();

        getCurrentWin()->exit_win();

        m_stack.slideInIdx(winIndex);
    }
}

void WinManager::gotoWin(QString name) {
    if (m_stack.isSliding()) {
        return;
    }

    for (int i = 0; i < m_stack.count(); i++) {
        Window * win = (Window *)m_stack.widget(i);
        if (win->getName().compare(name) == 0) {
            win->setFocus();
            win->enter_win();
            getCurrentWin()->exit_win();

            m_stack.slideInIdx(win->getIndex());
            break;
        }
    }
}

void WinManager::gotoWinWithArgs(QString name, QVariant args){
    if (m_stack.isSliding()) {
        return;
    }

    for (int i = 0; i < m_stack.count(); i++) {
        Window * win = (Window *)m_stack.widget(i);
        if (win->getName().compare(name) == 0) {
            win->setFocus();
            win->enterWin(args);
            getCurrentWin()->exit_win();

            m_stack.slideInIdx(win->getIndex());
            break;
        }
    }
}

void WinManager::gotoWinWithArgs(int winIndex, QVariant args) {
    Q_UNUSED(winIndex)
    Q_UNUSED(args)
    if (m_stack.isSliding()) {
        return;
    }
}

void WinManager::startWin(Window *win) {
    assert(win);
    if (m_stack.isSliding()) {
        return;
    }

    if (!m_window_default_bg.isEmpty())
        win->setBackground(m_window_default_bg);

    win->setFocus();
    win->show();
    m_stack.addWidget(win);

    if (m_stack.count() == 1) {
        /* the root window */
        win->enter_win();
    }
    else {
        /* switch to new window */
        getCurrentWin()->exit_win();
        m_stack.slideInNext();
    }
}

void WinManager::back() {
    if (m_stack.isSliding()) {
        return;
    }

    if (m_stack.count() > 1) {
        getCurrentWin()->exit_win();
        m_stack.slideInPrevDelNew();
    }
}

void WinManager::showPopupMessage(QString text, PopupMessageType type, int duringSec)
{
    Window *win = getCurrentWin();
    Toast *toast = new Toast(win);

    toast->move((win->width() - toast->width())/2, win->height() - toast->height() - 100);
    toast->setText(text);

    if (type == SUCCEEDED_TYPE) {
        toast->setBackgroundColor(Qt::green);
    }

    if (type == ERROR_TYPE) {
        toast->setBackgroundColor(Qt::red);
    }

    toast->setDuring(duringSec * 2000);
    toast->show();
}

Window *WinManager::getCurrentWin() {
    assert(m_stack.count() > 0);
    return dynamic_cast<Window *>(m_stack.currentWidget());
}

Window *WinManager::getWin(int index) {
    assert(index >= 0 && index < m_stack.count());
    return dynamic_cast<Window *>(m_stack.widget(index));
}

void WinManager::setSlidingTime(int time) {
    m_stack.setSpeed(time);
}

bool WinManager::eventFilter(QObject *target, QEvent *event)
{
    if (m_stack.isSliding()) {
        if (event->type() == QEvent::MouseButtonPress ||
                event->type() == QEvent::MouseButtonRelease) {
            return true;
        }
    }

    if (event->type() == QEvent::MouseButtonPress ||
            event->type() == QEvent::MouseButtonRelease) {

    }

    return QWidget::eventFilter(target, event);
}

void WinManager::resizeEvent(QResizeEvent *e)
{
    setWindowArea(QRect(0,0,e->size().width(),e->size().height()));
    emit sizeChanged(e->size());
}
