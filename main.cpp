#include <QApplication>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Gui gui;
    app.setWindowIcon(QIcon(":/Resources/logo.png"));
    return app.exec();
}
