#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the main window
    QWidget window;
    window.setWindowTitle("QtKombat");
    window.setFixedSize(750, 400); // Set initial window size

    // Set background image
    QPixmap backgroundImage("background.jpg");
    QPalette palette;
    palette.setBrush(window.backgroundRole(), QBrush(backgroundImage));
    window.setPalette(palette);

    // Create a vertical layout for the window
    QVBoxLayout *layout = new QVBoxLayout(&window);

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
    window.setLayout(layout);

    // Show the window
    window.show();

    return app.exec();
}
