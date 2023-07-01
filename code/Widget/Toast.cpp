#include "Toast.h"

//#include "TestedBoardInfo.h"

#include <QTimerEvent>
#include <QLabel>
#include <QHBoxLayout>
#include <QFont>
#include <QDebug>


int Toast::s_fontSize = 20;
int Toast::s_marginBottom = 20;
QColor Toast::s_defaultBackgroundColor = QColor(Qt::white);
QColor Toast::s_defaultTextColor = QColor(Qt::black);
Toast* Toast::s_lastInstance = nullptr;

void Toast::setDefaultFontSize(int fontSize)
{
    s_fontSize = fontSize;
}

void Toast::setDefaultMarginBottom(int marginBottom)
{
    s_marginBottom = marginBottom;
}

void Toast::setDefaultBackgroundColor(const QColor &color)
{
    s_defaultBackgroundColor = color;
}

void Toast::setDefaultTextColor(const QColor &color)
{
    s_defaultTextColor = color;
}

Toast::Toast(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_TranslucentBackground, true);

    QFont font;
//    font.setPointSize(s_fontSize * TestedBoardInfo::instance()->getScaleFactor());

    QPalette palette;
    palette.setColor(QPalette::WindowText, s_defaultTextColor);
    palette.setColor(QPalette::Background, s_defaultBackgroundColor);
    setAutoFillBackground(true);
    setPalette(palette);

    QHBoxLayout *layout = new QHBoxLayout(this);
    m_label = new QLabel();
    m_label->setFont(font);
    m_label->setStyleSheet("background:white; border:2px solid gray; border-radius:10px; ");
    layout->addWidget(m_label);

    hide();
}

void Toast::show()
{
    m_timerId = startTimer(m_duringMsec);
    QWidget::show();
}

int Toast::getDuring() const
{
    return m_duringMsec;
}

void Toast::setDuring(int duringMsec)
{
    m_duringMsec = duringMsec;
}

QColor Toast::getBackgroundColor() const
{
    return m_backgroundColor;
}
#include <QDebug>
void Toast::setBackgroundColor(const QColor& color)
{
    m_label->setStyleSheet(QString("color:white; background:%1; border:2px solid %2; border-radius:10px;").arg(color.name()).arg(color.name()));
}

void Toast::setTextColor(const QColor& color)
{
    m_label->setStyleSheet(QString("color:white; background:%1; border:2px solid %2; border-radius:10px; ").arg(color.name()).arg(color.name()));
}

void Toast::setText(QString text)
{
    m_label->setText(text);
}

void Toast::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId) {
        hide();
        this->deleteLater();
    }
}
