#include "gui.h"

void Gui::createMenus()
{
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *squadMenu = new QMenu("Squad", this);

    QAction *saveAction = new QAction("Save", this);
    QAction *loadAction = new QAction("Load", this);

    // Connect the actions to their respective slots
    connect(saveAction, &QAction::triggered, this, &Gui::saveSquad);
    connect(loadAction, &QAction::triggered, this, &Gui::loadSquad);

    squadMenu->addAction(saveAction);
    squadMenu->addAction(loadAction);

    menuBar->addMenu(squadMenu);

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

void Gui::startScreen()
{

    setWindowTitle("QtKombat");
    setFixedSize(750, 400); // Set initial window size

    // Create a vertical layout for the window
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Add a label with the game name as the title
    QLabel *titleLabel = new QLabel("BENVENUTO FROCIO");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    // Create a horizontal layout for the buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // Create and configure the "Inizia" button
    QPushButton *startButton = new QPushButton("Inizia");
    startButton->setFixedSize(100, 50);
    startButton->setStyleSheet("font-size: 18px;");
    buttonLayout->addWidget(startButton);

    // Create and configure the "Documentazione" button
    QPushButton *documentationButton = new QPushButton("Documentazione");
    documentationButton->setFixedSize(150, 50);
    documentationButton->setStyleSheet("font-size: 18px;");
    buttonLayout->addWidget(documentationButton);

    // Connect the "Inizia" button to the character selection action
    QObject::connect(startButton, &QPushButton::clicked, [&](){
        characterSelection();
    });

    // Connect the "Documentazione" button to the documentation display action
    QObject::connect(documentationButton, &QPushButton::clicked, [&](){
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


void Gui::updateSelectedCharacters(QCheckBox *checkbox, const QString &characterName, QSet<QString>& selectedCharacters, QLabel* remainingCapacityLabel, QHash<QString,int>& characterWeights)
{
    if (checkbox->isChecked()) {
        selectedCharacters.insert(characterName);
    } else {
        selectedCharacters.remove(characterName);
    }

    updateRemainingCapacityLabel(selectedCharacters, remainingCapacityLabel, characterWeights);
}

void Gui::updateRemainingCapacityLabel(QSet<QString>& selectedCharacters,QLabel* remainingCapacityLabel, QHash<QString,int>& characterWeights)
{
    int totalSelectedWeight = 0;
    for (const QString &character : selectedCharacters) {
        totalSelectedWeight += characterWeights.value(character, 0);
    }

    int remainingWeight = Squad::capacity - totalSelectedWeight;
    remainingCapacityLabel->setText("Remaining Weight: " + QString::number(remainingWeight));
}

void Gui::characterSelection(){

    // Create a new dialog for character selection
    QDialog *characterSelectionDialog = new QDialog(this);
    characterSelectionDialog->setWindowTitle("Select Characters");

    // Create a vertical layout for the dialog
    QVBoxLayout *mainLayout = new QVBoxLayout(characterSelectionDialog);

    QLabel *remainingCapacityLabel = new QLabel("Remaining Capacity: " + QString::number(Squad::capacity));
    mainLayout->addWidget(remainingCapacityLabel);

    // Create checkboxes for character selection
    QCheckBox *KnightCheckbox = new QCheckBox("Knight");
    QCheckBox *WizardCheckbox = new QCheckBox("Wizard");
    QCheckBox *GoblinCheckbox = new QCheckBox("Goblin");
    QCheckBox *ClericCheckbox = new QCheckBox("Cleric");
    QCheckBox *DragonCheckbox = new QCheckBox("Dragon");
    // ... create more checkboxes for characters as needed

    // Add checkboxes to the layout
    mainLayout->addWidget(KnightCheckbox);
    mainLayout->addWidget(WizardCheckbox);
    mainLayout->addWidget(GoblinCheckbox);
    mainLayout->addWidget(ClericCheckbox);
    mainLayout->addWidget(DragonCheckbox);

    QHash<QString, int> characterWeights; // Map to store character weights
    characterWeights.insert("Knight",15);
    characterWeights.insert("Wizard",12);
    characterWeights.insert("Goblin",2);
    characterWeights.insert("Dragon",30);
    characterWeights.insert("Cleric",9);
    QSet<QString> selectedCharacters;     // Set to store selected characters

    QObject::connect(KnightCheckbox, &QCheckBox::toggled, this, [=, &selectedCharacters, &characterWeights]() {
        updateSelectedCharacters(KnightCheckbox,"Knight",selectedCharacters,remainingCapacityLabel,characterWeights);
    });
    QObject::connect(WizardCheckbox, &QCheckBox::toggled, this, [=, &selectedCharacters,  &characterWeights]() {
        updateSelectedCharacters(WizardCheckbox,"Wizard",selectedCharacters,remainingCapacityLabel,characterWeights);
    });
    QObject::connect(GoblinCheckbox, &QCheckBox::toggled, this, [=, &selectedCharacters, &characterWeights]() {
        updateSelectedCharacters(GoblinCheckbox,"Goblin",selectedCharacters,remainingCapacityLabel,characterWeights);
    });
    QObject::connect(ClericCheckbox, &QCheckBox::toggled, this, [=, &selectedCharacters,  &characterWeights]() {
        updateSelectedCharacters(ClericCheckbox,"Cleric",selectedCharacters,remainingCapacityLabel,characterWeights);
    });
    QObject::connect(DragonCheckbox, &QCheckBox::toggled, this, [=, &selectedCharacters, &characterWeights]() {
        updateSelectedCharacters(DragonCheckbox,"Dragon",selectedCharacters,remainingCapacityLabel,characterWeights);
    });

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
        if (KnightCheckbox->isChecked()) {
            squad.addCharacter(new Knight());

        }
        if (WizardCheckbox->isChecked()) {
            squad.addCharacter(new Wizard());
        }

        // Clean up memory

        delete buttonBox;
        delete mainLayout;
        delete characterSelectionDialog;

        moveSelection(squad);
    }
}
