#include "gamewindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QSpacerItem>
#include <QDebug>
#include <QPixmap>
#include <QMessageBox>
#include <QLineEdit>


GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Game Window");
    setFixedSize(470, 400);
    setStyleSheet("background-color: white;");
    const QString iconPaths[5] = {":/icons/brown.png", ":/icons/blue.png", ":/icons/green.png", ":/icons/red.png", ":/icons/yellow.png"};


    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    welcomeLabel = new QLabel("Welcome to the Horse Betting Game!", this);
    welcomeLabel->setFont(QFont("Arial", 20, QFont::Bold));
    welcomeLabel->setStyleSheet("color: black;");
    layout->addWidget(welcomeLabel);

    continueButton = new QPushButton("Continue", this);
    continueButton->setFixedSize(100, 50);
    layout->addWidget(continueButton);

    // Connect the clicked signal of the button to a slot
    connect(continueButton, &QPushButton::clicked, this, &GameWindow::onContinueClicked);

    //set up initial money pool 
    double initialMoneyPool = 100.0; // Initial money pool amount
    bet = new Bet(initialMoneyPool, this);
    connect(bet, &Bet::moneyPoolChanged, this, &GameWindow::updateMoneyPool); //emitted by placeBet() function in bet.cpp
    moneyPoolLabel = new QLabel("Money Pool: " + QString::number(bet->getMoneyPool()), this);
    moneyPoolLabel->setFont(QFont("Arial", 20, QFont::Bold));
    moneyPoolLabel->setStyleSheet("color: black;");
    layout->addWidget(moneyPoolLabel);

    for (int i = 0; i < 5; ++i) {
        horseButtons[i] = new QPushButton("Horse " + QString::number(i + 1), this);
        horseButtons[i]->setFixedSize(100, 50);
        horseButtons[i]->setVisible(false); // Initially hide the buttons

        horseButtons[i]->setIcon(QIcon(iconPaths[i]));
        layout->addWidget(horseButtons[i]);

        // Connect the clicked signal of each horse button to a slot
        connect(horseButtons[i], &QPushButton::clicked, this, &GameWindow::onHorseSelected);
    }
}


void GameWindow::onContinueClicked() {
    // Change the text of the welcome label
    welcomeLabel->setText("Pick a horse");
    continueButton->hide();

    for (int i = 0; i < 5; ++i) {
        horseButtons[i]->setVisible(true);
    }
}

void GameWindow::onHorseSelected() {
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        for (int i = 0; i < 5; ++i) {
            if (horseButtons[i] == senderButton) {
                horseIndex = i;
                break;
            }
        }
        horseSelected = senderButton->text();
        //horseSelected = senderButton->icon().pixmap().fileName();
        //qDebug() << "Selected horse:" << horseSelected;

        welcomeLabel->setText("Pick a bet amount");
        for (int i = 0; i < 5; ++i) {
            horseButtons[i]->hide();
        }
        // Show the bet input field
        betInput = new QLineEdit(this);
        betInput->setPlaceholderText("Enter bet amount from $1 to $" + QString::number(bet->getMoneyPool()));
        layout()->addWidget(betInput);
        // Connect the returnPressed signal of the bet input field to a slot
        connect(betInput, &QLineEdit::returnPressed, this, &GameWindow::onBetEntered);

    }
}

void GameWindow::onBetEntered() {
    QString betAmountStr = betInput->text();
    bool ok;
    int betAmount = betAmountStr.toInt(&ok);

    //setting bets now calls placeBet function in bet.cpp, changing bet object values
    bet->setBetAmount(betAmount);
    if (bet->placeBet()) {
        // Bet successfully placed
        moneyPoolLabel->setText("Money Pool: " + QString::number(bet->getMoneyPool()));
        QMessageBox::information(this, "Success", "Bet placed successfully!");
    } else {
        // Bet exceeds money pool
        QMessageBox::warning(this, "Error", "Bet amount exceeds money pool!");
        betInput->clear();
    }

    // if (ok && betAmount >= 1 && betAmount <= 10000) {
    //     // Bet amount is within the valid range
    //     //qDebug() << "Bet amount:" << betAmount; // just printing bet amount for now but can save it to something
    //     // Perform actions with the bet amount here
    // } else {
    //     // Bet amount is invalid
    //     //qDebug() << "Invalid bet amount:" << betAmountStr;
    //     // Show error message
    //     QMessageBox::critical(this, "Invalid Bet Amount", "Please enter a valid bet amount from $1 to $10,000.");
    //     // Clear the bet input field
    //     betInput->clear();
    // }
}

void GameWindow::updateMoneyPool(double newAmount)
{
    // updates text 
    moneyPoolLabel->setText("Money Pool: " + QString::number(newAmount));
}

void GameWindow::checkBetResult(int winningHorse) {
    if (horseIndex == winningHorse) {
        double payout = bet->calculatePayout(betAmount);
        double moneyPool = bet->getMoneyPool();
        double newPool = payout + moneyPool;
        updateMoneyPool(newPool);
        QMessageBox::information(this, "Race Result", "Congratulations! Your horse won!");
    }
    else{
        QMessageBox::information(this, "Race Result", "Sorry! Your horse didn't win this time.");
    }
}



