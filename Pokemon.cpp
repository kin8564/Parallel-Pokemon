#include <string>
#include <array>
#include "pokemon.h"
#include "Types.h"
#include "Move.h"

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
        Pokemon(std::string monster, int hp, int atk, int def, int spa, int spd, int spe, Types* typeA, Types* typeB)
            : name(monster), healthPoints(hp), attack(atk), defense(def), specialAttack(spa), specialDefense(spd), speed(spe),
            type1(typeA), type2(typeB), accuracy(0), evasion(0),
            statAtk{0, attack}, statDef{0, defense}, statSpa{0, specialAttack}, statSpd{0, specialDefense}, statSpe{0, speed},
            statAcc{0, 1.0}, statEva{0, 1.0} {
            moves.fill(nullptr);
        }

    public:
        std::string getName() {
            return name;
        }

        int getHP() {
            return healthPoints;
        }

        void setHP(int x) {
            healthPoints = x;
        }

        int getAtk() {
            return statAtk[1];
        }

        int getAtkStage() {
            return statAtk[0];
        }

        void setAtk(int x) {
            statAtk[1] = x;
        }

        void setAtkStage(int x) {
            statAtk[0] += x;
            if (statAtk[0] > 6) {
                statAtk[0] = 6;
            } else if (statAtk[0] < -6) {
                statAtk[0] = -6;
            }
        }

        int getDef() {
            return statDef[1];
        }

        int getDefStage() {
            return statDef[0];
        }

        void setDef(int x) {
            statDef[1] = x;
        }

        void setDefStage(int x) {
            statDef[0] += x;
            if (statDef[0] > 6) {
                statDef[0] = 6;
            } else if (statDef[0] < -6) {
                statDef[0] = -6;
            }
        }

        int getSpa() {
            return statSpa[1];
        }

        int getSpaStage() {
            return statSpa[0];
        }

        void setSpa(int x) {
            statSpa[1] = x;
        }

        void setSpaStage(int x) {
            statSpa[0] += x;
            if (statSpa[0] > 6) {
                statSpa[0] = 6;
            } else if (statSpa[0] < -6) {
                statSpa[0] = -6;
            }
        }

        int getSpd() {
            return statSpd[1];
        }

        int getSpdStage() {
            return statSpd[0];
        }

        void setSpd(int x) {
            statSpd[1] = x;
        }

        void setSpdStage(int x) {
            statSpd[0] += x;
            if (statSpd[0] > 6) {
                statSpd[0] = 6;
            } else if (statSpd[0] < -6) {
                statSpd[0] = -6;
            }
        }

        int getSpe() {
            return statSpe[1];
        }

        int getSpeStage() {
            return statSpe[0];
        }

        void setSpe(int x) {
            statSpe[1] = x;
        }

        void setSpeStage(int x) {
            statSpe[0] += x;
            if (statSpe[0] > 6) {
                statSpe[0] = 6;
            } else if (statSpe[0] < -6) {
                statSpe[0] = -6;
            }
        }
};