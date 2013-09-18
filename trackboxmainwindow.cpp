#include "trackboxmainwindow.h"
#include "ui_trackboxmainwindow.h"

#include <QMouseEvent>
#include <QPixmap>
#include <QIcon>
#include <QDebug>
#include <QPainter>
#include <QBitmap>

trackboxMainWindow::trackboxMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trackboxMainWindow) {
    ui->setupUi(this);
    this->setWindowFlags( Qt::FramelessWindowHint );

    QPixmap closePixmap (":/trackbox/icons/close.png");
    closePixmap = colorPixmap(closePixmap, QColor(0,0,0));

    QIcon closeIcon(closePixmap);
    ui->closeButton->setIcon(closeIcon);

    connect ( ui->closeButton, SIGNAL( clicked() ), this, SLOT( closeButtonClicked() ) );
    }

trackboxMainWindow::~trackboxMainWindow() {
    delete ui;
    }

void trackboxMainWindow::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        m_ResizeState = this->getResizeState(e->pos());
        m_ResizeOffset = e->globalPos();
        m_MoveOffset = e->pos();
        }
    e->accept();
    }

void trackboxMainWindow::mouseMoveEvent(QMouseEvent *e) {
    QPoint eventPoint = e->globalPos();
    QRect geom = this->geometry();
    QPoint diff = eventPoint - m_ResizeOffset;


    switch (m_ResizeState) {
        default:
            break;
        case TopLeftResize:
            geom.setTopLeft(geom.topLeft() + diff);
            break;
        case TopRightResize:
            geom.setTopRight(geom.topRight() + diff);
            break;
        case TopResize:
            geom.setTop(geom.top() + diff.y());
            break;
        case BottomLeftResize:
            geom.setBottomLeft(geom.bottomLeft() + diff);
            break;
        case BottomRightResize:
            geom.setBottomRight(geom.bottomRight() + diff);
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
        case Moving:
            geom.moveTo(this->pos() + (e->pos() - m_MoveOffset));
            break;
        case IdleResize: {
            switch( this->getResizeState(e->pos()) ) {
                case TopLeftResize:
                case BottomRightResize:
                    this->setCursor(Qt::SizeFDiagCursor);
                    break;
                case BottomLeftResize:
                case TopRightResize:
                    this->setCursor(Qt::SizeBDiagCursor);
                    break;
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
    if( geom.size().boundedTo(this->maximumSize()).expandedTo(this->minimumSize()) == geom.size() ) {
        this->setGeometry(geom);
        m_ResizeOffset = eventPoint;
        }
    }

void trackboxMainWindow::mouseReleaseEvent(QMouseEvent *e) {
    m_ResizeState = IdleResize;
    this->unsetCursor();
    e->accept();
    }

void trackboxMainWindow::resizeEvent(QResizeEvent *e) {
    ui->closeButton->move(width() - ui->closeButton->width(), 0);
    e->accept();
    }

void trackboxMainWindow::closeButtonClicked() {
    exit(0);
    }

trackboxMainWindow::ResizeState trackboxMainWindow::getResizeState(const QPoint &pos) const {
    int resizeMargin = 10;
    QRect r = this->rect();

    if( QRect(r.topLeft(),QPoint(resizeMargin,r.top()+resizeMargin)).contains(pos) )
        return TopLeftResize;
    else if( QRect(QPoint(r.right()-resizeMargin,r.top()+resizeMargin), r.topRight()).contains(pos) )
        return TopRightResize;
    else if( QRect(r.bottomLeft(),QPoint(resizeMargin,r.bottom() - resizeMargin)).contains(pos) )
        return BottomLeftResize;
    else if( QRect(r.bottomRight(), QPoint(r.right()-resizeMargin, r.bottom()-resizeMargin)).contains(pos) )
        return BottomRightResize;
    else if( QRect(r.topLeft(),QPoint(r.right(),r.top()+resizeMargin)).contains(pos) )
        return TopResize;
    else if( QRect(QPoint(r.left(),r.bottom()-resizeMargin),r.bottomRight()).contains(pos) )
        return BottomResize;
    else if( QRect(QPoint(r.right()-resizeMargin,r.top()),r.bottomRight()).contains(pos) )
        return RightResize;
    else if( QRect(r.topLeft(),QPoint(r.left()+resizeMargin,r.bottom())).contains(pos) )
        return LeftResize;
    else
        return Moving;
    }

QPixmap trackboxMainWindow::colorPixmap(const QPixmap &pix, const QColor &color) {
    QPixmap newPix(pix.size());
    newPix.fill(Qt::transparent);
    QBitmap mask=pix.createMaskFromColor(Qt::black,
                                         Qt::MaskOutColor);
    QPainter p(&newPix);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::Antialiasing);

    p.setBackgroundMode(Qt::TransparentMode);
    p.setPen(color);
    p.drawPixmap(newPix.rect(),mask,pix.rect());
    p.end();

    return newPix;
    }
