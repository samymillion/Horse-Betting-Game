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

//! Game window 
/*!
 * gamewindow.cpp is our file used for game window and game window mechanisms including: picking a horse, entering bet, and money pool updating. Primarily, features that were meant to be implemented sequentially are included in this file.
 */

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

  	//! Continue into game
    continueButton = new QPushButton("Continue", this);
    continueButton->setFixedSize(100, 50);
    layout->addWidget(continueButton);

    connect(continueButton, &QPushButton::clicked, this, &GameWindow::onContinueClicked);

    //! Set up initial money pool 
    double initialMoneyPool = 100.0; // Initial money pool amount
    bet = new Bet(initialMoneyPool, this);
    connect(bet, &Bet::moneyPoolChanged, this, &GameWindow::updateMoneyPool); //emitted by placeBet() function in bet.cpp
    moneyPoolLabel = new QLabel("Money Pool: " + QString::number(bet->getMoneyPool()), this);
    moneyPoolLabel->setFont(QFont("Arial", 20, QFont::Bold));
    moneyPoolLabel->setStyleSheet("color: black;");
    layout->addWidget(moneyPoolLabel);

    //! Set icons for horses
    for (int i = 0; i < 5; ++i) {
        horseButtons[i] = new QPushButton("Horse " + QString::number(i + 1), this);
        horseButtons[i]->setFixedSize(100, 50);
        horseButtons[i]->setVisible(false); 

        horseButtons[i]->setIcon(QIcon(iconPaths[i]));
        layout->addWidget(horseButtons[i]);

        
        connect(horseButtons[i], &QPushButton::clicked, this, &GameWindow::onHorseSelected);
    }
}


void GameWindow::onContinueClicked() {
    //! User to pick a horse
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
       

        welcomeLabel->setText("Pick a bet amount");
        for (int i = 0; i < 5; ++i) {
            horseButtons[i]->hide();
        }
        //! Show the bet input field
        betInput = new QLineEdit(this);
        betInput->setPlaceholderText("Enter bet amount from $1 to $" + QString::number(bet->getMoneyPool()));
        layout()->addWidget(betInput);
        
        connect(betInput, &QLineEdit::returnPressed, this, &GameWindow::onBetEntered);

    }
}

void GameWindow::onBetEntered() {
    QString betAmountStr = betInput->text();
    bool ok;
    int betAmount = betAmountStr.toInt(&ok);

    //! Setting bets calls placeBet function in bet.cpp, changing bet object values
    bet->setBetAmount(betAmount);
    if (bet->placeBet()) {
        //! Bet successfully placed
        moneyPoolLabel->setText("Money Pool: " + QString::number(bet->getMoneyPool()));
        QMessageBox::information(this, "Success", "Bet placed successfully!");
    } else {
        //! Bet exceeds money pool
        QMessageBox::warning(this, "Error", "Bet amount exceeds money pool!");
        betInput->clear();
    }

}

void GameWindow::updateMoneyPool(double newAmount)
{
    //! Updates money pool with new amount 
    moneyPoolLabel->setText("Money Pool: " + QString::number(newAmount));
}

void GameWindow::checkBetResult(int winningHorse) {
    if (horseIndex == winningHorse) {
        // double payout = bet->calculatePayout(betAmount);
        double payout = bet->calculatePayout(bet->getBetAmount());
        double moneyPool = bet->getMoneyPool();
        double newPool = payout + moneyPool;
        updateMoneyPool(newPool);
        QMessageBox::information(this, "Race Result", "Congratulations! Your horse won!");
    }
    else{
        QMessageBox::information(this, "Race Result", "Sorry! Your horse didn't win this time.");
    }
}



