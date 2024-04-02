#include "Horse.h"


#include <cstdlib>
#include <ctime>

// Constructor
Horse::Horse(const std::string& horseName) : name(horseName), moneyLine(0) {
    speedFactor = rand() % 10 + 1; // Random speed factor between 1 and 10
}

// Getter methods
std::string Horse::getName() const { return name; }
int Horse::getSpeedFactor() const { return speedFactor; }
int Horse::getMoneyLine() const { return moneyLine; }

//Setter methods
void Horse::setSeed() const{
    srand(time(nullptr)); // Seed for random number generation
}

void Horse::setMoneyLine(int odds){
    this->moneyLine = odds;
}
