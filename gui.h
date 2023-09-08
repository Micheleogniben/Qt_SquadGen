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
#include <QButtonGroup>
#include <QRadioButton>
#include <QStringListModel>
#include <QScrollArea>
#include <set>

#include <squad.h>
#include <cleric.h>
#include <knight.h>
#include <dragon.h>
#include <goblin.h>
#include <wizard.h>
#include <movesmanager.h>
#include <battlemanager.h>
#include <type.h>
#include <statistics.h>

class Gui: public QMainWindow
{
    Q_OBJECT
private:
    MovesManager* movesManager;
    BattleManager* battleManager;
    Squad* squad;

    void createMenus();

    void updateRemainingCapacityLabel(const QString&,int, QLabel*, QHash<QString,QPair<int,int>>&);
    bool enoughCapacity(const QString &,const int , const QHash<QString,QPair<int,int>>&)const;
    void updateKombatScreen(QVBoxLayout*, QVBoxLayout*);

//Dialog Windows

    void characterSelection();
    void moveSelection();

    void squadManagement();
    int updateMoves(Character*);
    void chooseAction(Character*);

    void showMoveInfoDialog(Move*);
    void showCharacterInfoDialog(Character*);

    void attack();
    Character* chooseCharacter(Squad*,QString);
    Move* chooseMove(Character*);
    int chooseKombatAction();

//Flow windows

    void startScreen();
    void managementScreen();
    void kombatScreen();

public:
    Gui(QWidget* parent = nullptr);
private slots:
    void help();
};

#endif // GUI_H
