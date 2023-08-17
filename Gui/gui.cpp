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
        //CharacterSelection();
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

Gui::Gui(QWidget* parent): QWidget(parent)
{
    startScreen();
    createMenus();
}


