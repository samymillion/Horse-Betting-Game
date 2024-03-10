#include <QApplication>
#include <QWidget>
#include <QPalette>
#include <QColor>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    // Create a main window
    QWidget mainWindow;
    mainWindow.setWindowTitle("PIXEL DERBY 2024");

    // Set background image of the window using stylesheets
    mainWindow.setStyleSheet("background-color: #171a17;");

    // Set window to fullscreen size
    mainWindow.showFullScreen();

    // Create a vertical layout to hold the line of buttons and the grid layout
    QVBoxLayout *mainLayout = new QVBoxLayout(&mainWindow);

    // Create a horizontal layout to hold the line of buttons
    QHBoxLayout *buttonBoxLayout = new QHBoxLayout;

    for (int i = 0; i < 3; ++i) {
        QPushButton *lineButton = new QPushButton();

        if(i == 0){
            lineButton->setFixedSize(400, 50);
            lineButton->setText("$42000");
            lineButton->setStyleSheet("font-family: Trebuchet MS Bold; background-color: #0f111a; background-position: center; font-size: 30px; color: white; border: 3px solid #282e42; border-radius: 5px;");
            buttonBoxLayout->addWidget(lineButton);
        }
        else if(i == 1){
            lineButton->setFixedSize(600, 50);
            lineButton->setText("S T A R T   R A C E");
            // Add border-radius to make the corners rounder
            lineButton->setStyleSheet("font: bold; background-image: url(gradient.png); background-position: center; font-size: 30px; color: white; border: 3px solid white; border-radius: 15px;");
            buttonBoxLayout->addWidget(lineButton);
        }
        else{
            lineButton->setFixedSize(400, 50);
            lineButton->setText("PIXELDERBY v1.0");
            buttonBoxLayout->addWidget(lineButton);
            lineButton->setStyleSheet("font-family: Verdana; background-image: url(gold.png); background-position: center; font-size: 25px; color: black; border: 1px solid black; border-radius: 5px;");
        }
    }
   

    mainLayout->addLayout(buttonBoxLayout);

    // Create a grid layout
    QGridLayout *gridLayout = new QGridLayout;

    // Create 5 by 20 grid of buttons
    const int numRows = 5;
    const int numCols = 25;

    // std::string colors[5] = {"blue.png", "brown.png", "green.png", "red.png", "yellow.png"};

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            QPushButton *button = new QPushButton();
            button->setFixedSize(50, 50); // Set the size of the button
            if(col == 0){
                if(row == 0){
                    button->setStyleSheet("background-color: #333b2b;");
                    button->setIcon(QIcon("brown.png"));
                    
                }
                if(row == 1){
                    button->setIcon(QIcon("blue.png"));
                    button->setStyleSheet("color: #69824e;");
                }
                if(row == 2){
                    button->setIcon(QIcon("green.png"));
                    button->setStyleSheet("color: #69824e;");
                }
                if(row == 3){
                    button->setIcon(QIcon("red.png"));
                    button->setStyleSheet("color: #69824e;");
                }
                if(row == 4){
                    button->setIcon(QIcon("yellow.png"));
                    button->setStyleSheet("color: #69824e;");
                }
                button->setIconSize(QSize(50, 50)); 
            }
            if(col == 24){
                button->setIcon(QIcon("fin.png"));
                button->setIconSize(QSize(50, 50)); 
            }
            else{
                button->setStyleSheet("background-color: white; color: back;");
            }
            gridLayout->addWidget(button, row, col); // Add button to the grid layout
        }
    }

    // CREATE CONNECTION FROM START BUTTON TO BACK END RACE SIM

    mainLayout->addLayout(gridLayout);

    // DELETE AFTER THIS
    gridLayout = new QGridLayout;

    QPushButton *button = new QPushButton();
    button->setFixedSize(470, 50);
    button->setText("PLAYER STATS");
    button->setStyleSheet("font-family: Trebuchet MS; background-color: #292b29; background-position: center; font-size: 25px; font-family: Trebuchet MS; color: white; border: 1px solid black;");
    gridLayout->addWidget(button, 0, 0);

    button = new QPushButton();
    button->setFixedSize(470, 50);
    button->setText("HORSE ROSTER");
    button->setStyleSheet("font-family: Trebuchet MS; background-color: #292b29; background-position: center; font-size: 25px; font-family: Trebuchet MS; color: white; border: 1px solid black;");
    gridLayout->addWidget(button, 0, 1);

    button = new QPushButton();
    button->setFixedSize(470, 50);
    button->setText("BETTING AMOUNT");
    button->setStyleSheet("font-family: Trebuchet MS; background-color: #292b29; background-position: center; font-size: 25px; font-family: Trebuchet MS; color: white; border: 1px solid black;");
    gridLayout->addWidget(button, 0, 2);

    // CREATE CONNECTION FROM START BUTTON TO BACK END RACE SIM

    mainLayout->addLayout(gridLayout);


    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    mainWindow.setMinimumSize(1920, 1080);

    mainWindow.setLayout(mainLayout); // Set the main layout as the layout of the main window

    mainWindow.show(); // Show the main window

    return app.exec();
}
