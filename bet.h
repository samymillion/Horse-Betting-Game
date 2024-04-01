//!  A bet class that contains a bet object to store information on bet amount, money pool, and calculates payout. 

#ifndef BET_H
#define BET_H

#include <QObject>

class Bet : public QObject
{
    Q_OBJECT
public:

    struct BetInfo {
        double amount;
        int horseIndex;
        double payout;
    };

    //! A constructor.
    /*!
      A more elaborate description of the constructor.
    */
    explicit Bet(double initialMoneyPool, QObject *parent = nullptr);
    
    //! A setter function for bet amount that takes 1 argument and sets the attribute m_betAmount.
    /*!
      \param amount an double argument that represents the amount bet by the user.
    */
    void setBetAmount(double amount);

    //! A setter function for money pool that takes 1 argument and sets the attribute m_moneyPool.
    /*!
      \param amount an double argument that represents the current money pool of the user.
    */
    void setMoneyPool(double amount);

    //! A getter function for bet amount that returns the attribute m_betAmount.
    /*!
      \return the amount bet by the user.
    */
    double getBetAmount() const;

    //! A getter function for bet amount that returns the attribute m_moneyPool.
    /*!
      \return the user's current money pool.
    */
    double getMoneyPool() const;

    //! A function that returns true and deducts the user's bet amount from money pool. If the bet is greater than the money pool, return false.
    /*!
      \return true if the bet is within the limits of the money pool, false otherwise.
    */
    bool placeBet();

    //! A function that takes the bet amount set by the user and returns two times the initial bet to represent the payout (payout is 200% of bet amount).
    /*!
      \param amount the bet amount that the user set this round.
      \return double the initial bet amount, which represents the payout.
    */
    double calculatePayout(int amount, int odds, int horseIndex, bool isWin);

    const std::vector<BetInfo>& getBettingHistory() const;

signals:
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
