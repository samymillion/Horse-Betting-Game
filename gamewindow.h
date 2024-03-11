#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include <QPair>
#include <QGridLayout>
#include <QLineEdit>

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

private:
    QLabel *welcomeLabel;
    QPushButton *continueButton;
    QPushButton *horseButtons[5];
    QString horseSelected; // Variable to store the selected horse
    QLineEdit *betInput; // Variable to store the bet input field
    int betAmount; // Variable to store the bet amount

    //bet object
    Bet *bet;
    QLabel *moneyPoolLabel;
    
};


#endif // GAMEWINDOW_H
