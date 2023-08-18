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
#include <QListWidget>
#include <QCheckBox>
#include <QDialogButtonBox>

#include <squad.h>
#include <cleric.h>
#include <knight.h>
#include <dragon.h>
#include <goblin.h>
#include <wizard.h>
#include <controller.h>

class Gui: public QWidget
{
    Q_OBJECT
private:
    Controller control;
    void startScreen();
    void createMenus();
    void characterSelection();
    void moveSelection(Squad&);
public:
    Gui(QWidget* = nullptr);
    void updateRemainingCapacityLabel(QSet<QString>&, QLabel*, QHash<QString,int>&);
    void updateSelectedCharacters(QCheckBox *, const QString &,QSet<QString>&, QLabel*,QHash<QString,int>&);
private slots:
    void saveSquad(); // Slot for the Save action
    void loadSquad(); // Slot for the Load action
};

#endif // GUI_H
