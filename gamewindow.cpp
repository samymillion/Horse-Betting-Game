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
#include <iostream>

//! Game window 
/*!
 * gamewindow.cpp is our file used for game window and game window mechanisms including: picking a horse, entering bet, and money pool updating. Primarily, features that were meant to be implemented sequentially are included in this file.
 */

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Game Window");
    setFixedSize(470, 400);
    setStyleSheet("background-color: white;");
    const QString iconPaths[5] = {":/icons/brown.png", ":/icons/blue.png", ":/icons/green.png", ":/icons/red.png", ":/icons/yellow.png"};
    const QString names[5] = {"Cocoa Comet", "Ocean Breeze", "Jade Jumper", "Ruby Rocket", "Lemon Lucky"};


    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    welcomeLabel = new QLabel("WELCOME TO PIXEL DERBY!!\nPRESS CONTINUE TO BET ON A HORSE", this);
    welcomeLabel->setFixedSize(470, 50);
    welcomeLabel->setAlignment(Qt::AlignHCenter);
    welcomeLabel->setStyleSheet("font-family: Trebuchet MS Bold; background-color: #292b29; background-position: center; font-size: 15px; color: white; border: 1px solid black;");
    layout->addWidget(welcomeLabel);

  	//! Continue into game
    continueButton = new QPushButton("CONTINUE", this);
    continueButton->setFixedSize(470, 50);
    continueButton->setStyleSheet("font-family: Trebuchet MS Bold; background-color: #e3e1da; background-position: center; color: black; border: 3px solid #282e42; border-radius: 5px;");
    layout->addWidget(continueButton);
    layout->setAlignment(continueButton, Qt::AlignTop | Qt::AlignHCenter);

    connect(continueButton, &QPushButton::clicked, this, &GameWindow::onContinueClicked);
    //! Set up initial money pool 
    double initialMoneyPool = 100.0; // Initial money pool amount
    bet = new Bet(initialMoneyPool, this);
    connect(bet, &Bet::moneyPoolChanged, this, &GameWindow::updateMoneyPool); //emitted by placeBet() function in bet.cpp

    moneyPoolLabel = new QLabel("MONEY POOL: $" + QString::number(bet->getMoneyPool()), this);
    moneyPoolLabel->setFixedSize(470, 50);
    moneyPoolLabel->setAlignment(Qt::AlignCenter);
    moneyPoolLabel->setStyleSheet("font-family: Trebuchet MS Bold; background-color: #0f111a; background-position: center; font-size: 25px; color: white; border: 3px solid #282e42; border-radius: 5px;");
    layout->addWidget(moneyPoolLabel);

    //! Set icons for horses
    for (int i = 0; i < 5; ++i) {
        horseButtons[i] = new QPushButton(names[i], this);
        horseButtons[i]->setFixedSize(470, 50);
        horseButtons[i]->setVisible(false); 

        horseButtons[i]->setIcon(QIcon(iconPaths[i]));
        layout->addWidget(horseButtons[i]);

        
        connect(horseButtons[i], &QPushButton::clicked, this, &GameWindow::onHorseSelected);
    }
}

//! A function allows the user to pick the horse that they would like to bet on too win
/*!
*/
void GameWindow::onContinueClicked() {

    std::cout << "Test passed (Continue Button Works)\n";
    //! User to pick a horse
    welcomeLabel->setText("\nPICK A HORSE");
    continueButton->hide();

    for (int i = 0; i < 5; ++i) {
        horseButtons[i]->setVisible(true);
    }
}

//! A function that allows the user to input in a text box the amount they would like to bet on a horse
/*!
*/
void GameWindow::onHorseSelected() {

    std::cout << "Test passed (Horse Selection Works)\n";

    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        for (int i = 0; i < 5; ++i) {
            if (horseButtons[i] == senderButton) {
                horseIndex = i;
                break;
            }
        }
        horseSelected = senderButton->text();


        welcomeLabel->setText("\nPICK A BET AMOUNT");
        for (int i = 0; i < 5; ++i) {
            horseButtons[i]->hide();
        }
        //! Show the bet input field
        betInput = new QLineEdit(this);
        betInput->setPlaceholderText("ENTER A BET AMOUNT FROM $1 TO $" + QString::number(bet->getMoneyPool()));
        layout()->addWidget(betInput);

        connect(betInput, &QLineEdit::returnPressed, this, &GameWindow::onBetEntered);

    }
}

//! A function that once the user has entered bet sets the bet amount and goes onto the next screen to confirm if it is placed succesfully or if there is an error
/*!
*/
void GameWindow::onBetEntered() {
    QString betAmountStr = betInput->text();
    bool ok;
    int betAmount = betAmountStr.toInt(&ok);

    //! Setting bets calls placeBet function in bet.cpp, changing bet object values
    bet->setBetAmount(betAmount);
    if (bet->placeBet()) {
        //! Bet successfully placed
        moneyPoolLabel->setText("MONEY POOL: $" + QString::number(bet->getMoneyPool()));
        moneyPoolLabel->setAlignment(Qt::AlignCenter);
        moneyPoolLabel->setStyleSheet("font-family: Trebuchet MS; background-color: #0f111a; background-position: center; font-size: 25px; color: white; border: 3px solid #282e42; border-radius: 5px;");
        QMessageBox::information(this, "Success", "Bet placed successfully!");

        // Disable further betting until next race
        for (QPushButton* button : horseButtons) {
            button->setEnabled(false);
        }
        if (betInput) {
            betInput->setEnabled(false);
            betInput->hide(); // Hide bet input to indicate betting is closed
        }
        welcomeLabel->setText("Waiting for next race...");
        emit betPlaced();
    } else {
        //! Bet exceeds money pool
        QMessageBox::warning(this, "Error", "Bet amount exceeds money pool!");
        betInput->clear();
    }
}

//! A function that updates the money paul based on the new maount
/*!
    \param newAmount the new amount for money pool
*/
void GameWindow::updateMoneyPool(double newAmount)
{
    //! Updates money pool with new amount 
    moneyPoolLabel->setText("MONEY POOL: " + QString::number(newAmount));
}

//! A function checks if the horse that the user bet on won the race 
/*!
    \param winningHorse id of the horse that wins
*/
void GameWindow::checkBetResult(int winningHorse, int odds) {
    if (horseIndex == winningHorse) {
        double payout = bet->calculatePayout(bet->getBetAmount(), odds, horseIndex, 1);
        double moneyPool = bet->getMoneyPool();
        double newPool = payout + moneyPool;
        updateMoneyPool(newPool);
        bet->setMoneyPool(newPool);
        QMessageBox::information(this, "Race Result", "Congratulations! Your horse won!");
    }
    else{
        double payout = bet->calculatePayout(bet->getBetAmount(), odds, horseIndex, 0);
        QMessageBox::information(this, "Race Result", "Sorry! Your horse didn't win this time.");
    }
}

void GameWindow::resetWindow() {
    // Reset the welcome label to prompt user to pick a horse
    welcomeLabel->setText("\nPICK A HORSE");
    
    welcomeLabel->show();
    

    continueButton->hide();

    // Re-enable and show horse selection buttons
    for (QPushButton* button : horseButtons) {
        button->setEnabled(true);
        button->setVisible(true);
    }

    //Hide the bet input if it exists and clear it for the next input
    if (betInput) {
        betInput->hide();
        betInput->clear();
    }

    //Reset the horseIndex
    horseIndex = -1;

    // Ensure the money pool label is updated to reflect current state
    moneyPoolLabel->setText("MONEY POOL: " + QString::number(bet->getMoneyPool()));
    moneyPoolLabel->show();
}

//NEW BETTING HISTORY
void GameWindow::displayBettingHistory() {
    QDialog *betHistoryDialog = new QDialog(this);
    betHistoryDialog->setWindowTitle("Bet History");
    QVBoxLayout *layout = new QVBoxLayout(betHistoryDialog);

    const auto& history = bet->getBettingHistory();

    const QString names[5] = {"Cocoa Comet", "Ocean Breeze", "Jade Jumper", "Ruby Rocket", "Lemon Lucky"};
 
    if (history.empty()) {
        layout->addWidget(new QLabel("No History of Races to Show"));
    } else {

        for (const auto& betInfo : history) {

            QString itemText = QString("Bet: $%1 on " + names[betInfo.horseIndex] + " Payout: $%2")
                .arg(betInfo.amount)
                .arg(betInfo.payout);
            layout->addWidget(new QLabel(itemText));
        }
    }

    betHistoryDialog->setLayout(layout);
    betHistoryDialog->exec(); 

}


