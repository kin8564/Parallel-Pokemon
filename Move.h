#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <array>
#include "Types.h"  // Include Types enum class

class Move {
private:
    const std::string name;
    const Types type;
    const int category;
    int power, accuracy, pp;
    std::array<int, 8> statEffect; // {buff/debuff, atk, def, spa, spd, spe, acc, eva}

protected:
    Move(const std::string& name, Types type, int cat, int pw, int acc, int points, const std::array<int, 8>& statArray);

public:
    std::string getName() const;
    Types getType() const;
    int getCat() const;
    int getPow() const;
    int getAcc() const;
    int getPP() const;
    std::array<int, 8> getEff() const;
};

#endif // MOVE_H
