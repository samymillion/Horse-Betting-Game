//!  A bet class that contains a bet object to store information on bet amount, money pool, and calculates payout. 
#include "bet.h"
#include <iostream>
#include <cmath>
// using namespace std;

//! A constructor.
/*!
    A more elaborate description of the constructor.
*/
Bet::Bet(double initialMoneyPool, QObject *parent) : QObject(parent), m_betAmount(0.0), m_moneyPool(initialMoneyPool)
{

}

//! A setter function for bet amount that takes 1 argument and sets the attribute m_betAmount.
/*!
    \param amount an double argument that represents the amount bet by the user.
*/
void Bet::setBetAmount(double amount)
{
    m_betAmount = amount;
}

//! A setter function for money pool that takes 1 argument and sets the attribute m_moneyPool.
/*!
    \param amount an double argument that represents the current money pool of the user.
*/
void Bet::setMoneyPool(double amount)
{
    m_moneyPool = amount;
}

//! A getter function for bet amount that returns the attribute m_betAmount.
/*!
    \return the amount bet by the user.
*/
double Bet::getBetAmount() const
{
    return m_betAmount;
}

//! A getter function for bet amount that returns the attribute m_moneyPool.
/*!
    \return the user's current money pool.
*/
double Bet::getMoneyPool() const
{
    return m_moneyPool;
}

//! A function that returns true and deducts the user's bet amount from money pool. If the bet is greater than the money pool, return false.
/*!
    \return true if the bet is within the limits of the money pool, false otherwise.
*/
bool Bet::placeBet()
{
    if (m_betAmount > m_moneyPool) { // if bet exceeds money pool return false
        std::cout << "Test passed (user cannot set bet amount outside bounds of money pool)\n";
        return false;
    } else {
        m_moneyPool -= m_betAmount; // if bet is valid, deduct bet amount from money pool
        emit moneyPoolChanged(m_moneyPool); // emit signal that money pool changed
        std::cout << "Test passed (user submits bet for one horse before a race for an amount that is within the budget of their current money pool)\n";
        return true;
    }
}

//! A function that takes the bet amount set by the user and returns two times the initial bet to represent the payout (payout is 200% of bet amount).
/*!
    \param amount the bet amount that the user set this round.
    \return double the initial bet amount, which represents the payout.
*/
double Bet::calculatePayout(int amount, int odds, int horseIndex, bool isWin) {
    
    int payout = 0;

    if (isWin == true){

        if (odds > 0) {
            // For positive odds
            payout = round(amount + (amount * odds / 100.0));
        } else {
            // For negative odds (odds value is negative, so make it positive for calculation)
            payout = round(amount + (amount / (-odds / 100.0)));
        }
    }

    BetInfo newBet;
    newBet.amount = amount;
    newBet.horseIndex = horseIndex;
    newBet.payout = payout;
    m_bettingHistory.push_back(newBet);

    return payout;
}

//NEW BETTING HISTORY
const std::vector<Bet::BetInfo>& Bet::getBettingHistory() const {
    return m_bettingHistory;
}
