#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include <QPair>
#include <QGridLayout>
#include <QLineEdit>
#include <QListWidget>

#include "bet.h"

class GameWindow : public QWidget {
    Q_OBJECT
public:
    GameWindow(QWidget *parent = nullptr);

private slots:
    void onContinueClicked();
    void onHorseSelected();
    void onBetEntered();
    void updateMoneyPool(double newAmount);

public slots:
    void checkBetResult(int winningHorseIndex, int odds);
    void resetWindow();
    void displayBettingHistory();

signals:
    void betPlaced();

private:
    QLabel *welcomeLabel;
    QPushButton *continueButton;
    QPushButton *horseButtons[5];
    QString horseSelected; // Variable to store the selected horse
    QLineEdit *betInput; // Variable to store the bet input field
    int betAmount; // Variable to store the bet amount
    int horseIndex;

    //bet object
    Bet *bet;
    QLabel *moneyPoolLabel;

    //betting history
    QListWidget *bettingHistoryWidget;
};


#endif // GAMEWINDOW_H
