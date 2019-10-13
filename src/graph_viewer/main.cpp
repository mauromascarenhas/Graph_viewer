#include "mainwindow.h"

#include <QSurface>
#include <QApplication>

int main(int argc, char *argv[])
{
    QSurfaceFormat format;
    format.setVersion(4, 1);

#if __unix__
    format.setProfile(QSurfaceFormat::CoreProfile);
#else
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
#endif
    format.setDepthBufferSize(32);
    format.setSamples(4);

    QSurfaceFormat::setDefaultFormat(format);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
