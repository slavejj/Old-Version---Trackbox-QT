#ifndef TRACKBOXMAINWINDOW_H
#define TRACKBOXMAINWINDOW_H

#include <QWidget>

namespace Ui {
class trackboxMainWindow;
}

class trackboxMainWindow : public QWidget {
        Q_OBJECT

    public:
        explicit trackboxMainWindow(QWidget *parent = 0);
        ~trackboxMainWindow();

        enum ResizeState { IdleResize, Moving, TopResize, BottomResize, LeftResize, RightResize, TopLeftResize, TopRightResize, BottomLeftResize, BottomRightResize};

    protected:
        virtual void mousePressEvent(QMouseEvent *e);
        virtual void mouseMoveEvent(QMouseEvent *e);
        virtual void mouseReleaseEvent(QMouseEvent *e);

        ResizeState getResizeState(const QPoint & pos) const;

        ResizeState m_ResizeState;
        QPoint  m_ResizeOffset;
        QPoint m_MoveOffset;

    private:
        Ui::trackboxMainWindow *ui;
    };

#endif // TRACKBOXMAINWINDOW_H
