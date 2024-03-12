#ifndef BET_H
#define BET_H

#include <QObject>

class Bet : public QObject
{
    Q_OBJECT
public:
    explicit Bet(double initialMoneyPool, QObject *parent = nullptr);
    void setBetAmount(double amount);
    void setMoneyPool(double amount);
    double getBetAmount() const;
    double getMoneyPool() const;
    bool placeBet();
    double calculatePayout(double amount);
signals:
    void moneyPoolChanged(double newAmount);
public slots:

private:
    double m_betAmount;
    double m_moneyPool;
};

#endif // BET_H
