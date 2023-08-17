#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QIcon>

class Gui: public QWidget
{
    Q_OBJECT
public:
    Gui(QWidget* = nullptr);
private:
    void startScreen();
    void createMenus();
private slots:
    void saveSquad(); // Slot for the Save action
    void loadSquad(); // Slot for the Load action
};

#endif // GUI_H
