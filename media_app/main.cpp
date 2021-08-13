#include <QApplication>
#include "windowframe.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    WindowFrame window;
    window.show();
    window.setFixedSize(800,480);
    return app.exec();
}

