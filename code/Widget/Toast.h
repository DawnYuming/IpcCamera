#ifndef TOAST_H
#define TOAST_H

#include <QLabel>

class QLabel;

class Toast : public QWidget
{
    Q_OBJECT
public:
    /* Create a Toast for display text message. */
    // static Toast * makeTextToast(QString text, int duringMsec, QWidget *parent);
    // static Toast * makeTextToast(QString text, QColor textColor, QColor background, int duringMsec, QWidget *parent);

    static void setDefaultFontSize(int fontSize);
    static void setDefaultMarginBottom(int marginBottom);
    static void setDefaultBackgroundColor(const QColor &color);
    static void setDefaultTextColor(const QColor &color);

    /* Contrustors */
    Toast(QWidget *parent = 0);

    /*
     * Show the toast, and it automatically disappear and destroy itself
     * after the during time.
     */
    Q_INVOKABLE void show();

    int getDuring() const;
    void setDuring(int duringMsec);

    QColor getBackgroundColor() const;
    void setBackgroundColor(const QColor& color);

    void setTextColor(const QColor& color);

    void setText(QString text);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    static int    s_fontSize;
    static int    s_marginBottom;
    static QColor s_defaultBackgroundColor;
    static QColor s_defaultTextColor;
    static Toast  *s_lastInstance;

    QLabel     *m_label;
    QString    m_message;
    QColor     m_backgroundColor;
    int        m_duringMsec;
    int        m_timerId;
};

#endif // TOAST_H
