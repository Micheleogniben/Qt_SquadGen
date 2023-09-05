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
#include <QSpinBox>
#include <QPair>

#include "squad.h"
#include "cleric.h"
#include "knight.h"
#include "dragon.h"
#include "goblin.h"
#include "wizard.h"
#include "controller.h"
#include "movesmanager.h"

class Gui: public QWidget
{
    Q_OBJECT
private:
    Controller control;
    void startScreen();
    void createMenus();
    Squad* characterSelection();
    Squad* moveSelection(Squad*);
    void updateRemainingCapacityLabel(const QString&,int, QLabel*, QHash<QString,QPair<int,int>>&);
    bool enoughCapacity(const QString &,const int , const QHash<QString,QPair<int,int>>&)const;
    void showMoveInfoDialog(Move*);
public:
    Gui(QWidget* = nullptr);
private slots:
    void saveSquad(); // Slot for the Save action
    void loadSquad(); // Slot for the Load action
    void help();      // Slot for the Help action
};

#endif // GUI_H
