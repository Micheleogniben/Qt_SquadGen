#include <QApplication>
#include <QWidget>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Gui gui;
    return app.exec();
}
