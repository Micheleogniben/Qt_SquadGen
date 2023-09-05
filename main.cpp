#include <QApplication>
#include <QWidget>
#include "dragon.h"
#include "knight.h"
#include "wizard.h"
#include "movesmanager.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Creazione delle mosse
    MovesManager movesManager;

    Gui gui;
    app.setWindowIcon(QIcon(":/Resources/logo.png"));
    return app.exec();
}
