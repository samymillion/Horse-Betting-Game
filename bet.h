/*!
 * \file bet.h
 * \author Kevin, Zeba, Sam, Anna, Rohith
 * \date 2024-04-01
 * \brief Definition of the Bet class for managing bets in the game.
 *
 * This file contains the declaration of the Bet class, which is responsible for managing the bet
 * amount, the money pool, the payout and the bet history
 */
#ifndef BET_H
#define BET_H

#include <QObject>


/*!
 * \class Bet
 * \brief The Bet class manages bets in the game.
 *
 * This class handles the bet amount, the money pool, and calculates the payout for the bets. It
 * also maintains a history of all bets made.
 */
class Bet : public QObject
{
    Q_OBJECT
public:

    //! Structure to store information about a bet.
    struct BetInfo {
        double amount;
        int horseIndex;
        double payout;
    };



    //! \brief Initializes a Bet object with a specified initial money pool
    /*!
      \param initialMoneyPool The initial amount of money in the pool.
      \param parent The parent QObject
      Constructor for the Bet class
    */
    explicit Bet(double initialMoneyPool, QObject *parent = nullptr);
    
    //! \brief Sets the attribute m_betAmount to the specified amount.
    /*!
      A setter function for bet amount that takes 1 argument and sets the attribute m_betAmount.
      \param amount an double argument that represents the amount bet by the user.
    */
    void setBetAmount(double amount);

    //!  \brief Sets the attribute m_moneyPool to the specified amount.
    /*!
      A setter function for money pool that takes 1 argument and sets the attribute m_moneyPool.
      \param amount an double argument that represents the current money pool of the user.
    */
    void setMoneyPool(double amount);

    //! \brief Returns the attribute m_betAmount.
    /*!
      A getter function for bet amount that returns the attribute m_betAmount.
      \return the amount bet by the user.
    */
    double getBetAmount() const;

    //! \brief Returns the attribute m_moneyPool.
    /*!
      A getter function for bet amount that returns the attribute m_moneyPool.
      \return the user's current money pool.
    */
    double getMoneyPool() const;

    //! \brief Deducts the bet amount from the money pool if the bet is valid.
    /*!
      A function that returns true and deducts the user's bet amount from money pool. If the bet is greater than the money pool, return false.
      \return true if the bet is within the limits of the money pool, false otherwise.
    */
    bool placeBet();

    //!  \brief Calculates the payout for the bet.
    /*!
    A function that takes the bet amount set by the user and returns two times the initial bet to represent the payout (payout is 200% of bet amount).
      \param amount the bet amount that the user set this round.
      \param odds The odds for the bet.
      \param horseIndex The index of the horse the bet is placed on.
      \param isWin A boolean indicating whether the bet was a winning bet.
      \return double the initial bet amount, which represents the payout.
    */
    double calculatePayout(int amount, int odds, int horseIndex, bool isWin);

    //! \brief Returns the betting history. 
    /*!
      Gets the betting history.
      \return A const reference to a vector of BetInfo objects representing the betting history.
    */
    const std::vector<BetInfo>& getBettingHistory() const;

signals:
    //! when the money pool changes.
    /*!
      \param newAmount The new amount of the money pool.
    */
    void moneyPoolChanged(double newAmount);
public slots:

private:
    //! private variable that stores current bet amount
    double m_betAmount;

    //! private variable that stores the current money pool
    double m_moneyPool;

    std::vector<BetInfo> m_bettingHistory;
};

#endif // BET_H
