#include <QApplication>
#include <QWidget>
#include "startScreen.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    startScreen(&window);
    return app.exec();
}
