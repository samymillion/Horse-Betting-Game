#include "bet.h"

Bet::Bet(double initialMoneyPool, QObject *parent) : QObject(parent), m_betAmount(0.0), m_moneyPool(initialMoneyPool)
{

}

void Bet::setBetAmount(double amount)
{
    m_betAmount = amount;
}

void Bet::setMoneyPool(double amount)
{
    m_moneyPool = amount;
}

double Bet::getBetAmount() const
{
    return m_betAmount;
}

double Bet::getMoneyPool() const
{
    return m_moneyPool;
}

bool Bet::placeBet()
{
    if (m_betAmount > m_moneyPool) {
        // Bet exceeds money pool
        return false;
    } else {
        // Deduct bet amount from money pool
        m_moneyPool -= m_betAmount;
        emit moneyPoolChanged(m_moneyPool);
        return true;
    }
}
