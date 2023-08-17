#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>


void startScreen(QWidget* window){
    // Create the main window
    window->setWindowTitle("QtKombat");
    window->setFixedSize(750, 400); // Set initial window size

    // Create a vertical layout for the window
    QVBoxLayout *layout = new QVBoxLayout(window);

    // Add a label with the game name
    QLabel *titleLabel = new QLabel("BENVENUTO FROCIO");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Create and configure the start button
    QPushButton *startButton = new QPushButton("Inizia");
    startButton->setFixedSize(100, 50);
    startButton->setStyleSheet("font-size: 18px;");
    layout->addWidget(startButton, 0, Qt::AlignCenter); // Center the button

    // Connect the button to the start action
    QObject::connect(startButton, &QPushButton::clicked, [&](){
        // Add code here to proceed to the next game screen
    });

    // Set the layout as the main layout of the window
    window->setLayout(layout);

    //Set the Icon
    window->setWindowIcon(QIcon(":/Resources/logo.png"));

    // Show the window

    window->show();
}
