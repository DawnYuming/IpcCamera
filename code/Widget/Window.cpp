/*
 * File  : Window.cpp
 * Breif : Implementation of Window.h
 */

#include "Window.h"
#include "WinManager.h"
#include <assert.h>

Window::Window(QWidget *parent)
    : QWidget(parent),
      m_background(this)
{
    QRect rect = WinManager::instance()->getWindowArea();
    setGeometry(rect.x(), rect.y(), rect.width(), rect.height());
}

Window::Window(QString name)
    : m_index(0),
      m_name(name),
      m_background(this)
{
    QRect rect = WinManager::instance()->getWindowArea();
    setGeometry(rect.x(), rect.y(), rect.width(), rect.height());
}

Window::~Window()
{
}

int Window::getIndex()
{
    return m_index;
}

void Window::setIndex(int index)
{
    m_index = index;
}

QString Window::getName()
{
    return m_name;
}

void Window::setBackground(QString backgroundPath)
{
    m_background.setGeometry(0, 0, width(), height());
    m_background.setPixmap(QPixmap(backgroundPath));
}

void Window::setBackgroundStylesheet(QString stylesheet)
{
    m_background.setGeometry(0, 0, width(), height());
    m_background.setStyleSheet(stylesheet);
}

void Window::enter_win() {
    /* do nothing */
}

void Window::enterWin(QVariant args) {
    Q_UNUSED(args);
    /* do nothing */
}

void Window::exit_win() {
    /* do nothing */
}
