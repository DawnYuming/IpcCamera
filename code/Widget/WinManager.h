/*
 * Brief: Manager all the windows. It is a singleton!
 */

#ifndef _WIN_MANAGER_H_
#define _WIN_MANAGER_H_

#include "DeclarativeWindow.h"
#include "SlidingStackedWidget.h"
#include <QObject>
#include <QTimer>
#include <QVariant>
#include <QColor>
#include <QWidget>

class WinManager : public QWidget
{
    Q_OBJECT
public:
    static WinManager *instance();

    enum PopupMessageType {
        SUCCEEDED_TYPE,
        NORMAL_TYPE,
        WARNING_TYPE,
        ERROR_TYPE
    };

    /* window switch */
    Q_INVOKABLE void gotoWin(QString name);
    Q_INVOKABLE void gotoWinWithArgs(QString name, QVariant args);
    Q_INVOKABLE void gotoWinWithArgs(int winIndex, QVariant args);
    Q_INVOKABLE void back();
    Q_INVOKABLE void showPopupMessage(QString text, PopupMessageType type = NORMAL_TYPE, int duringSec = 2);

    void startWin(Window *win);
    void gotoWin(int winIndex);

    /* window manager */
    void addWin(DeclarativeWindow *win);
    Window *getWin(int id);
    Window *getCurrentWin();

    /* layout */
    void  setWindowArea(QRect rect);
    QRect getWindowArea();
    void  setWindowDefaultBackgroud(QString background_path); // would not affect windows started.
    void  setSlidingTime(int time); /* millisecond */

signals:
    void touchScreen();
    void sizeChanged(QSize);

protected:
    WinManager(QWidget *parent = 0);
    ~WinManager();

    bool eventFilter(QObject *target, QEvent *event);
    void resizeEvent(QResizeEvent *e);

private slots:
    void onSwitchWinDone();

private:
    void drawBlackBackground();

    static WinManager   *_instance;
    SlidingStackedWidget m_stack;
    QString              m_window_default_bg;
    bool                 m_filter_mouse;
    bool                 m_filter_key;
};

#endif
