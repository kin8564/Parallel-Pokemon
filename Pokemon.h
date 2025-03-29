#ifndef POKEMON_H
#define POKEMON_H
#include "Types.h"
#include "Move.h"

#include <string>
#include <array>


/**
 * Parent class for all Pokemon
 */
class Pokemon {
private:
    std::string name;

    int healthPoints, attack, defense, specialAttack, specialDefense, speed, accuracy, evasion;

    Types* type1;
    Types* type2;

    std::array<Move*, 4> moves;

    std::array<int, 2> statAtk, statDef, statSpa, statSpd, statSpe;

    std::array<double, 2> statAcc, statEva;

protected:
    Pokemon(std::string monster, int hp, int atk, int def, int spa, int spd, int spe, Types* typeA, Types* typeB);

public:
    std::string getName();
    int getHP();
    int getAtk();
    int getAtkStage();
    int getDef();
    int getDefStage();
    int getSpa();
    int getSpaStage();
    int getSpd();
    int getSpdStage();
    int getSpe();
    int getSpeStage();

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

#endif