#include "openglwindow.h"
#include <QApplication>

#include "zone.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Zone* pZone = new Zone();

    w.AddDrawable(pZone);
    return a.exec();
}
