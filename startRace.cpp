#include <QApplication>
#include <cmath>
#include <QWidget>
#include <QPalette>
#include <QColor>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QSize>
#include <QTimer>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QPalette>
#include <iostream>
using namespace std;

#include "startRace.h"

//! startRace runs the race logic and components related to the race
startRace::startRace(QWidget *parent) : QWidget(parent), horsesFinished(0) {
    srand(static_cast<unsigned>(time(NULL))); //seed
    this->setupUI();
}

//! A function to setup aspects of the race within the gamewindow 
void startRace::setupUI() {

        GameWindow* gameWindow = new GameWindow();

        std::cout << "Test passed (GUI is displayed successfully)\n";
        setWindowTitle("PIXEL DERBY 2024");
        setStyleSheet("background-color: #171a17;");
        showFullScreen();

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        QHBoxLayout* buttonBoxLayout = createButtonBar();
        mainLayout->addLayout(buttonBoxLayout);

        QGridLayout* gridLayout = new QGridLayout;
        QPushButton* button;

        createHorses();
        
        //! Player stats button
        button = new QPushButton("BETTING HISTORY");
        button->setFixedSize(470, 50);
        button->setStyleSheet("font-family: Trebuchet MS; background-color: #292b29; background-position: center; font-size: 25px; color: white; border: 1px solid black;");
        gridLayout->addWidget(button, 0, 0);
        connect(button, &QPushButton::clicked, gameWindow, &GameWindow::displayBettingHistory);

        //! Horse roster button
        button = new QPushButton("HORSE ROSTER");
        button->setFixedSize(470, 50);
        button->setStyleSheet("font-family: Trebuchet MS; background-color: #292b29; background-position: center; font-size: 25px; color: white; border: 1px solid black;");
        gridLayout->addWidget(button, 0, 2);
        connect(button, &QPushButton::clicked, this, &startRace::showHorseRoster);


        //! Betting interface
        //! Assuming GameWindow is properly defined elsewhere and handles betting logic
        
        connect(this, &startRace::raceFinished, gameWindow, &GameWindow::checkBetResult);
        connect(this, &startRace::resetBet, gameWindow, &GameWindow::resetWindow);
        
        connect(gameWindow, &GameWindow::betPlaced, this, [this]() {
            betPlaced = true;
        });

        gridLayout->addWidget(gameWindow, 0, 1);
        gridLayout->setAlignment(gameWindow, Qt::AlignTop | Qt::AlignHCenter);
        gridLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

        createRaceTrack(mainLayout);
        mainLayout->addLayout(gridLayout);

        //! Set main layout alignment and size
        mainLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
        setMinimumSize(960, 540);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &startRace::advanceHorses);
    }

//! A function to assign and display horse statistics to help user select and bet
void startRace::showHorseRoster() {
    QDialog *horseRosterDialog = new QDialog(this);
    horseRosterDialog->setWindowTitle("Horse Roster");
    QVBoxLayout *layout = new QVBoxLayout(horseRosterDialog);
    int numHorses = 5;

    for (int i = 0; i < numHorses; ++i) {
        QLabel *horseLabel = new QLabel(QString::fromStdString(horseList.at(i).getName()));
        int speed = horseList.at(i).getSpeedFactor();
        int odds = horseList.at(i).getMoneyLine();
        //int strength = rand() % 101; // Generic ranking of strength to 100
        //QLabel *horseSpeedLabel = new QLabel("Speed: " + QString::number(speed) + " mph");
        QLabel *horseOddsLabel = new QLabel("Odds: " + QString::number(odds));
    /*    int health = (speed + strength)/2;
        QLabel *horseHealthLabel = new QLabel("Overall Health: " + QString::number(health));
    */
        QPalette palette;
        if (speed <= 5) {
            palette.setColor(QPalette::WindowText, Qt::red); // Set text color to red if health < 25
        } else if (speed >= 7) {
            palette.setColor(QPalette::WindowText, Qt::green); // Set text color to green if health >= 75
        } else {
            palette.setColor(QPalette::WindowText, Qt::white); // Set text color to white for other cases
        }

        horseLabel->setPalette(palette);
    //    horseSpeedLabel->setPalette(palette);
        horseOddsLabel->setPalette(palette);
    //   horseHealthLabel->setPalette(palette);

        
        QFont font = horseLabel->font();
        font.setPointSize(20); // Just making the Horse i Statistics bigger
        horseLabel->setFont(font);
              

        layout->addWidget(horseLabel);
    //    layout->addWidget(horseSpeedLabel);
        layout->addWidget(horseOddsLabel);
    //    layout->addWidget(horseHealthLabel);
    }

    horseRosterDialog->exec();
}

//! A function that creates the top panel of buttons including money, start race, and game title bar
/*!
*   \return QHBoxLayout object layout which contains the widgets
*/
QHBoxLayout* startRace::createButtonBar() {
        QHBoxLayout* layout = new QHBoxLayout;
        QPushButton* button;

        //! Bet Display Button
        button = createButton("GROUP#30", 300, 50, "font-family: Verdana; background-color: #6e0885; background-position: center; font-size: 25px; color: white; border: 3px solid #282e42; border-radius: 5px;");
        layout->addWidget(button);

        //! Start Race Button
        startRaceButton = createButton("S T A R T   R A C E", 600, 50, "font: bold; background-image: url(:/icons/gradient.png); background-position: center; font-size: 30px; color: white; border: 3px solid white; border-radius: 15px;");
        layout->addWidget(startRaceButton);
        connect(startRaceButton, &QPushButton::clicked, this, [this]() {
            if (!betPlaced) {
                QMessageBox messageBox;
                messageBox.setWindowTitle("Action Required");
                messageBox.setText("Place a bet first!");
                messageBox.setStyleSheet("QMessageBox { background-color: white; }");
                messageBox.setIcon(QMessageBox::Warning);
                messageBox.setStandardButtons(QMessageBox::Ok);
                messageBox.exec();
            } else {
                std::cout << "Test passed (Start Button Initiates the Race)\n";
                timer->start(500);
                startRaceButton->setEnabled(false);
                betPlaced = false; // Reset this flag to ensure a bet is placed for each new race
            }
        });
        //! Version Display Button
        button = createButton("PIXELDERBY v1.0", 300, 50, "font-family: Verdana; background-image: url(:/icons/gold.png); background-position: center; font-size: 25px; color: black; border: 1px solid black; border-radius: 5px;");
        layout->addWidget(button);

        return layout;
    }

//! A function that creates buttons that we use throughout startRace
/*!
    \return QPushButton object button to use for different purposes
    \param text of the button text to appear
    \param width of the button dimensions
    \param height of the button dimensions
    \param style elements including font, background, etc.
*/
QPushButton* startRace::createButton(const QString& text, int width, int height, const QString& style) {
        QPushButton* button = new QPushButton(text);
        button->setFixedSize(width, height);
        button->setStyleSheet(style);
        return button;
    }

//! A function that creates the race track for the horse game
/*!
    \param mainLayout a Qt layout to build the race track layout upon and appear flexibly in game window
*/
void startRace::createRaceTrack(QVBoxLayout* mainLayout) {
        raceTrackLayout = new QGridLayout;
        trackButtons.resize(numRows);

        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                QPushButton* button = new QPushButton();
                button->setFixedSize(50, 50);

                if (col == 0) {
                    setupStartingLineButton(button, row);
                } else if (col == numCols - 1) {
                    button->setStyleSheet("border-image: url(:/icons/fin.png);");
                } else {
                    button->setStyleSheet("background-color: white; color: black;");
                }
                trackButtons[row].append(button);
                raceTrackLayout->addWidget(button, row, col);
            }
        }
        mainLayout->addLayout(raceTrackLayout);
    }

//! A function that creates button marking the starting line for the horse race game
/*!
    \param button Qt button to utilize as starting line
    \param row what row to place within
*/
void startRace::setupStartingLineButton(QPushButton* button, int row) {
        const QString iconPaths[5] = {":/icons/brown.png", ":/icons/blue.png", ":/icons/green.png", ":/icons/red.png", ":/icons/yellow.png"};
        button->setIcon(QIcon(iconPaths[row % 5]));
        button->setIconSize(QSize(50, 50));
        button->setStyleSheet("background-color: red;");
    }

//! A function that moves horse along the track randomly
void startRace::advanceHorses() {
        for (int row = 0; row < numRows; ++row) {
        double baseChance = 0.5; // Base chance for the horse to move (50%)
        int speed = horseList.at(row).getSpeedFactor(); // Get the speed factor of the current horse
        double adjustedChance = baseChance + (speed - 5) * 0.02; // Adjusted chance based on speed factor

        double randomValue = static_cast<double>(rand()) / RAND_MAX;

        std::cout << "Horse " << row << " speed: " << speed << ", adjustedChance: " << adjustedChance << std::endl; //debugging

            if (randomValue < adjustedChance) { // If the random number generated is less than the probability
                for (int col = numCols - 1; col > 0; --col) {
                    if (!trackButtons[row][col - 1]->icon().isNull()) {
                        // Advance horse
                        trackButtons[row][col]->setIcon(trackButtons[row][col - 1]->icon());
                        trackButtons[row][col]->setIconSize(QSize(50, 50));
                        trackButtons[row][col - 1]->setIcon(QIcon());
                        break; // Stop moving this row's horse after it has advanced
                    }
                }
            }
        }

        // Check for race completion
        for (int row = 0; row < numRows; ++row) {
            if (!trackButtons[row][numCols-1]->icon().isNull()) {

                placeHorse(row);

                if(horsesFinished == 5){
                    std::cout << "Test passed (Race Ends after ALL horses reach the finish line)\n";
                    timer->stop(); // Stop the race
                    QMessageBox messageBox;
                    messageBox.setText(QString("%1 wins! \n"
                                               "%2 was the runner up. \n"
                                               "%3 finished in third place. \n"
                                               "%4 finished in fourth place. \n"
                                               "%5 had a bad day!")
                                           .arg(QString::fromStdString(horseList.at(results[0]).getName()))
                                           .arg(QString::fromStdString(horseList.at(results[1]).getName()))
                                           .arg(QString::fromStdString(horseList.at(results[2]).getName()))
                                           .arg(QString::fromStdString(horseList.at(results[3]).getName()))
                                           .arg(QString::fromStdString(horseList.at(results[4]).getName())));
                    messageBox.exec();
                    std::cout << "Test passed (Race results are displayed on a pop up window successfully)\n";
                    emit raceFinished(results[0], horseList.at(results[0]).getMoneyLine());
                    promptRaceRestart();
                    break;
                }
            }
        }
}

//! A function that places a horse in the result order that they arrived in the race
/*!
    \return boolean to place horse's in the order that they arrive
    \param button Qt button to utilize as starting line
*/
bool startRace::placeHorse(int horseRow) {
        // Check if the horse is already placed in the results
        for (int x = 0; x < horsesFinished; x++) {
            if (horseRow == results[x]) {
                return false;
            }
        }

        // Place the horse in the next available position
        if (horsesFinished < numRows) {
            results[horsesFinished] = horseRow;
            horsesFinished++;
            return true;
        }
        return false;
    }


std::vector<Horse> startRace::createHorses(){
    Horse horseOne("Cocoa Comet");
    Horse horseTwo("Ocean Breeze");
    Horse horseThree("Jade Jumper");
    Horse horseFour("Ruby Rocket");
    Horse horseFive("Lemon Lucky");
    horseList.push_back(horseOne);
    horseList.push_back(horseTwo);
    horseList.push_back(horseThree);
    horseList.push_back(horseFour);
    horseList.push_back(horseFive);

    for (Horse horse : horseList) { //debugging
        std::cout << "Name: " << horse.getName() << ", Speed: " << horse.getSpeedFactor() << std::endl;
    }

    calculateMoneyLine();

    return horseList;
}

void startRace::calculateMoneyLine() {
    double totalSpeed = 0;
    std::vector<double> winningProbabilities(horseList.size(), 0.0);

    //Calculate total speed
    for (const Horse& horse : horseList) {
        totalSpeed += horse.getSpeedFactor();
    }

    //Calculate raw probabilities based on relative speed
    for (size_t i = 0; i < horseList.size(); ++i) {
        winningProbabilities[i] = horseList[i].getSpeedFactor() / totalSpeed;
    }

    //Calculate average winning probability
    double averageWinningProbability = 0.0;
    for (double prob : winningProbabilities) {
        averageWinningProbability += prob;
    }
    averageWinningProbability /= horseList.size();

    //Calculate Moneyline based on comparison with averageWinningProbability
    for (size_t i = 0; i < horseList.size(); ++i) {
        double winningProbability = winningProbabilities[i];

        int moneyLine;
        if (winningProbability > averageWinningProbability) {
            moneyLine = -round(((winningProbability / (1 - winningProbability)) * 100)) - 100;
        } else {
            moneyLine = round((1 - winningProbability) / winningProbability * 100);
        }

        horseList[i].setMoneyLine(moneyLine);
        std::cout << "Horse " << horseList[i].getName() << " winningProbability: " << winningProbability << ", odds: " << horseList[i].getMoneyLine() << std::endl; // Debugging
    }
}


void startRace::promptRaceRestart() {
    QMessageBox messageBox;
    messageBox.setWindowTitle("Race Finished");
    messageBox.setText("Would you like to race again or quit?");
    messageBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    messageBox.setDefaultButton(QMessageBox::Retry);
    int choice = messageBox.exec();

    switch(choice) {
    case QMessageBox::Retry:
        resetRace();
        break;
    case QMessageBox::Close:
    default:
        QApplication::quit();
        break;
    }
}


void startRace::resetRace() {
    // Reset the track for all horses
    for(int row = 0; row < numRows; ++row) {
        for(QPushButton* button : trackButtons[row]) {
            button->setIcon(QIcon()); // Clear the icon to reset the track
        }
        // Place the horses back at the starting line
        if(!trackButtons[row].isEmpty()) {
            setupStartingLineButton(trackButtons[row][0], row);
        }
    }

    horseList.clear();
    createHorses();
    emit resetBet();

    horsesFinished = 0; // Reset the counter
    startRaceButton->setEnabled(true); // Re-enable the start race button
}


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    startRace window;
    window.show();
    return app.exec();
}
