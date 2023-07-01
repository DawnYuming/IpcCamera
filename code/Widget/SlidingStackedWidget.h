#ifndef SLIDINGSTACKEDWIDGET_H
#define SLIDINGSTACKEDWIDGET_H

#include <QtGui>
#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QEasingCurve>
#include <QStackedWidget>

#define USB_QLABEL_MOVICE
/*
 * Description:
 * SlidingStackedWidget is a class that is derived from QtStackedWidget
 * and allows smooth side shifting of widgets, in addition
 * to the original hard switching from one to another as offered by
 * QStackedWidget itself.
 */
class SlidingStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    /* This enumeration is used to define the animation direction */
    enum t_direction {
        LEFT2RIGHT,
        RIGHT2LEFT,
        TOP2BOTTOM,
        BOTTOM2TOP,
        AUTOMATIC
    };

    SlidingStackedWidget(QWidget *parent);
    ~SlidingStackedWidget(void);

    bool isSliding();

public slots:
    void setSpeed(int speed);   /* animation duration in milliseconds */
    void setAnimation(enum QEasingCurve::Type animationtype); /* check out the QEasingCurve documentation for different styles */
    void setVerticalMode(bool vertical=true);
    void setWrap(bool wrap); /* wrapping is related to slideInNext/Prev;it defines the behaviour when reaching last/first page */

    void slideInNext();
    void slideInPrev();
    void slideInIdx(int idx, enum t_direction direction=AUTOMATIC);
    void slideInPrevDelNew(); /* added by Jack */

signals:
    void animationFinished(void);

protected slots:
    void animationDoneSlot(void);
    void animationDoneSlotDelNew(void); /* added by Jack */

protected:
    void slideInWgt(QWidget * widget, enum t_direction direction=AUTOMATIC);

    QWidget *m_mainwindow;

    int m_speed;
    enum QEasingCurve::Type m_animationtype;
    bool m_vertical;
    int m_now;
    int m_next;
    bool m_wrap;
    QPoint m_pnow;
    bool m_active;
#ifdef USB_QLABEL_MOVICE
    QLabel*   m_pic_slide_next;
    QLabel*   m_pic_slide_now;
#endif
    QParallelAnimationGroup *m_animgroup;

    QList<QWidget*> blockedPageList;
};

#endif // SLIDINGSTACKEDWIDGET_H
