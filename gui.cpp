#include "gui.h"

void Gui::createMenus()
{
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *squadMenu = new QMenu("Squad", this);
    QMenu* helpMenu = new QMenu("Help", this);

    QAction *saveAction = new QAction("Save", this);
    QAction *loadAction = new QAction("Load", this);
    QAction *helpAction = new QAction("Help", this);

    // Connect the actions to their respective slots
    connect(saveAction, &QAction::triggered, this, &Gui::saveSquad);
    connect(loadAction, &QAction::triggered, this, &Gui::loadSquad);
    connect(helpAction, &QAction::triggered, this, &Gui::help);

    squadMenu->addAction(saveAction);
    squadMenu->addAction(loadAction);
    helpMenu->addAction(helpAction);

    menuBar->addMenu(squadMenu);
    menuBar->addMenu(helpMenu);

    layout()->setMenuBar(menuBar); // Add the menu bar to the layout
}

void Gui::saveSquad()
{
    // Implement your save logic here
    // For example: open a file dialog to choose a file to save the squad
    // Save the squad data to the selected file
}

void Gui::loadSquad()
{
    // Implement your load logic here
    // For example: open a file dialog to choose a file to load the squad from
    // Load the squad data from the selected file
}

void Gui::help()
{
    QFile file(":/Resources/documentation.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString documentation = in.readAll();

        QMessageBox msgBox;
        msgBox.setWindowTitle("Documentation");
        msgBox.setText(documentation);
        msgBox.exec();

        file.close();
    } else {
        QMessageBox::warning(nullptr, "Error", "Documentation file not found!");
    }
}

void Gui::startScreen()
{

    setWindowTitle("QtKombat");
    setFixedSize(750, 400); // Set initial window size

    // Create a vertical layout for the window
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Add a label with the game name as the title
    QLabel *titleLabel = new QLabel("WELCOME TO QTKombat");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    // Create a horizontal layout for the buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // Create and configure the "Create your Squad" button
    QPushButton *createButton = new QPushButton("Create your Squad");
    createButton->setFixedSize(200, 50);
    createButton->setStyleSheet("font-size: 18px;");
    buttonLayout->addWidget(createButton);

    // Create and configure the "Load Squad" button
    QPushButton *loadButton = new QPushButton("Load a Squad");
    loadButton->setFixedSize(200, 50);
    loadButton->setStyleSheet("font-size: 18px;");
    buttonLayout->addWidget(loadButton);

    // Connect the "Inizia" button to the character selection action
    QObject::connect(createButton, &QPushButton::clicked, [&](){
        characterSelection();
    });

    // Add the button layout to the main layout
    mainLayout->addLayout(buttonLayout);

    // Set the main layout of the window
    setLayout(mainLayout);

    // Show the window
    show();
}

Gui::Gui(QWidget* parent): QWidget(parent), control()
{
    startScreen();
    createMenus();
}

void Gui::moveSelection(Squad &){

}

bool Gui::enoughCapacity(const QString &characterName, const int unitCount,  const QHash<QString,QPair<int,int>>& characterMap) const{
    int totalSelectedWeight = 0;
    for (auto i = characterMap.cbegin(); i != characterMap.cend(); ++i) {
        QString key = i.key();
        QPair<int,int> value = i.value();
        if(key!=characterName)
            totalSelectedWeight += value.first * value.second;
    }
    int remainingWeight = Squad::capacity - (totalSelectedWeight + characterMap[characterName].first *unitCount) ;
    if(remainingWeight  >= 0 ) return true;
    else return false;
}

void Gui::updateRemainingCapacityLabel(const QString & characterName, int unitCount, QLabel* remainingCapacityLabel, QHash<QString,QPair<int,int>>& characterMap)
{
    characterMap[characterName].second = unitCount;
    int totalSelectedWeight = 0;
    for ( auto map : characterMap) {
        totalSelectedWeight += map.first * map.second;
    }

    int remainingCapacity = Squad::capacity - totalSelectedWeight;
    remainingCapacityLabel->setText("Remaining Capacity: " + QString::number(remainingCapacity));
}

void Gui::characterSelection(){
    QDialog *characterSelectionDialog = new QDialog(this);
    characterSelectionDialog->setWindowTitle("Select Characters");

    QVBoxLayout *mainLayout = new QVBoxLayout(characterSelectionDialog);

    QLabel *remainingCapacityLabel = new QLabel("Remaining Capacity: " + QString::number(Squad::capacity));
    mainLayout->addWidget(remainingCapacityLabel);

    QHash<QString,QPair<int,int>> characterMap; // Map to store character weights per unit and number of occurencies
    characterMap.insert("Knight", QPair<int,int>(15,0));
    characterMap.insert("Wizard", QPair<int,int>(12,0));
    characterMap.insert("Goblin", QPair<int,int>(2,0));
    characterMap.insert("Dragon", QPair<int,int>(30,0));
    characterMap.insert("Cleric", QPair<int,int>(9,0));

    //Boxes
        // KnightBox
        QSpinBox *knightSpinBox = new QSpinBox;
        knightSpinBox->setRange(0, Squad::capacity); // Set the maximum number of units
        QLabel *knightLabel = new QLabel("Knight: " );
        mainLayout->addWidget(knightLabel);
        mainLayout->addWidget(knightSpinBox);

        //WizardBox
        QSpinBox *wizardSpinBox = new QSpinBox;
        wizardSpinBox->setRange(0, Squad::capacity); // Set the maximum number of units
        QLabel *wizardLabel = new QLabel("Wizard: ");
        mainLayout->addWidget(wizardLabel);
        mainLayout->addWidget(wizardSpinBox);

        //ClericBox
        QSpinBox *clericSpinBox = new QSpinBox;
        clericSpinBox->setRange(0, Squad::capacity); // Set the maximum number of units
        QLabel *clericLabel = new QLabel("Cleric: ");
        mainLayout->addWidget(clericLabel);
        mainLayout->addWidget(clericSpinBox);

        //GoblinBox
        QSpinBox *goblinSpinBox = new QSpinBox;
        goblinSpinBox->setRange(0, Squad::capacity); // Set the maximum number of units
        QLabel *goblinLabel = new QLabel("Goblin: ");
        mainLayout->addWidget(goblinLabel);
        mainLayout->addWidget(goblinSpinBox);

        //DragonBox
        QSpinBox *dragonSpinBox = new QSpinBox;
        dragonSpinBox->setRange(0, Squad::capacity); // Set the maximum number of units
        QLabel *dragonLabel = new QLabel("Dragon ");
        mainLayout->addWidget(dragonLabel);
        mainLayout->addWidget(dragonSpinBox);

    //Connections
        // Connect Knight to update
        QObject::connect(knightSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=, &characterMap]() {
            QString character="Knight";
            bool eC = enoughCapacity(character,knightSpinBox->value(), characterMap);
            if(eC)
                updateRemainingCapacityLabel(character, knightSpinBox->value(), remainingCapacityLabel, characterMap);
            else{
                QMessageBox::warning(this, "Exceeded Capacity", "Your input has exceeded the remaining capacity.");
                knightSpinBox->setValue(characterMap[character].second);
            }
        });

        // Connect Wizard to update
        QObject::connect(wizardSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=, &characterMap]() {
            QString character="Wizard";
            bool eC = enoughCapacity(character,wizardSpinBox->value(), characterMap);
            if(eC)
                updateRemainingCapacityLabel(character, wizardSpinBox->value(), remainingCapacityLabel, characterMap);
            else{
                QMessageBox::warning(this, "Exceeded Capacity", "Your input has exceeded the remaining capacity.");
                wizardSpinBox->setValue(characterMap[character].second);
            }
        });

        // Connect Cleric to update
        QObject::connect(clericSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=, &characterMap]() {
            QString character="Cleric";
            bool eC = enoughCapacity(character,clericSpinBox->value(), characterMap);
            if(eC)
                updateRemainingCapacityLabel(character, clericSpinBox->value(), remainingCapacityLabel, characterMap);
            else{
                QMessageBox::warning(this, "Exceeded Capacity", "Your input has exceeded the remaining capacity.");
                clericSpinBox->setValue(characterMap[character].second);
            }
        });

        // Connect Goblin to update
        QObject::connect(goblinSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=, &characterMap]() {
            QString character="Goblin";
            bool eC = enoughCapacity(character,goblinSpinBox->value(), characterMap);
            if(eC)
                updateRemainingCapacityLabel(character, goblinSpinBox->value(), remainingCapacityLabel, characterMap);
            else{
                QMessageBox::warning(this, "Exceeded Capacity", "Your input has exceeded the remaining capacity.");
                goblinSpinBox->setValue(characterMap[character].second);
            }
        });

        // Connect Dragon to update
        QObject::connect(dragonSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=, &characterMap]() {
            QString character="Dragon";
            bool eC = enoughCapacity(character,dragonSpinBox->value(), characterMap);
            if(eC)
                updateRemainingCapacityLabel(character, dragonSpinBox->value(), remainingCapacityLabel, characterMap);
            else{
                QMessageBox::warning(this, "Exceeded Capacity", "Your input has exceeded the remaining capacity.");
                dragonSpinBox->setValue(characterMap[character].second);
            }
        });

        // more to come...

    // Create a button box for OK and Cancel buttons
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    mainLayout->addWidget(buttonBox);

    // Connect the OK button
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, characterSelectionDialog, &QDialog::accept);

    // Connect the Cancel button
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, characterSelectionDialog, &QDialog::reject);

    // Show the character selection dialog
    if (characterSelectionDialog->exec() == QDialog::Accepted) {
        // Handle the selected characters and proceed with the game
        Squad squad;

        for (auto it = characterMap.cbegin(); it != characterMap.cend(); ++it) {
            QString key = it.key();
            QPair<int,int> value = it.value();
            for(int i=value.second; i!=0; i--){
                if (key=="Knight")  squad.addCharacter(new Knight());
                else if(key=="Wizard")  squad.addCharacter(new Wizard());
                else if(key=="Cleric")  squad.addCharacter(new Cleric());
                else if(key=="Goblin")  squad.addCharacter(new Goblin());
                else if(key=="Dragon")  squad.addCharacter(new Dragon());
            }
        }
        //Memory Cleanup
        delete characterSelectionDialog;
        //squadManagement(squad);

    }
}
