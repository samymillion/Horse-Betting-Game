/*!
 * \file bet.cpp
 * \author Kevin, Zeba, Sam, Anna, Rohith
 * \date 2024-04-01
 * \brief Implementation file for the bet class.
 *
 *   This class manages the bet in a betting game, this icnludes the bet amount, the money pool,  payouts, 
 *   and it also has an array that maintains the bet history
 */
#include "bet.h"
#include <iostream>
#include <cmath>
// using namespace std;

//! \brief Constructor for the Bet class.
/*!
    THis consturctor initalized a Bet object with a initial money pool.
    \param initialMoneyPool A double representing the initial amount of money in the pool.
    \param parent The parent QObject (optional).
*/
Bet::Bet(double initialMoneyPool, QObject *parent) : QObject(parent), m_betAmount(0.0), m_moneyPool(initialMoneyPool)
{

}

//! \brief A setter function for bet amount that takes 1 argument and sets the attribute m_betAmount.
/*!
    \param amount an double argument that represents the amount bet by the user.
*/
void Bet::setBetAmount(double amount)
{
    m_betAmount = amount;
}

//! \brief A setter function for money pool that takes 1 argument and sets the attribute m_moneyPool.
/*!
    \param amount an double argument that represents the current money pool of the user.
*/
void Bet::setMoneyPool(double amount)
{
    m_moneyPool = amount;
}

//! \brief A getter function for bet amount that returns the attribute m_betAmount.
/*!
    \return the amount bet by the user.
*/
double Bet::getBetAmount() const
{
    return m_betAmount;
}

//! \brief A getter function for bet amount that returns the attribute m_moneyPool.
/*!
    \return the user's current money pool.
*/
double Bet::getMoneyPool() const
{
    return m_moneyPool;
}

//! \brief Attempts to place a bet with the current bet amount
/*!
    Deducts the bet amount from the money pool if the bet is within the pool's limits
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

//! \brief Calculates the payout based on the bet amount, odds, horse index, and win status.
/*!
    \param amount The bet amount.
    \param odds The odds for the bet.
    \param horseIndex The index of the horse 
    \param isWin A boolean indicating whether the bet was a winning bet.
    \return The calculated payout based on the bet amount and odds.
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

//! \brief Gets the betting history (all previous bets)
/*!
    \return A const reference to a vector of  objects representing the betting history
*/
const std::vector<Bet::BetInfo>& Bet::getBettingHistory() const {
    return m_bettingHistory;
}
