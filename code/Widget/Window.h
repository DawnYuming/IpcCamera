/*
 * File  : Window.h
 * Breif : The base class of windows.
 */

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <QWidget>
#include <QLabel>
#include <QKeyEvent>

class Window : public QWidget
{
    friend class WinManager;
    Q_OBJECT
    Q_PROPERTY(int         screenWidth       READ width               NOTIFY sizeChanged)
    Q_PROPERTY(int         screenHeight      READ height              NOTIFY sizeChanged)

public:
    Window(QWidget *parent = 0);
    Window(QString name);
    ~Window();

    int getIndex();
    QString getName();

    void handleSetBackOrLogout(bool back);
    void setBackground(QString background_path);
    void setBackgroundStylesheet(QString stylesheet);

    virtual void enter_win();
    virtual void enterWin(QVariant args);
    virtual void exit_win();

signals:
    void sizeChanged();

protected:
    /* WARNING: Do not call! It is called by WinManager */
    void setIndex(int index);

private:
    int m_index;
    QString m_name;
    QLabel m_background;
};

#endif
