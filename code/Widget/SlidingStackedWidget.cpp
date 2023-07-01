#include "SlidingStackedWidget.h"

SlidingStackedWidget::SlidingStackedWidget(QWidget *parent)
    : QStackedWidget(parent) {
    if (parent != 0) {
        m_mainwindow = parent;
    }
    else {
        m_mainwindow = this;
        qDebug()<<"ATTENTION: untested mainwindow case !";
    }
    /* Parent should not be 0; not tested for any other case yet !! */

#ifdef Q_OS_SYMBIAN
#ifndef __S60_50__
    qDebug()<< "WARNING: ONLY TESTED AND 5TH EDITION";
#endif
#endif

    m_vertical = false;
    m_speed    = 500;
    m_now      = 0;
    m_next     = 0;
    m_wrap     = false;
    m_pnow     = QPoint(0,0);
    m_active   = false;
    m_animationtype = QEasingCurve::Linear;//OutBounce;//OutBack;
#ifdef USB_QLABEL_MOVICE
    m_pic_slide_next = new QLabel(this);
    m_pic_slide_now = new QLabel(this);
#endif
    m_animgroup = new QParallelAnimationGroup;
}

SlidingStackedWidget::~SlidingStackedWidget(){
#ifdef USB_QLABEL_MOVICE
    m_pic_slide_next->clear();
    delete m_pic_slide_next;
    m_pic_slide_now->clear();
    delete m_pic_slide_now;
#endif
    while(m_animgroup->animationCount()){
        m_animgroup->animationAt(0)->deleteLater();
        m_animgroup->removeAnimation(m_animgroup->animationAt(0));
    }
    m_animgroup->clear();
    m_animgroup->deleteLater();
    m_animgroup = NULL;
}

bool SlidingStackedWidget::isSliding() {
    return m_active;
}

void SlidingStackedWidget::setVerticalMode(bool vertical) {
    m_vertical = vertical;
}

void SlidingStackedWidget::setSpeed(int speed) {
    m_speed = speed;
}

void SlidingStackedWidget::setAnimation(enum QEasingCurve::Type animationtype) {
    m_animationtype = animationtype;
}

void SlidingStackedWidget::setWrap(bool wrap) {
    m_wrap = wrap;
}

void SlidingStackedWidget::slideInNext() {
    int now = currentIndex();
    if (m_wrap || (now < this->count() - 1))
        slideInIdx(now + 1);
}

void SlidingStackedWidget::slideInPrev() {
    int now = currentIndex();
    if (m_wrap || (now > 0))
        slideInIdx(now - 1);
}

void SlidingStackedWidget::slideInPrevDelNew() {
    int now = currentIndex();
    if (m_wrap || (now > 0))
        slideInIdx(now - 1);
}

void SlidingStackedWidget::animationDoneSlotDelNew(void) {
    QWidget *widget = this->widget(this->count() - 1);
    removeWidget(widget);
    widget->deleteLater();
}

void SlidingStackedWidget::slideInIdx(int idx, enum t_direction direction) {
    if (idx > this->count() - 1) {
        direction = m_vertical ? TOP2BOTTOM : RIGHT2LEFT;
        idx = idx % count();
    }
    else if (idx < 0) {
        direction = m_vertical ? BOTTOM2TOP: LEFT2RIGHT;
        idx = (idx + this->count()) % count();
    }
    slideInWgt(this->widget(idx), direction);
}

void SlidingStackedWidget::slideInWgt(QWidget *newwidget, enum t_direction direction) {
    if (m_active) {
        return;
        /* At the moment, do not allow re-entrance before an animation is completed.
         * other possibility may be to finish the previous animation abrupt, or
         * to revert the previous animation with a counter animation, before going ahead
         * or to revert the previous animation abrupt
         * and all those only, if the newwidget is not the same as that of the previous running animation.
         */
    }
    else {
        m_active = true;
    }

    enum t_direction directionhint;
    int now  = this->currentIndex();
    int next = this->indexOf(newwidget);
    if (now == next) {
        m_active = false;
        return;
    }
    else if (now < next){
        directionhint = m_vertical ? TOP2BOTTOM : RIGHT2LEFT;
    }
    else {
        directionhint = m_vertical ? BOTTOM2TOP : LEFT2RIGHT;
    }
    if (direction == AUTOMATIC) {
        direction = directionhint;
    }
    /* NOW....calculate the shifts */
    int offsetx = frameRect().width();  /* Inherited from mother */
    int offsety = frameRect().height(); /* Inherited from mother */

    /* The following is important, to ensure that the new widget
       has correct geometry information when sliding in first time */
    widget(next)->setGeometry (0, 0, offsetx, offsety);

    if (direction == BOTTOM2TOP)  {
        offsetx = 0;
        //offsety = -offsety;
    }
    else if (direction == TOP2BOTTOM) {
        offsetx = 0;
        offsety = -offsety;
    }
    else if (direction == RIGHT2LEFT) {
        offsetx = -offsetx;
        offsety = 0;
    }
    else if (direction == LEFT2RIGHT) {
        //offsetx = offsetx;
        offsety = 0;
    }
    /* Re-position the next widget outside/aside of the display area */
    QPoint pnext = widget(next)->pos();
    QPoint pnow  = widget(now)->pos();
    m_pnow = pnow;

#ifdef USB_QLABEL_MOVICE
    m_pic_slide_next->clear();
    delete m_pic_slide_next;
    m_pic_slide_next = new QLabel(this);
    m_pic_slide_next->setPixmap(QPixmap::grabWidget(widget(next)));
    m_pic_slide_next->adjustSize();
    m_pic_slide_next->move(pnext.x(), pnext.y());
    m_pic_slide_next->show();

    m_pic_slide_now->clear();
    delete m_pic_slide_now;
    m_pic_slide_now = new QLabel(this);
    m_pic_slide_now->setPixmap(QPixmap::grabWidget(widget(now)));
    m_pic_slide_now->adjustSize();
    m_pic_slide_now->move(pnow.x(), pnow.y());
    m_pic_slide_now->show();

    if(next>now)
        m_pic_slide_next->raise();
    else
        m_pic_slide_now->raise();

    widget(now)->hide();
    widget(next)->hide();

    /* Animate both, the now and next widget to the side, using animation framework */
    QPropertyAnimation *animnow = new QPropertyAnimation(m_pic_slide_now, "pos");
    animnow->setDuration(m_speed);
    animnow->setEasingCurve(m_animationtype);
    animnow->setStartValue(QPoint(pnow.x(), pnow.y()));
    animnow->setEndValue(QPoint(offsetx + pnow.x(), offsety + pnow.y()));
    QPropertyAnimation *animnext = new QPropertyAnimation(m_pic_slide_next, "pos");
    animnext->setDuration(m_speed);
    animnext->setEasingCurve(m_animationtype);
    animnext->setStartValue(QPoint(-offsetx + pnext.x(), -offsety + pnext.y()));
    animnext->setEndValue(QPoint(pnext.x(), pnext.y()));
    if(m_animgroup){
        while(m_animgroup->animationCount()){
            m_animgroup->animationAt(0)->deleteLater();
            m_animgroup->removeAnimation(m_animgroup->animationAt(0));
        }
        m_animgroup->clear();
        m_animgroup->deleteLater();
        m_animgroup = NULL;
    }
    m_animgroup = new QParallelAnimationGroup;
    m_animgroup->addAnimation(animnow);
    m_animgroup->addAnimation(animnext);

    QObject::connect(m_animgroup, SIGNAL(finished()), this, SLOT(animationDoneSlot()));
    m_next   = next;
    m_now    = now;
    m_active = true;
    m_animgroup->start();
#else
    widget(next)->move(pnext.x() - offsetx, pnext.y() - offsety);
    /* Make it visible/show */
    widget(next)->show();
    widget(next)->raise();

    /* Animate both, the now and next widget to the side, using animation framework */
    QPropertyAnimation *animnow = new QPropertyAnimation(widget(now), "pos");
    animnow->setDuration(m_speed);
    animnow->setEasingCurve(m_animationtype);
    animnow->setStartValue(QPoint(pnow.x(), pnow.y()));
    animnow->setEndValue(QPoint(offsetx + pnow.x(), offsety + pnow.y()));

    QPropertyAnimation *animnext = new QPropertyAnimation(widget(next), "pos");
    animnext->setDuration(m_speed);
    animnext->setEasingCurve(m_animationtype);
    animnext->setStartValue(QPoint(-offsetx + pnext.x(), offsety + pnext.y()));
    animnext->setEndValue(QPoint(pnext.x(), pnext.y()));

    if(m_animgroup){
        while(m_animgroup->animationCount()){
            m_animgroup->animationAt(0)->deleteLater();
            m_animgroup->removeAnimation(m_animgroup->animationAt(0));
        }
        m_animgroup->clear();
        m_animgroup->deleteLater();
        m_animgroup = NULL;
    }
    m_animgroup = new QParallelAnimationGroup;
    m_animgroup->addAnimation(animnow);
    m_animgroup->addAnimation(animnext);

    QObject::connect(m_animgroup, SIGNAL(finished()), this, SLOT(animationDoneSlot()));
    m_next   = next;
    m_now    = now;
    m_active = true;
    m_animgroup->start();
#endif
    /* Note:
     * the rest is done via a connect from the animation ready;
     * animation->finished() provides a signal when animation is done;
     * so we connect this to some post processing slot,
     * that we implement here below in animationDoneSlot.
     */
}

void SlidingStackedWidget::animationDoneSlot(void) {
#ifdef USB_QLABEL_MOVICE
    m_pic_slide_next->hide();
    m_pic_slide_next->hide();
#endif
    this->setCurrentIndex(m_next);
    widget(m_now)->hide();
    widget(m_now)->move(m_pnow);
    widget(m_next)->show();
    while(m_animgroup->animationCount()){
        m_animgroup->animationAt(0)->deleteLater();
        m_animgroup->removeAnimation(m_animgroup->animationAt(0));
    }
    m_animgroup->clear();
    m_animgroup->deleteLater();
    m_animgroup = NULL;
    m_active = false;
    emit animationFinished();
}

/* REFERENCES:
 * http://doc.trolltech.com/4.6/animation-overview.html#easing-curves
 * http://doc.trolltech.com/4.6/qpropertyanimation.html
 * http://doc.trolltech.com/4.6/qanimationgroup.html
 */
