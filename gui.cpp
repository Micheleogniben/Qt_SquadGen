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

    int remainingCapacity = squad->getCurrentCapacity() - totalSelectedWeight;
    remainingCapacityLabel->setText("Remaining Capacity: " + QString::number(remainingCapacity));
}

//=========================

void Gui::updateKombatScreen(QVBoxLayout* yourTeamLayout, QVBoxLayout* opponentLayout) {

    QLayoutItem* item;
    while ((item = yourTeamLayout->takeAt(0)) != nullptr) {
        QWidget* widget = item->widget();
        if (widget) {
            yourTeamLayout->removeWidget(widget);
            delete widget;
        }
        delete item;
    }

    while ((item = opponentLayout->takeAt(0)) != nullptr) {
        QWidget* widget = item->widget();
        if (widget) {
            opponentLayout->removeWidget(widget);
            delete widget;
        }
        delete item;
    }

    QLabel *yourTeamLabel = new QLabel("Your Squad:");
    yourTeamLabel->setStyleSheet("font-size: 20px;color:red");
    yourTeamLayout->addWidget(yourTeamLabel);

    QLabel *opponentLabel = new QLabel("YourVictim:");
    opponentLabel->setStyleSheet("font-size: 20px;color:red");
    opponentLayout->addWidget(opponentLabel);

    for (Character* character : *battleManager->getTeam(1)) {
        QLabel* label = new QLabel(character->getName() + "   " + QString::number(character->getLifePoints()) + " LifeP");
        yourTeamLayout->addWidget(label);
    }

    for (Character* character : *battleManager->getTeam(2)) {
        QLabel* label = new QLabel(character->getName() + "   " + QString::number(character->getLifePoints()) + " LifeP");
        opponentLayout->addWidget(label);
    }
}

Character* Gui::chooseCharacter(Squad* squadSelected, QString title){
    QDialog attackerSelectDialog(this);
    attackerSelectDialog.setWindowTitle(title);

    QVBoxLayout attackerSelectLayout(&attackerSelectDialog);

    QLabel promptLabel("Scegli un personaggio");
    attackerSelectLayout.addWidget(&promptLabel);

    QListWidget attackerListWidget(&attackerSelectDialog);
    attackerListWidget.setSelectionMode(QAbstractItemView::SingleSelection);

    for (Character* character : *squadSelected) {
        QListWidgetItem* item = new QListWidgetItem(character->getName());
        attackerListWidget.addItem(item);
    }

    attackerSelectLayout.addWidget(&attackerListWidget);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &attackerSelectDialog);
    attackerSelectLayout.addWidget(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &attackerSelectDialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &attackerSelectDialog, &QDialog::reject);

    if (attackerSelectDialog.exec() == QDialog::Accepted) {
        QListWidgetItem* selectedItem = attackerListWidget.currentItem();
        if (selectedItem) {
            QString selectedCharacterName = selectedItem->text();
            Character* selectedCharacter = squadSelected->findByName(selectedCharacterName);
            return selectedCharacter;
        }
    }

    return nullptr; // Nessun personaggio selezionato o dialogo annullato
}

Move* Gui::chooseMove(Character* character) {
    QDialog moveSelectDialog(this);
    moveSelectDialog.setWindowTitle("Scegli una Mossa");

    QVBoxLayout moveSelectLayout(&moveSelectDialog);

    QLabel promptLabel("Scegli una mossa per " + character->getName() + ":");
    moveSelectLayout.addWidget(&promptLabel);

    QListWidget moveListWidget(&moveSelectDialog);
    moveListWidget.setSelectionMode(QAbstractItemView::SingleSelection);

    const std::tuple<const Move*, const Move*> availableMoves = character->getMoves();
    const Move* firstMove = std::get<0>(availableMoves);
    const Move* secondMove = std::get<1>(availableMoves);

    QListWidgetItem* firstMoveItem = new QListWidgetItem(firstMove->getName());
    QListWidgetItem* secondMoveItem = new QListWidgetItem(secondMove->getName());

    moveListWidget.addItem(firstMoveItem);
    moveListWidget.addItem(secondMoveItem);

    moveSelectLayout.addWidget(&moveListWidget);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &moveSelectDialog);
    moveSelectLayout.addWidget(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &moveSelectDialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &moveSelectDialog, &QDialog::reject);

    if (moveSelectDialog.exec() == QDialog::Accepted) {
        QListWidgetItem* selectedItem = moveListWidget.currentItem();
        if (selectedItem) {
            QString selectedMoveName = selectedItem->text();
            if (selectedMoveName == firstMove->getName()) {
                return const_cast<Move*>(firstMove); // Rimuovi const e restituisci la mossa
            } else if (selectedMoveName == secondMove->getName()) {
                return const_cast<Move*>(secondMove); // Rimuovi const e restituisci la mossa
            }
        }
    }

    return nullptr; // Nessuna mossa selezionata o dialogo annullato
}


int Gui::chooseKombatAction() {
    QDialog actionSelectDialog(this);
    actionSelectDialog.setWindowTitle("Scegli un'azione di combattimento");

    QVBoxLayout actionSelectLayout(&actionSelectDialog);

    QLabel promptLabel("Scegli un'azione di combattimento:");
    actionSelectLayout.addWidget(&promptLabel);

    QRadioButton* abilityRadio = new QRadioButton("Usa l'abilità");
    QRadioButton* moveRadio = new QRadioButton("Scegli una mossa");

    QButtonGroup buttonGroup(&actionSelectDialog);
    buttonGroup.addButton(abilityRadio);
    buttonGroup.addButton(moveRadio);

    actionSelectLayout.addWidget(abilityRadio);
    actionSelectLayout.addWidget(moveRadio);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &actionSelectDialog);
    actionSelectLayout.addWidget(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &actionSelectDialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &actionSelectDialog, &QDialog::reject);

    if (actionSelectDialog.exec() == QDialog::Accepted) {
        if (abilityRadio->isChecked()) {
            return 0; // L'utente ha scelto di usare l'abilità
        } else if (moveRadio->isChecked()) {
            return 1; // L'utente ha scelto di selezionare una mossa
        }
    }

    return -1; // Nessuna scelta o dialogo annullato
}


void Gui::attack(){
    Character * attacker = chooseCharacter(battleManager->getTeam(1),QString("Scegli un Personaggio con cui Attaccare"));
    Character* defender = nullptr;
    Move* move = nullptr;
    if(attacker) {
        if(chooseKombatAction()==1){
            move = chooseMove(attacker);
        }
        else{
            //attacker->useAbility();
        }
    }
    if(move){
        defender = chooseCharacter(battleManager->getTeam(2),QString("Scegli il target"));
        if(defender){
            move->useMove(attacker,defender);
            battleManager->update();
            battleManager->updateTurn();
        }
    }

}


//=========================
void Gui::showCharacterInfoDialog(Character* character){
    QDialog characterInfoDialog(this);
    characterInfoDialog.setWindowTitle("Informazioni sul Personaggio");

    QVBoxLayout characterInfoLayout(&characterInfoDialog);

    QLabel nameLabel("Nome: " + character->getName());
    QLabel characterLabel("Character Type:  " + toText(character->getCharType()));
    QLabel typeLabel("Types:  ");
    QLabel phAtkLabel("Danno Fisico:  " + QString::number(character->getPhyAtk()));
    QLabel magAtkLabel("Attacco Magico:   " + QString::number(character->getMagAtk()));
    QLabel phDefLabel("Difesa fisica:   "+ QString::number(character->getPhyDef()));
    QLabel magDefLabel("Difesa Magica:  "+ QString::number(character->getMagDef()));
    QLabel movesNames("Mosse:  " + character->getMovesNames());

    characterInfoLayout.addWidget(&nameLabel);
    characterInfoLayout.addWidget(&characterLabel);
    characterInfoLayout.addWidget(&phAtkLabel);
    characterInfoLayout.addWidget(&magAtkLabel);
    characterInfoLayout.addWidget(&phDefLabel);
    characterInfoLayout.addWidget(&magDefLabel);
    characterInfoLayout.addWidget(&movesNames);

    Goblin* goblin = dynamic_cast<Goblin*>(character);
    QLabel amountLabel;
    if(goblin){
        amountLabel.setText("Amount of Goblins:   " + QString::number(goblin->getAmount()));
        characterInfoLayout.addWidget(&amountLabel);
    }

    QDialogButtonBox closeButton(QDialogButtonBox::Close, &characterInfoDialog);
    characterInfoLayout.addWidget(&closeButton);

    connect(&closeButton, &QDialogButtonBox::rejected, &characterInfoDialog, &QDialog::reject);

    characterInfoDialog.exec();
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

//=========================


void Gui::squadManagement() {
    QDialog* characterSelectDialog = new QDialog(this);
    characterSelectDialog->setWindowTitle("Selezione dei Personaggi");

    QVBoxLayout characterSelectLayout(characterSelectDialog);

    QButtonGroup characterGroup;  // Gruppo per gestire i bottoni radio

    Character* selectedCharacter=nullptr;

    for (Character* character : *squad) {
        QVBoxLayout* itemLayout = new QVBoxLayout();

        QLabel* characterLabel = new QLabel(character->getName());
        characterLabel->setStyleSheet("font-size: 15px; color: black;");

        QRadioButton* selectRadio = new QRadioButton("Seleziona");
        itemLayout->addWidget(characterLabel);
        itemLayout->addWidget(selectRadio);

        characterSelectLayout.addLayout(itemLayout);

        QPushButton* infoButton = new QPushButton("Info");
        connect(infoButton, &QPushButton::clicked, [=]() {
            showCharacterInfoDialog(character);
        });
        characterSelectLayout.addWidget(infoButton);

        // Aggiungi il pulsante radio al gruppo
        characterGroup.addButton(selectRadio);

        // Connetti il segnale del pulsante radio per gestire la selezione del personaggio
        connect(selectRadio, &QRadioButton::clicked, [&selectedCharacter,&selectRadio,&character,this]() {
            if (selectRadio->isChecked()) {
                // Il personaggio è selezionato, puoi fare qualcosa con esso
                //QMessageBox::critical(this, "Errore", character->getName());
                selectedCharacter=character;
            }
        });
    }

    QDialogButtonBox characterSelectButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QPushButton* addCharacterButton = new QPushButton("Aggiungi Personaggio");
    characterSelectButtonBox.addButton(addCharacterButton, QDialogButtonBox::ActionRole);
    characterSelectLayout.addWidget(&characterSelectButtonBox);

    connect(&characterSelectButtonBox, &QDialogButtonBox::accepted, characterSelectDialog, &QDialog::accept);
    connect(&characterSelectButtonBox, &QDialogButtonBox::rejected, characterSelectDialog, &QDialog::reject);
    connect(addCharacterButton, &QPushButton::clicked, [=]() {
        characterSelection();
        moveSelection();
        characterSelectDialog->close();
        squadManagement();
        characterSelectDialog->deleteLater();
        return;
    });

    if (characterSelectDialog->exec() == QDialog::Accepted) {
        if(selectedCharacter)
            chooseAction(selectedCharacter);
        else {
            characterSelectDialog->deleteLater();
            return;
        }
    }
    characterSelectDialog->deleteLater();
    return;
}



// Funzione per la selezione delle mosse
int Gui::updateMoves(Character* character) {
    QDialog moveDialog(this);
    moveDialog.setWindowTitle("Selezione Mosse per " + character->getName());

    QVBoxLayout mainLayout(&moveDialog);

    std::set<QString> movesToAdd;  // Utilizza un set invece di un vettore

    // Crea una QScrollArea per la lista delle mosse
    QScrollArea scrollArea;
    QWidget* scrollContent = new QWidget(&scrollArea);
    QVBoxLayout moveLayout(scrollContent);

    for (Move* move : movesManager->getCompatibleMoves(character)) {
        QVBoxLayout *itemLayout = new QVBoxLayout();

        QLabel* moveLabel = new QLabel(move->getName());
        moveLabel->setStyleSheet("font-size: 15px; color: black;");

        QCheckBox* selectCheckBox = new QCheckBox("Seleziona");
        itemLayout->addWidget(moveLabel);
        itemLayout->addWidget(selectCheckBox);

        moveLayout.addLayout(itemLayout);

        QPushButton* infoButton = new QPushButton("Info");
        connect(infoButton, &QPushButton::clicked, [=]() {
            showMoveInfoDialog(move);
        });
        moveLayout.addWidget(infoButton);

        connect(selectCheckBox, &QCheckBox::stateChanged, [move, &movesToAdd, selectCheckBox](int state) {
            if (state == Qt::Checked) {
                if (selectCheckBox->isChecked()) {
                    movesToAdd.insert(move->getName());
                    //qDebug() << "Selected Move Name: " << move->getName();
                }
            } else if (state == Qt::Unchecked) {
                movesToAdd.erase(move->getName());
                //qDebug() << "Unselected Move Name: " << move->getName();
            }
        });
    }

    scrollContent->setLayout(&moveLayout);
    scrollArea.setWidget(scrollContent);
    scrollArea.setWidgetResizable(true);
    mainLayout.addWidget(&scrollArea);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &moveDialog);
    mainLayout.addWidget(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &moveDialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &moveDialog, &QDialog::reject);

    if (moveDialog.exec() == QDialog::Accepted) {
        if (movesToAdd.size() != 2) {
            QMessageBox::critical(this, "Errore", "Devi selezionare esattamente 2 mosse per personaggio");
            return 0;
        }
        else {
            auto it = movesToAdd.begin();
                Move* firstMove = movesManager->moveByName(*it);
                ++it;
                Move* secondMove = movesManager->moveByName(*it);

                character->clearMoves();
                character->addMove(firstMove, secondMove);
                return 2;
        }
    }

    return 1;
}


//=========================

void Gui::chooseAction(Character* character) {
   QMessageBox confirmBox(QMessageBox::Question, "Conferma Azione", "Vuoi eliminare o modificare le mosse di " + character->getName() + "?", QMessageBox::NoButton, this);

   QPushButton* modifyButton = confirmBox.addButton("Modifica Mosse", QMessageBox::ActionRole);
   QPushButton* deleteButton = confirmBox.addButton("Elimina Personaggio", QMessageBox::YesRole);

   confirmBox.setDefaultButton(QMessageBox::Close);

   confirmBox.exec();

   if (confirmBox.clickedButton() == modifyButton) {
       bool correctInsertion = false;
       while (!correctInsertion) {
           correctInsertion = updateMoves(character);
           squadManagement();
       }
   } else if (confirmBox.clickedButton() == deleteButton) {
       squad->deleteByName(character->getName());
       squadManagement();
   }
}

void Gui::moveSelection() {

    for (Character* character : *squad) {
        if(character->getMovesNames()==""){
            int insertionCheck = 0;
            while(insertionCheck == 0) insertionCheck = updateMoves(character);
        }
    }
}

void Gui::characterSelection(){

    QDialog *characterSelectionDialog = new QDialog(this);
    characterSelectionDialog->setWindowTitle("Select Characters");

    QVBoxLayout *mainLayout = new QVBoxLayout(characterSelectionDialog);

    QLabel *remainingCapacityLabel = new QLabel("Remaining Capacity: " + QString::number(squad->getCurrentCapacity()));
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

        for (auto it = characterMap.cbegin(); it != characterMap.cend(); ++it) {
            QString key = it.key();
            QPair<int, int> value = it.value();

            if (key == "Goblin" && value.second > 0) {

                Goblin* goblin=nullptr;
                for(auto character : *squad){
                    goblin = dynamic_cast<Goblin*>(character);
                }
                if(goblin){
                    QMessageBox::warning(this, "Ord of Goblins yet created", "A ord of goblins was yet created so the goblins you added will be added to it.");
                    int amount = goblin->getAmount()+value.second;
                    goblin->setAmount(amount);
                }
                else{
                    QString name=QInputDialog::getText(this, "Enter Name", "Enter a name for the Ord of Goblins:");
                    while(name.isEmpty()){
                        QMessageBox::warning(this, "Missing Name", "You must enter a name for the Ord of Goblins.");
                        name= QInputDialog::getText(this, "Enter Name", "Enter a name for the Ord of Goblins:");
                    }

                    while(squad->isNameTaken(name)){
                        QMessageBox::warning(this, "Duplicate Name", "This name is already used. Please choose a different name.");
                        name = QInputDialog::getText(this, "Enter Name", "Enter a name for the " + key + ":");
                    }

                    squad->addCharacter(new Goblin(name,value.second));
                }
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
        return;
    }
    delete characterSelectionDialog;
    return;
}


//=========================

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
        characterSelection();
        if (!squad->isEmpty()) {
            moveSelection();
            managementScreen();
        }
    });

    connect(loadButton, &QPushButton::clicked, [&]() {
        //Squad* squad =Parser()...
        managementScreen();
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


void Gui::managementScreen() {

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
    connect(saveSquadButton, &QPushButton::clicked, [this]() {

    });

    connect(editSquadButton, &QPushButton::clicked, [this]() {
        squadManagement();
        managementScreen();
    });

    connect(loadSquadButton, &QPushButton::clicked, [this]() {

    });

    connect(startKombatButton, &QPushButton::clicked, [this]() {
        kombatScreen();
    });
}

void Gui::kombatScreen() {

    QWidget* managementWidget = centralWidget();
    QWidget *kombatWidget = new QWidget(this);
    setCentralWidget(kombatWidget);
    delete managementWidget;

    // Crea un layout principale per la finestra di combattimento
    QVBoxLayout *mainLayout = new QVBoxLayout(kombatWidget);

    // Crea un layout orizzontale per la parte superiore della finestra (informazioni sulla squadra)
    QHBoxLayout *topLayout = new QHBoxLayout();

    // Crea una sezione per visualizzare i membri della tua squadra
    QWidget *yourTeamWidget = new QWidget(kombatWidget);
    QVBoxLayout *yourTeamLayout = new QVBoxLayout(yourTeamWidget);

    // Crea una sezione per visualizzare l'avversario
    QWidget *opponentWidget = new QWidget(kombatWidget);
    QVBoxLayout *opponentLayout = new QVBoxLayout(opponentWidget);

    Squad* opponentSquad= new Squad();
    opponentSquad->addCharacter(new Dragon("ADAM"));

    battleManager = new BattleManager(squad,opponentSquad);

    updateKombatScreen(yourTeamLayout,opponentLayout);

    topLayout->addWidget(yourTeamWidget);
    topLayout->addWidget(opponentWidget);

    mainLayout->addLayout(topLayout);

    // Crea un pulsante per l'attacco
    QPushButton *attackButton = new QPushButton("Attacca", kombatWidget);

    mainLayout->addWidget(attackButton);

    QHBoxLayout *exitLayout = new QHBoxLayout();

    // Crea un pulsante "Esci" più piccolo
    QPushButton *exitButton = new QPushButton("Esci", kombatWidget);
    exitButton->setFixedSize(80, 30); // Imposta le dimensioni desiderate

    // Aggiungi il pulsante "Esci" al layout orizzontale
    exitLayout->addWidget(exitButton, Qt::AlignRight | Qt::AlignBottom);

    // Imposta il layout principale per la finestra di combattimento
    kombatWidget->setLayout(mainLayout);

    // Connetti il pulsante "Attacca" a una funzione per gestire l'attacco
    connect(attackButton, &QPushButton::clicked,[=](){
        attack();
        updateKombatScreen(yourTeamLayout,opponentLayout);
    });

    connect(exitButton, &QPushButton::clicked, [=]() {
        managementScreen();
    });

}


//=========================


Gui::Gui(QWidget* parent): QMainWindow(parent)
{
    movesManager=new MovesManager();
    battleManager=nullptr;
    squad=new Squad();

    createMenus();
    setCentralWidget(new QWidget());
    startScreen();
}
