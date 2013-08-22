#include "trackboxmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    trackboxMainWindow w;
    w.show();
    
    return a.exec();
}
