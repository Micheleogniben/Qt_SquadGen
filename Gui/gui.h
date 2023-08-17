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

class Gui: public QWidget
{
    Q_OBJECT
public:
    Gui(QWidget* = nullptr);
    void setMenus();
    void startScreen();
};

#endif // GUI_H
