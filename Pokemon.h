#ifndef POKEMON_H
#define POKEMON_H
#include "Types.h"  // Include Types class
#include "Move.h"   // Include Move class

#include <string>
#include <array>


/**
 * Parent class for all Pokemon
 */
class Pokemon {
private:
    std::string name;

    // Base stats that do not change during battle
    int healthPoints, attack, defense, specialAttack, specialDefense, speed, accuracy, evasion;

    Types* type1;
    Types* type2;

    // Move set (4 moves per Pokemon)
    std::array<Move*, 4> moves;

    // Stat changes during battle
    std::array<int, 2> statAtk, statDef, statSpa, statSpd, statSpe;
    std::array<double, 2> statAcc, statEva;

protected:
    Pokemon(std::string monster, int hp, int atk, int def, int spa, int spd, int spe, Types* typeA, Types* typeB);

public:
    // Getters
    std::string getName() const;
    int getHP() const;
    int getAtk() const;
    int getAtkStage() const;
    int getDef() const;
    int getDefStage() const;
    int getSpa() const;
    int getSpaStage() const;
    int getSpd() const;
    int getSpdStage() const;
    int getSpe() const;
    int getSpeStage() const;

    // Setters
    void setHP(int x);
    void setAtk(int x);
    void setAtkStage(int x);
    void setDef(int x);
    void setDefStage(int x);
    void setSpa(int x);
    void setSpaStage(int x);
    void setSpd(int x);
    void setSpdStage(int x);
    void setSpe(int x);
    void setSpeStage(int x);
};

#endif // POKEMON_H
