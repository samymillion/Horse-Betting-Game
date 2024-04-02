#ifndef HORSE_H
#define HORSE_H

#include <QString>
#include <string>

class Horse {
public:
    // Constructor
    Horse(const std::string& horseName);

    // Getter methods
    std::string getName() const;
    int getSpeedFactor() const;
    int getMoneyLine() const;
    void setSeed() const;
    void setMoneyLine(int odds);

private:
    std::string name; // Name of the horse
    int speedFactor; // Speed factor of the horse
    int moneyLine;   // money line betting odds of the horse for a given race
};

#endif // HORSE_H
