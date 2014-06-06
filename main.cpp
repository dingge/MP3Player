#include <QApplication>
#include "customwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CustomWindow window;
    window.show();

    return app.exec();
}
