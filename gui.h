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
#include <QInputDialog>
#include <QMainWindow>

#include <squad.h>
#include <cleric.h>
#include <knight.h>
#include <dragon.h>
#include <goblin.h>
#include <wizard.h>
#include <movesmanager.h>

class Gui: public QMainWindow
{
    Q_OBJECT
private:
    void startScreen();
    void createMenus();
    Squad* characterSelection();
    Squad* moveSelection(Squad*);
    void updateRemainingCapacityLabel(const QString&,int, QLabel*, QHash<QString,QPair<int,int>>&);
    bool enoughCapacity(const QString &,const int , const QHash<QString,QPair<int,int>>&)const;
    void showMoveInfoDialog(Move*);
    void squadManagement(Squad*);
    Squad* editSquad(Squad*);
    void editCharacterMoves(Character*);
    void startKombat(Squad*);
    Character* selectCharacters(Squad*);
    void selectMoves(Character*);
public:
    Gui(QWidget* parent = nullptr);
private slots:
    void help();
};

#endif // GUI_H
