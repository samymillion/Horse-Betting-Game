#include <QApplication>
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
#include "startRace.h"
#include "GameWindow.h"

startRace::startRace(QWidget *parent) : QWidget(parent), horsesFinished(0) {
    srand(static_cast<unsigned>(time(NULL))); //seed
    this->setupUI();
}

void startRace::setupUI() {
        setWindowTitle("PIXEL DERBY 2024");
        setStyleSheet("background-color: #171a17;");
        showFullScreen();

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        QHBoxLayout* buttonBoxLayout = createButtonBar();
        mainLayout->addLayout(buttonBoxLayout);

        QGridLayout* gridLayout = new QGridLayout;
        QPushButton* button;

        // PLAYER STATS BUTTON
        button = new QPushButton("PLAYER STATS");
        button->setFixedSize(470, 50);
        button->setStyleSheet("font-family: Trebuchet MS; background-color: #292b29; background-position: center; font-size: 25px; color: white; border: 1px solid black;");
        gridLayout->addWidget(button, 0, 0);

        // HORSE ROSTER BUTTON
        button = new QPushButton("HORSE ROSTER");
        button->setFixedSize(470, 50);
        button->setStyleSheet("font-family: Trebuchet MS; background-color: #292b29; background-position: center; font-size: 25px; color: white; border: 1px solid black;");
        gridLayout->addWidget(button, 0, 1);

        // BETTING INTERFACE
        // Assuming GameWindow is properly defined elsewhere and handles betting logic
        GameWindow* gameWindow = new GameWindow();
        connect(this, &startRace::raceFinished, gameWindow, &GameWindow::checkBetResult);
        gridLayout->addWidget(gameWindow, 0, 2);

        createRaceTrack(mainLayout);
        mainLayout->addLayout(gridLayout);

        // Set main layout alignment and size
        mainLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
        setMinimumSize(960, 540);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &startRace::advanceHorses);
    }

QHBoxLayout* startRace::createButtonBar() {
        QHBoxLayout* layout = new QHBoxLayout;
        QPushButton* button;

        // Bet Display Button
        button = createButton("$42000", 200, 50, "font-family: Trebuchet MS Bold; background-color: #0f111a; background-position: center; font-size: 30px; color: white; border: 3px solid #282e42; border-radius: 5px;");
        layout->addWidget(button);

        // Start Race Button
        startRaceButton = createButton("S T A R T   R A C E", 600, 50, "font: bold; background-image: url(:/icons/gradient.png); background-position: center; font-size: 30px; color: white; border: 3px solid white; border-radius: 15px;");
        layout->addWidget(startRaceButton);
        connect(startRaceButton, &QPushButton::clicked, this, [=]() {
            timer->start(500);
            startRaceButton->setEnabled(false);
        });

        // Version Display Button
        button = createButton("PIXELDERBY v1.0", 300, 50, "font-family: Verdana; background-image: url(:/icons/gold.png); background-position: center; font-size: 25px; color: black; border: 1px solid black; border-radius: 5px;");
        layout->addWidget(button);

        return layout;
    }

QPushButton* startRace::createButton(const QString& text, int width, int height, const QString& style) {
        QPushButton* button = new QPushButton(text);
        button->setFixedSize(width, height);
        button->setStyleSheet(style);
        return button;
    }

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

void startRace::setupStartingLineButton(QPushButton* button, int row) {
        const QString iconPaths[5] = {":/icons/brown.png", ":/icons/blue.png", ":/icons/green.png", ":/icons/red.png", ":/icons/yellow.png"};
        button->setIcon(QIcon(iconPaths[row % 5]));
        button->setIconSize(QSize(50, 50));
        button->setStyleSheet("background-color: red;");
    }

void startRace::advanceHorses() {
        for (int row = 0; row < numRows; ++row) {
            // Randomly decide if the horse moves this tick
            if (rand() % 2 == 0) { // 50% chance to move
                for (int col = numCols - 1; col > 0; --col) {
                    if (!trackButtons[row][col - 1]->icon().isNull()) {
                        // Advance horse
                        trackButtons[row][col]->setIcon(trackButtons[row][col-1]->icon());
                        trackButtons[row][col]->setIconSize(QSize(50, 50));
                        trackButtons[row][col-1]->setIcon(QIcon());
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
                    timer->stop(); // Stop the race
                    QMessageBox messageBox;
                    messageBox.setText(QString("Horse %1 wins! \n"
                                               "Horse %2 was the runner up. \n"
                                               "Horse %3 finished in third place. \n"
                                               "Horse %4 finished in fourth place. \n"
                                               "Horse %5 had a bad day!")
                                           .arg(results[0]+1)
                                           .arg(results[1]+1)
                                           .arg(results[2]+1)
                                           .arg(results[3]+1)
                                           .arg(results[4]+1));
                    messageBox.exec();
                    emit raceFinished(results[0]);
                    break;
                }
            }
        }
    }

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

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    startRace window;
    window.show();
    return app.exec();
}
