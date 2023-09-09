#include "gui.h"

void Gui::createMenus()
{
    QMenuBar *menuBar = new QMenuBar(this);

    layout()->setMenuBar(menuBar);
}

bool Gui::enoughCapacity(const QString &characterName, const int unitCount,  const QHash<QString,QPair<int,int>>& characterMap) const{
    int totalSelectedWeight = 0;
    for (auto i = characterMap.cbegin(); i != characterMap.cend(); ++i) {
        QString key = i.key();
        QPair<int,int> value = i.value();
        if(key!=characterName)
            totalSelectedWeight += value.first * value.second;
    }
    int remainingWeight = squad->getCurrentCapacity() - (totalSelectedWeight + characterMap[characterName].first *unitCount) ;
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
    remainingCapacityLabel->setText("Spazio rimanente per la tua squadra: " + QString::number(remainingCapacity));
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

    QLabel *yourTeamLabel = new QLabel("La tua squadra:");
    yourTeamLabel->setStyleSheet("font-size: 20px;color:red");
    yourTeamLayout->addWidget(yourTeamLabel);

    QLabel *opponentLabel = new QLabel("Il tuo avversario:");
    opponentLabel->setStyleSheet("font-size: 20px;color:red");
    opponentLayout->addWidget(opponentLabel);

    for (Character* character : *battleManager->getTeam(1)) {
        QLabel* label = new QLabel(character->getName() + "   " + QString::number(character->getLifePoints()) + " Life Points");
        yourTeamLayout->addWidget(label);
    }

    for (Character* character : *battleManager->getTeam(2)) {
        QLabel* label = new QLabel(character->getName() + "   " + QString::number(character->getLifePoints()) + " Life Points");
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

    return nullptr;
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
                return const_cast<Move*>(firstMove);
            } else if (selectedMoveName == secondMove->getName()) {
                return const_cast<Move*>(secondMove);
            }
        }
    }

    return nullptr;
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
            return 0;
        } else if (moveRadio->isChecked()) {
            return 1;
        }
    }

    return -1;
}


int Gui::attack(){
    Character * attacker = chooseCharacter(battleManager->getTeam(1),QString("Scegli un Personaggio con cui Attaccare"));
    Character* target = nullptr;
    Move* move = nullptr;
    if(attacker) {
        int action = chooseKombatAction();
        if(action==1){
            move = chooseMove(attacker);
        }
        else if(action==0){
            bool abilityUsed = attacker->getAbilityUsed();
            if(abilityUsed){ QMessageBox::critical(nullptr, "Errore", "Abilitá giá usata"); return 0;}
            else{
                CharType chty = attacker->getCharType();
                bool abFr, abTar;

                if(chty==CharType::Goblin){ abFr = Goblin::abilityFriendly;  abTar = Goblin::abilityHasTarget;}
                if(chty==CharType::Knight){ abFr = Knight::abilityFriendly;  abTar = Knight::abilityHasTarget;}
                if(chty==CharType::Wizard){ abFr = Wizard::abilityFriendly;  abTar = Wizard::abilityHasTarget;}
                if(chty==CharType::Cleric){ abFr = Cleric::abilityFriendly;  abTar = Cleric::abilityHasTarget;}
                if(chty==CharType::Dragon){ abFr = Dragon::abilityFriendly;  abTar = Dragon::abilityHasTarget;}

                if(!abTar) { attacker->useAbility(nullptr); QMessageBox::warning(nullptr, "Abilitá usata correttamente" , attacker->getName() + " ha usato la sua abilitá"); }

                else if(abTar && abFr){ target = chooseCharacter(battleManager->getTeam(1),QString("Scegli il target")); if(target==0) return 0; }
                else if(abTar && !abFr){ target = chooseCharacter(battleManager->getTeam(2),QString("Scegli il target")); if(target==0) return 0; }

                if(target) { attacker->useAbility(target); QMessageBox::warning(nullptr, "Abilitá usata correttamente" , attacker->getName() + " ha usato la sua abilitá su " + target->getName() );}
            }
        }
        else return 0;
    }
    if(move){
        if(dynamic_cast<StatisticMove*>(move) && static_cast<StatisticMove*>(move)->isFriendly()){
            target = chooseCharacter(battleManager->getTeam(1),QString("Scegli il target"));
        }
        else target = chooseCharacter(battleManager->getTeam(2),QString("Scegli il target"));
        if(target){
            QMessageBox::warning(nullptr,"Mossa eseguita","Danni inflitti: "+ QString::number(move->useMove(attacker,target)));
            qDebug() << attacker->getName() << " ha usato " << move->getName() << " colpendo " << target->getName()  ;
            qDebug() << target->getLifePoints() << "    "<< move->getPhyDmg();
        }
    }

    int i=battleManager->update();
    if(i!=0) return i;
    QMessageBox::warning(nullptr, "Brutte Notizie", "Ora é il turno del tuo avversario");
    battleManager->opponentKombatLogic();
    i=battleManager->update();
    if(i!=0) return i;
    battleManager->updateTurn();
    return 0;
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
    QLabel abilityDescription("");

    CharType chartype = character->getCharType();
    if(chartype==CharType::Goblin) abilityDescription.setText("Descrizione abilitá:  " + Goblin::getAbilityDescription());
    if(chartype==CharType::Knight) abilityDescription.setText("Descrizione abilitá:  " + Knight::getAbilityDescription());
    if(chartype==CharType::Cleric) abilityDescription.setText("Descrizione abilitá:  " + Cleric::getAbilityDescription());
    if(chartype==CharType::Wizard) abilityDescription.setText("Descrizione abilitá:  " + Wizard::getAbilityDescription());
    if(chartype==CharType::Dragon) abilityDescription.setText("Descrizione abilitá:  " + Dragon::getAbilityDescription());

    characterInfoLayout.addWidget(&nameLabel);
    characterInfoLayout.addWidget(&characterLabel);
    characterInfoLayout.addWidget(&phAtkLabel);
    characterInfoLayout.addWidget(&magAtkLabel);
    characterInfoLayout.addWidget(&phDefLabel);
    characterInfoLayout.addWidget(&magDefLabel);
    characterInfoLayout.addWidget(&movesNames);
    characterInfoLayout.addWidget(&abilityDescription);

    Goblin* goblin = dynamic_cast<Goblin*>(character);
    QLabel amountLabel;
    if(goblin){
        amountLabel.setText("Numero di Goblins:   " + QString::number(goblin->getAmount()));
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

    QButtonGroup characterGroup;

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

        characterGroup.addButton(selectRadio);

        connect(selectRadio, &QRadioButton::clicked, [&selectedCharacter,&selectRadio,&character,this]() {
            if (selectRadio->isChecked()) {
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



int Gui::updateMoves(Character* character) {
    QDialog moveDialog(this);
    moveDialog.setWindowTitle("Selezione Mosse per " + character->getName());

    QVBoxLayout mainLayout(&moveDialog);

    std::set<QString> movesToAdd;

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
                }
            } else if (state == Qt::Unchecked) {
                movesToAdd.erase(move->getName());
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
    characterSelectionDialog->setWindowTitle("Seleziona i personaggi da aggiungere alla tua squadra: ");

    QVBoxLayout *mainLayout = new QVBoxLayout(characterSelectionDialog);

    QLabel *remainingCapacityLabel = new QLabel("Spazio rimanente per la tua squadra: " + QString::number(squad->getCurrentCapacity()));
    mainLayout->addWidget(remainingCapacityLabel);

    QHash<QString,QPair<int,int>> characterMap; // Map to store character weights per unit and number of occurencies
    characterMap.insert("Goblin", QPair<int,int>(goblinStats.weight,0));
    characterMap.insert("Knight", QPair<int,int>(knightStats.weight,0));
    characterMap.insert("Wizard", QPair<int,int>(wizardStats.weight,0));
    characterMap.insert("Cleric", QPair<int,int>(clericStats.weight,0));
    characterMap.insert("Dragon", QPair<int,int>(dragonStats.weight,0));

    //Boxes

        //GoblinBox
        QSpinBox *goblinSpinBox = new QSpinBox;
        goblinSpinBox->setRange(0, Squad::capacity);
        QLabel *goblinLabel = new QLabel("Goblin: ");
        mainLayout->addWidget(goblinLabel);
        mainLayout->addWidget(goblinSpinBox);

        // KnightBox
        QSpinBox *knightSpinBox = new QSpinBox;
        knightSpinBox->setRange(0, Squad::capacity);
        QLabel *knightLabel = new QLabel("Knight: " );
        mainLayout->addWidget(knightLabel);
        mainLayout->addWidget(knightSpinBox);

        //WizardBox
        QSpinBox *wizardSpinBox = new QSpinBox;
        wizardSpinBox->setRange(0, Squad::capacity);
        QLabel *wizardLabel = new QLabel("Wizard: ");
        mainLayout->addWidget(wizardLabel);
        mainLayout->addWidget(wizardSpinBox);

        //ClericBox
        QSpinBox *clericSpinBox = new QSpinBox;
        clericSpinBox->setRange(0, Squad::capacity);
        QLabel *clericLabel = new QLabel("Cleric: ");
        mainLayout->addWidget(clericLabel);
        mainLayout->addWidget(clericSpinBox);

        //DragonBox
        QSpinBox *dragonSpinBox = new QSpinBox;
        dragonSpinBox->setRange(0, Squad::capacity);
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
                QMessageBox::warning(this, "Capacitá superata", "Non c'é piú spazio nella squadra");
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
                QMessageBox::warning(this, "Capacitá superata", "Non c'é piú spazio nella squadra");
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
                QMessageBox::warning(this, "Capacitá superata", "Non c'é piú spazio nella squadra");
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
                QMessageBox::warning(this, "Capacitá superata", "Non c'é piú spazio nella squadra");
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
                QMessageBox::warning(this, "Capacitá superata", "Non c'é piú spazio nella squadra");
                dragonSpinBox->setValue(characterMap[character].second);
            }
        });


    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    mainLayout->addWidget(buttonBox);

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, characterSelectionDialog, &QDialog::accept);

    QObject::connect(buttonBox, &QDialogButtonBox::rejected, characterSelectionDialog, &QDialog::reject);

    if (characterSelectionDialog->exec() == QDialog::Accepted) {

        for (auto it = characterMap.cbegin(); it != characterMap.cend(); ++it) {
            QString key = it.key();
            QPair<int, int> value = it.value();

            if (key == "Goblin" && value.second > 0) {

                Goblin* goblin=nullptr;
                for(auto character : *squad){
                    goblin = dynamic_cast<Goblin*>(character);
                }
                if(goblin){
                    QMessageBox::warning(this, "Orda di goblin giá creata", "I tuoi goblin verranno aggiunti all'orda preesistente");
                    int amount = goblin->getAmount()+value.second;
                    goblin->setAmount(amount);
                }
                else{
                    QString name=QInputDialog::getText(this, "Inserisci un nome", "Inserisci un nome per la tua orda di goblin");
                    while(name.isEmpty()){
                        QMessageBox::warning(this, "Nome mancante", "Devi inserire un nome");
                        name= QInputDialog::getText(this, "Inserisci un nome", "Inserisci un nome per la tua orda di goblin");
                    }

                    while(squad->isNameTaken(name)){
                        QMessageBox::warning(this, "Nome giá inserito", "Questo nome é giá stato inserito, inseriscine un altro");
                        name= QInputDialog::getText(this, "Inserisci un nome", "Inserisci un nome per la tua orda di goblin");
                    }

                    squad->addCharacter(new Goblin(name,value.second));
                }
            }

            else{
                for (int i = value.second; i != 0; i--) {
                    QString name = QInputDialog::getText(this, "Inserisci un nome", "Inserisci un nome per " + key + ":");
                    while(name.isEmpty()) {
                        QMessageBox::warning(this, "Nome mancante", "Devi inserire un nome per " + key + ".");
                        name = QInputDialog::getText(this, "Inserisci un nome", "Inserisci un nome per " + key + ":");
                    }

                    while(squad->isNameTaken(name)){
                        QMessageBox::warning(this, "Nome giá inserito", "Questo nome é giá stato inserito, inseriscine un altro");
                        name = QInputDialog::getText(this, "Inserisci un nome", "Inserisci un nome per " + key + ":");
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
    setFixedSize(750, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("BENVENUTO IN QTKombat");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *createButton = new QPushButton("Crea una squadra");
    createButton->setFixedSize(200, 50);
    createButton->setStyleSheet("font-size: 18px;");

    QPushButton *loadButton = new QPushButton("Carica una squadra");
    loadButton->setFixedSize(200, 50);
    loadButton->setStyleSheet("font-size: 18px;");

    connect(createButton, &QPushButton::clicked, [&]() {
        characterSelection();
        if (!squad->isEmpty()) {
            moveSelection();
            managementScreen();
        }
    });

    connect(loadButton, &QPushButton::clicked, [&]() {
        try {
            QString filePath = QFileDialog::getOpenFileName(
                this,
                "Seleziona un file",
                QDir::homePath(),
                "File JSON (*.json)"
            );

            if (filePath.isEmpty())
                throw std::runtime_error("Percorso non selezionato!");

            squad = Parser::loadSquad(filePath);
            QMessageBox::information(this, "Squadra caricata", "La tua squadra è stata caricata con successo!");
            managementScreen();

        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Errore", "C'è stato un errore nel caricamento della squadra: " + QString(e.what()));
        }
    });

    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(loadButton);

    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(buttonLayout);

    QWidget* central = centralWidget();
    if (central->layout()) {
        QLayout* existingLayout = central->layout();
        central->setLayout(nullptr);
        delete existingLayout;
    }

    central->setLayout(mainLayout);

    show();
}


void Gui::managementScreen() {

    QWidget *buttonWidget = new QWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(buttonWidget);

    QHBoxLayout *topButtonLayout = new QHBoxLayout();

    QPushButton *saveSquadButton = new QPushButton("Salva la squadra");
    saveSquadButton->setFixedSize(200, 70);
    saveSquadButton->setStyleSheet("font-size: 12px;");

    QPushButton *editSquadButton = new QPushButton("Modifica la squadra");
    editSquadButton->setFixedSize(200, 70);
    editSquadButton->setStyleSheet("font-size: 12px;");

    QPushButton *loadSquadButton = new QPushButton("Carica una squadra");
    loadSquadButton->setFixedSize(200, 70);
    loadSquadButton->setStyleSheet("font-size: 12px;");

    topButtonLayout->addWidget(saveSquadButton);
    topButtonLayout->addWidget(editSquadButton);
    topButtonLayout->addWidget(loadSquadButton);

    QPushButton *startKombatButton = new QPushButton("Inizia il Kombattimento");
    startKombatButton->setFixedSize(200, 70);
    startKombatButton->setStyleSheet("font-size: 12px;background-color: red; color: black;");

    QHBoxLayout *centerButtonLayout = new QHBoxLayout();
    centerButtonLayout->addStretch();
    centerButtonLayout->addWidget(startKombatButton);
    centerButtonLayout->addStretch();

    mainLayout->addLayout(topButtonLayout);
    mainLayout->addLayout(centerButtonLayout);

    QWidget *previousWidget = centralWidget();
    setCentralWidget(buttonWidget);
    delete previousWidget;

    connect(saveSquadButton, &QPushButton::clicked, [this]() {
        try {
            QString filePath = QFileDialog::getSaveFileName(
                this,
                "Seleziona un file",
                QDir::homePath(),
                "File JSON (*.json)"
            );

            if (filePath.isEmpty())
                throw std::runtime_error("Percorso non selezionato!");

            Parser::saveSquad(filePath, *squad);
            QMessageBox::information(this, "Squadra salvata", "La tua squadra è stata salvata con successo!");

        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Errore", "C'è stato un errore nel caricamento della squadra: " + QString(e.what()));
        }
    });

    connect(editSquadButton, &QPushButton::clicked, [this]() {
        squadManagement();
        managementScreen();
    });

    connect(loadSquadButton, &QPushButton::clicked, [this]() {
        try {
            QString filePath = QFileDialog::getOpenFileName(
                this,
                "Seleziona un file",
                QDir::homePath(),
                "File JSON (*.json)"
            );

            if (filePath.isEmpty())
                throw std::runtime_error("Percorso non selezionato!");

            squad = Parser::loadSquad(filePath);
            QMessageBox::information(this, "Squadra caricata", "La tua squadra è stata caricata con successo!");

        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Errore", "C'è stato un errore nel caricamento della squadra: " + QString(e.what()));
        }
    });

    connect(startKombatButton, &QPushButton::clicked, [this]() {
        if(squad){
            if(squad->getSize()==0) QMessageBox::critical(nullptr, "Errore", "Devi avere almeno un personaggio nella tua squadra");
            else{
                bool kombatPossible= true;
                for(Character* character : *squad){
                    if(character->getMovesNames()=="") kombatPossible=false;
                }
                if(kombatPossible) kombatScreen();
                else QMessageBox::critical(nullptr, "Errore", "Devi selezionare esattamente 2 mosse per ogni personaggio della tua squadra");
            }
        }
    });
}

void Gui::kombatScreen() {

    QWidget* managementWidget = centralWidget();
    QWidget *kombatWidget = new QWidget(this);
    setCentralWidget(kombatWidget);
    delete managementWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout(kombatWidget);

    QHBoxLayout *topLayout = new QHBoxLayout();

    QWidget *yourTeamWidget = new QWidget(kombatWidget);
    QVBoxLayout *yourTeamLayout = new QVBoxLayout(yourTeamWidget);

    QWidget *opponentWidget = new QWidget(kombatWidget);
    QVBoxLayout *opponentLayout = new QVBoxLayout(opponentWidget);

    battleManager = new BattleManager(squad,nullptr);
    battleManager->setBossBattle(movesManager);

    updateKombatScreen(yourTeamLayout,opponentLayout);

    topLayout->addWidget(yourTeamWidget);
    topLayout->addWidget(opponentWidget);

    mainLayout->addLayout(topLayout);

    QPushButton *attackButton = new QPushButton("Attacca", kombatWidget);

    mainLayout->addWidget(attackButton);

    QHBoxLayout *exitLayout = new QHBoxLayout();

    // Crea un pulsante "Esci" più piccolo
    QPushButton *exitButton = new QPushButton("Esci", kombatWidget);
    exitButton->setFixedSize(80, 30);

    exitLayout->addWidget(exitButton, Qt::AlignRight | Qt::AlignBottom);

    kombatWidget->setLayout(mainLayout);

    connect(attackButton, &QPushButton::clicked,[=](){
        int i = attack();
        updateKombatScreen(yourTeamLayout,opponentLayout);
        if(i==1){
            QMessageBox::warning(nullptr, "SCONFITTA", "Tutti i personaggi della tua squadra sono morti");
            delete battleManager;
            managementScreen();
        }
        if(i==2){
            QMessageBox::warning(nullptr, "VITTORIA", "Hai sconfitto il tuo avversario");

            delete battleManager;
            managementScreen();
        }
    });

    connect(exitButton, &QPushButton::clicked, [=]() {
        delete battleManager;
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
