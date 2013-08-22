#include "trackboxmainwindow.h"
#include "ui_trackboxmainwindow.h"

#include <QMouseEvent>

trackboxMainWindow::trackboxMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trackboxMainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags( Qt::FramelessWindowHint );
}

trackboxMainWindow::~trackboxMainWindow()
{
    delete ui;
}

void trackboxMainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_ResizeState = this->getResizeState(e->pos());
        m_ResizeOffset = e->globalPos();
    }
    e->accept();
}

void trackboxMainWindow::mouseMoveEvent(QMouseEvent *e)
{
    QPoint eventPoint = e->globalPos();
    QRect geom = this->geometry();
    QPoint diff = eventPoint - m_ResizeOffset;

    switch (m_ResizeState)
    {
    default:
        break;
    case TopResize:
        geom.setTop(geom.top() + diff.y());
        break;
    case BottomResize:
        geom.setBottom(geom.bottom() + diff.y());
        break;
    case LeftResize:
        geom.setLeft(geom.left() + diff.x());
        break;
    case RightResize:
        geom.setRight(geom.right() + diff.x());
        break;
    case IdleResize:
        {
            switch( this->getResizeState(e->pos()) )
            {
            case TopResize:
            case BottomResize:
                this->setCursor(Qt::SizeVerCursor);
                break;
            case LeftResize:
            case RightResize:
                this->setCursor(Qt::SizeHorCursor);
                break;
            case IdleResize:
            default:
                this->unsetCursor();
                break;
            }
        }
        break;
    }

    //do some checks
    if( geom.size().boundedTo(this->maximumSize()).expandedTo(this->minimumSize()) == geom.size() )
    {
        this->setGeometry(geom);
        m_ResizeOffset = eventPoint;
    }
}

void trackboxMainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    m_ResizeState = IdleResize;
    this->unsetCursor();
    e->accept();
}

trackboxMainWindow::ResizeState trackboxMainWindow::getResizeState(const QPoint &pos) const
{
    int resizeMargin = 10;
    QRect r = this->rect();

    if( QRect(r.topLeft(),QPoint(r.right(),r.top()+resizeMargin)).contains(pos) )
        return TopResize;
    else if( QRect(QPoint(r.left(),r.bottom()-resizeMargin),r.bottomRight()).contains(pos) )
        return BottomResize;
    else if( QRect(QPoint(r.right()-resizeMargin,r.top()),r.bottomRight()).contains(pos) )
        return RightResize;
    else if( QRect(r.topLeft(),QPoint(r.left()+resizeMargin,r.bottom())).contains(pos) )
        return LeftResize;
    else
        return IdleResize;
}
