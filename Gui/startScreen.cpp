#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include<characterselection.h>


void startScreen(QWidget* window){
    // Create the main window
    window->setWindowTitle("QtKombat");
    window->setFixedSize(750, 400); // Set initial window size

    // Create a vertical layout for the window
    QVBoxLayout *mainLayout = new QVBoxLayout(window);

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
        CharacterSelection();
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
    window->setLayout(mainLayout);

    // Set the Icon
    window->setWindowIcon(QIcon(":/Resources/logo.png"));

    // Show the window
    window->show();
}
