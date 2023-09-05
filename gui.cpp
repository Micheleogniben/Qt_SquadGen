#include "gui.h"


void Gui::createMenus()
{
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu* helpMenu = new QMenu("Help", this);
    QAction *helpAction = new QAction("Help", this);

    // Connect the actions to their respective slots

    connect(helpAction, &QAction::triggered, this, &Gui::help);

    helpMenu->addAction(helpAction);

    menuBar->addMenu(helpMenu);

    layout()->setMenuBar(menuBar); // Add the menu bar to the layout
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

Character* Gui::selectCharacters(Squad* squad) {
    QDialog characterSelectDialog(this);
    characterSelectDialog.setWindowTitle("Selezione dei Personaggi");

    QVBoxLayout characterSelectLayout(&characterSelectDialog);
    QListWidget characterList(&characterSelectDialog);

    for (Character* character : *squad) {
        QListWidgetItem* item = new QListWidgetItem(character->getName());
        characterList.addItem(item);
    }

    characterSelectLayout.addWidget(&characterList);

    QDialogButtonBox characterSelectButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &characterSelectDialog);
    characterSelectLayout.addWidget(&characterSelectButtonBox);

    connect(&characterSelectButtonBox, &QDialogButtonBox::accepted, &characterSelectDialog, &QDialog::accept);
    connect(&characterSelectButtonBox, &QDialogButtonBox::rejected, &characterSelectDialog, &QDialog::reject);

    if (characterSelectDialog.exec() == QDialog::Accepted) {
        QListWidgetItem* selectedItem = characterList.currentItem();
        if (!selectedItem) {
            QMessageBox::critical(this, "Errore", "Devi selezionare un personaggio.");
            return nullptr;
        }

        QString selectedCharacterName = selectedItem->text();
        Character* selectedCharacter = squad->findByName(selectedCharacterName);
        return selectedCharacter;
    }

    return nullptr;
}

// Funzione per la selezione delle mosse
bool Gui::selectMoves(Character* character) {
    QDialog moveDialog(this);
    moveDialog.setWindowTitle("Selezione Mosse per " + character->getName());

    QVBoxLayout moveLayout(&moveDialog);
    QListWidget moveList(&moveDialog);
    moveList.setSpacing(3);

    for (Move* move : movesManager.getCompatibleMoves(character)) {
        QPushButton* infoButton = new QPushButton("Info");
        connect(infoButton, &QPushButton::clicked, [=]() {
            showMoveInfoDialog(move);
        });

        // Crea un widget personalizzato con un layout orizzontale
        QWidget* itemWidget = new QWidget();
        QHBoxLayout* itemLayout = new QHBoxLayout(itemWidget);

        QLabel* moveLabel = new QLabel(move->getName());  // Crea un QLabel per il nome della mossa

        itemLayout->setContentsMargins(0, 0, 0, 0);
        moveLabel->setStyleSheet("font-size: 15px; color: black;");  // Imposta il colore del testo e la dimensione del carattere
        infoButton->setStyleSheet("font-size: 7px; color: black;");   // Imposta il colore del testo e la dimensione del carattere

        itemLayout->addWidget(moveLabel, 2);               // Aggiungi il nome della mossa a sinistra
        itemLayout->addWidget(infoButton);              // Aggiungi il pulsante "Info" a destra

        // Imposta il widget personalizzato come elemento del QListWidget
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(200, 50));
        moveList.addItem(item);
        moveList.setItemWidget(item, itemWidget);
    }

    moveList.setSelectionMode(QAbstractItemView::MultiSelection);
    moveLayout.addWidget(&moveList);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &moveDialog);
    moveLayout.addWidget(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &moveDialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &moveDialog, &QDialog::reject);

    if (moveDialog.exec() == QDialog::Accepted) {
        QList<QListWidgetItem*> selectedItems = moveList.selectedItems();

        if (selectedItems.size() != 2) {
            QMessageBox::critical(this, "Errore", "Devi selezionare esattamente 2 mosse per personaggio");
            return false;
        }

        for (QListWidgetItem* selectedItem : selectedItems) {
            QString moveName = selectedItem->text();
            character->addMove(movesManager.moveByName(moveName)); // Aggiungi la mossa al personaggio
        }
        QMessageBox::information(this, "Conferma", "Mosse selezionate con successo per " + character->getName() + ".");
        return true;
    }
    else return false;
}

void Gui::editSquad(Squad* squad) {
   Character * character = selectCharacters(squad);
   if(character){
       QMessageBox confirmBox(QMessageBox::Question, "Conferma Azione", "Vuoi eliminare o modificare le mosse di " + character->getName() + "?", QMessageBox::Yes | QMessageBox::No, this);
       confirmBox.setButtonText(QMessageBox::Yes, "Modifica Mosse");
       confirmBox.setButtonText(QMessageBox::No, "Elimina Personaggio");

       int choice = confirmBox.exec();

       if (choice == QMessageBox::Yes) {
           bool correctInsertion =false;
           while(!correctInsertion) correctInsertion = selectMoves(character);
       } else if (choice == QMessageBox::No) {
           // Elimina il personaggio dalla squadra
       }
   }
   return;
}

void Gui::squadManagement(Squad* squad) {
    // Create the button widget
    QWidget *buttonWidget = new QWidget(this);

    // Create a vertical layout for the buttons
    QVBoxLayout *mainLayout = new QVBoxLayout(buttonWidget);

    // Create a horizontal layout for the top row buttons
    QHBoxLayout *topButtonLayout = new QHBoxLayout();

    // Create the Save Squad button and set its size and style
    QPushButton *saveSquadButton = new QPushButton("Save Squad");
    saveSquadButton->setFixedSize(200, 70);
    saveSquadButton->setStyleSheet("font-size: 12px;");

    // Create the Edit Squad button and set its size and style
    QPushButton *editSquadButton = new QPushButton("Edit Squad");
    editSquadButton->setFixedSize(200, 70);
    editSquadButton->setStyleSheet("font-size: 12px;");

    // Create the Load Squad button and set its size and style
    QPushButton *loadSquadButton = new QPushButton("Load Squad");
    loadSquadButton->setFixedSize(200, 70);
    loadSquadButton->setStyleSheet("font-size: 12px;");

    // Add the top row buttons to the horizontal layout
    topButtonLayout->addWidget(saveSquadButton);
    topButtonLayout->addWidget(editSquadButton);
    topButtonLayout->addWidget(loadSquadButton);

    // Create the Start Kombat button and set its size and style
    QPushButton *startKombatButton = new QPushButton("Start Kombat");
    startKombatButton->setFixedSize(200, 70);
    startKombatButton->setStyleSheet("font-size: 12px;background-color: red; color: black;");

    // Create a horizontal layout for the center alignment of the Start Kombat button
    QHBoxLayout *centerButtonLayout = new QHBoxLayout();
    centerButtonLayout->addStretch(); // Add stretch to center-align the button
    centerButtonLayout->addWidget(startKombatButton);
    centerButtonLayout->addStretch(); // Add stretch to center-align the button

    // Add the top row layout and the center-aligned Start Kombat button layout to the main layout
    mainLayout->addLayout(topButtonLayout);
    mainLayout->addLayout(centerButtonLayout);

    // Set the new widget as the central widget
    QWidget *previousWidget = centralWidget();
    setCentralWidget(buttonWidget);
    delete previousWidget;

    // Connect button clicks to lambda functions for handling
    connect(saveSquadButton, &QPushButton::clicked, [this, squad]() {

    });

    connect(editSquadButton, &QPushButton::clicked, [this, squad]() {
        editSquad(squad);
        squadManagement(squad);
    });

    connect(loadSquadButton, &QPushButton::clicked, [this, squad]() {

    });

    connect(startKombatButton, &QPushButton::clicked, [this, squad]() {

    });
}

void Gui::startScreen()
{
    setWindowTitle("QtKombat");
    setFixedSize(750, 400); // Set initial window size

    // Create a vertical layout for the window
    QVBoxLayout *mainLayout = new QVBoxLayout(this); // Usa direttamente "this" come genitore

    // Add a label with the game name as the title
    QLabel *titleLabel = new QLabel("WELCOME TO QTKombat");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    // Create a horizontal layout for the buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // Create and configure the "Create your Squad" button
    QPushButton *createButton = new QPushButton("Create your Squad");
    createButton->setFixedSize(200, 50);
    createButton->setStyleSheet("font-size: 18px;");

    // Create and configure the "Load Squad" button
    QPushButton *loadButton = new QPushButton("Load a Squad");
    loadButton->setFixedSize(200, 50);
    loadButton->setStyleSheet("font-size: 18px;");

    // Connect the "Create your Squad" button to the character selection action
    connect(createButton, &QPushButton::clicked, [&]() {
        Squad *squadCreated = characterSelection();
        if (squadCreated) {
            moveSelection(squadCreated);
            squadManagement(squadCreated);
        }
    });

    connect(loadButton, &QPushButton::clicked, [&]() {
        //Squad* squad =Parser()...
        squadManagement(nullptr);
    });

    // Add the buttons to the horizontal button layout
    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(loadButton);

    // Add the title label to the vertical main layout
    mainLayout->addWidget(titleLabel);

    // Add spacing or other widgets if needed between title and buttons

    // Add the horizontal button layout to the vertical main layout
    mainLayout->addLayout(buttonLayout);

    // Set the main layout of the window
    centralWidget()->setLayout(mainLayout); // Usa centralWidget() per ottenere il widget centrale

    // Show the window
    show();
}


Gui::Gui(QWidget* parent): QMainWindow(parent), movesManager()
{
    createMenus();
    setCentralWidget(new QWidget());
    startScreen();
}

void Gui::showMoveInfoDialog(Move* move) {
    QDialog moveInfoDialog(this);
    moveInfoDialog.setWindowTitle("Informazioni sulla Mossa");

    QVBoxLayout moveInfoLayout(&moveInfoDialog);

    QLabel nameLabel("Nome: " + move->getName());
    QLabel descLabel("Descrizione: " + move->getDescription());
    QLabel phyDmgLabel("Danno Fisico: " + QString::number(move->getPhyDmg()));
    QLabel magDmgLabel("Danno Magico: " + QString::number(move->getMagDmg()));
    QString moveType=toText(move->getType());
    QLabel categoryLabel;
    if(moveType!="")
        categoryLabel.setText("Tipo: " + moveType );
    else categoryLabel.setText("Character Specific Move");


    moveInfoLayout.addWidget(&nameLabel);
    moveInfoLayout.addWidget(&descLabel);
    moveInfoLayout.addWidget(&phyDmgLabel);
    moveInfoLayout.addWidget(&magDmgLabel);
    moveInfoLayout.addWidget(&categoryLabel);

    QDialogButtonBox closeButton(QDialogButtonBox::Close, &moveInfoDialog);
    moveInfoLayout.addWidget(&closeButton);

    connect(&closeButton, &QDialogButtonBox::rejected, &moveInfoDialog, &QDialog::reject);

    moveInfoDialog.exec();
}


void Gui::moveSelection(Squad* squad) {

    for (Character* character : *squad) {
        bool correctInsertion =false;
        while(!correctInsertion) correctInsertion = selectMoves(character);
    }

    QMessageBox::information(this, "Conferma", "Mosse selezionate con successo per tutti i personaggi.");
    return;
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

Squad* Gui::characterSelection(){
    QDialog *characterSelectionDialog = new QDialog(this);
    characterSelectionDialog->setWindowTitle("Select Characters");

    QVBoxLayout *mainLayout = new QVBoxLayout(characterSelectionDialog);

    QLabel *remainingCapacityLabel = new QLabel("Remaining Capacity: " + QString::number(Squad::capacity));
    mainLayout->addWidget(remainingCapacityLabel);

    QHash<QString,QPair<int,int>> characterMap; // Map to store character weights per unit and number of occurencies DA MODIFICARE
    characterMap.insert("Goblin", QPair<int,int>(2,0));
    characterMap.insert("Knight", QPair<int,int>(15,0));
    characterMap.insert("Wizard", QPair<int,int>(12,0));
    characterMap.insert("Cleric", QPair<int,int>(9,0));
    characterMap.insert("Dragon", QPair<int,int>(30,0));

    //Boxes

        //GoblinBox
        QSpinBox *goblinSpinBox = new QSpinBox;
        goblinSpinBox->setRange(0, Squad::capacity); // Set the maximum number of units
        QLabel *goblinLabel = new QLabel("Goblin: ");
        mainLayout->addWidget(goblinLabel);
        mainLayout->addWidget(goblinSpinBox);

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
        Squad* squad = new Squad();

        for (auto it = characterMap.cbegin(); it != characterMap.cend(); ++it) {
            QString key = it.key();
            QPair<int, int> value = it.value();

            if (key == "Goblin" && value.second > 0) {
                QString name=QInputDialog::getText(this, "Enter Name", "Enter a name for the Ord of Goblins:");
                while(name.isEmpty()){
                    QMessageBox::warning(this, "Missing Name", "You must enter a name for the Ord of Goblins.");
                    name= QInputDialog::getText(this, "Enter Name", "Enter a name for the Ord of Goblins:");
                }

                while(squad->isNameTaken(name)){
                    QMessageBox::warning(this, "Duplicate Name", "This name is already used. Please choose a different name.");
                    name = QInputDialog::getText(this, "Enter Name", "Enter a name for the " + key + ":");
                }

                squad->addCharacter(new Goblin(name));
            }
            else{
                for (int i = value.second; i != 0; i--) {
                    QString name = QInputDialog::getText(this, "Enter Name", "Enter a name for the " + key + ":");
                    while(name.isEmpty()) {
                        QMessageBox::warning(this, "Missing Name", "You must enter a name for the " + key + ".");
                        name = QInputDialog::getText(this, "Enter Name", "Enter a name for the " + key + ":");
                    }

                    while(squad->isNameTaken(name)){
                        QMessageBox::warning(this, "Duplicate Name", "This name is already used. Please choose a different name.");
                        name = QInputDialog::getText(this, "Enter Name", "Enter a name for the " + key + ":");
                    }

                    if (key == "Knight") squad->addCharacter(new Knight(name));
                    if (key == "Wizard") squad->addCharacter(new Wizard(name));
                    if (key == "Cleric") squad->addCharacter(new Cleric(name));
                    if (key == "Dragon") squad->addCharacter(new Dragon(name));
                }
            }
        }

        //Memory Cleanup
        delete characterSelectionDialog;
        return squad;
    }
    delete characterSelectionDialog;
    return nullptr;
}
