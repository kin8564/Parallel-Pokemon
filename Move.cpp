#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <array>
#include "types.h"  // Ensure correct case for file inclusion

class Move {
private:
    const std::string name;
    const Types* type; // Pointer to a Types object
    const int category;
    int power, accuracy, pp;
    std::array<int, 8> statEffect; // {buff/debuff, atk, def, spa, spd, spe, acc, eva}

protected:
    Move(const std::string& name, const Types* type, int cat, int pw, int acc, int points, const std::array<int, 8>& statArray)
        : name(name), type(type), category(cat), power(pw), accuracy(acc), pp(points), statEffect(statArray) {}

public:
    std::string getName() const {
        return name;
    }

    const Types* getType() const { // Return a pointer
        return type;
    }

    int getCat() const {
        return category;
    }

    int getPow() const {
        return power;
    }

    int getAcc() const {
        return accuracy;
    }

    int getPP() const {
        return pp;
    }

    std::array<int, 8> getEff() const {
        return statEffect;
    }
};

#endif // MOVE_H
