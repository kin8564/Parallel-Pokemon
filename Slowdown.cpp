#include <iostream>
#include <unordered_map>
#include <random>
#include <string>
#include "Move.h"
#include "Types.h"
#include "Pokemon.h"
#include "PokeDex.h"
#include "AttackDex.h"
#include "Slowdown.h"
#include <vector>
#include <random>
#include <thread>
#include <chrono>

class Slowdown{
    public:
        static std::unordered_map<int, double> statMultiplier;
        static std::unordered_map<int, double> accMultiplier;
        static std::unordered_map<int, double> evaMultiplier;

        static void multiPopulate() {
            statMultiplier = {
                {-6, 2.0/8.0}, {-5, 2.0/7.0}, {-4, 2.0/6.0},
                {-3, 2.0/5.0}, {-2, 2.0/4.0}, {-1, 2.0/3.0},
                {0,  2.0/2.0}, {1,  3.0/2.0}, {2,  4.0/2.0},
                {3,  5.0/2.0}, {4,  6.0/2.0}, {5,  7.0/2.0},
                {6,  8.0/2.0}
            };

            accMultiplier = {
                {-6, 3.0/9.0}, {-5, 3.0/8.0}, {-4, 3.0/7.0},
                {-3, 3.0/6.0}, {-2, 3.0/5.0}, {-1, 3.0/4.0},
                {0,  3.0/3.0}, {1,  4.0/3.0}, {2,  5.0/3.0},
                {3,  6.0/3.0}, {4,  7.0/3.0}, {5,  8.0/3.0},
                {6,  9.0/3.0}
            };

            evaMultiplier = {
                {6,  3.0/9.0}, {5,  3.0/8.0}, {4,  3.0/7.0},
                {3,  3.0/6.0}, {2,  3.0/5.0}, {1,  3.0/4.0},
                {0,  3.0/3.0}, {-1, 4.0/3.0}, {-2, 5.0/3.0},
                {-3, 6.0/3.0}, {-4, 7.0/3.0}, {-5, 8.0/3.0},
                {-6, 9.0/3.0}
            };
        }

        static std::vector<int> typeMultiplier(int damage, Move* move, Pokemon* defender){
            double modifier = 1.0;
            int superEff = 0;
            int notVeryEff = 0;
            int noEff = 0;

            std::vector<int> dmgArray(4, 0);

            // Check if defender has a primary type
            if (defender->getTypeA() != Types::NONE) { // Adjust as necessary to handle null or no type
                switch (defender->getTypeA()) {
                    case Types::BUG:
                        // Weak: Flying, Rock, Fire
                        if (move->getType() == Types::FLYING || move->getType() == Types::ROCK || move->getType() == Types::FIRE) {
                            modifier *= 2;
                        }
                        // Resist: Fighting, Ground, Grass
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::GROUND || move->getType() == Types::GRASS) {
                            modifier /= 2;
                        }
                        break;

                    case Types::DARK:
                        //Weak: BUG, FAIRY, FIGHTING
                        if (move->getType() == Types::BUG || move->getType() == Types::FAIRY || move->getType() == Types::FIGHTING) {
                            modifier = modifier * 2;
                        }
                        //Resist: GHOST, DARK
                        if (move->getType() == Types::GHOST || move->getType() == Types::DARK) {
                            modifier = modifier / 2;
                        }
                        //Immune: Psychic
                        if (move->getType() == Types::PSYCHIC) {
                            modifier = 0;
                        }
                        break;

                    case Types::DRAGON:
                        //Weak: DRAGON, FAIRY, ICE
                        if (move->getType() == Types::DRAGON || move->getType() == Types::FAIRY || move->getType() == Types::ICE) {
                            modifier = modifier * 2;
                        }
                        //Resist: FIRE, WATER, GRASS, ELECTRIC
                        if (move->getType() == Types::FIRE || move->getType() == Types::WATER || move->getType() == Types::GRASS || move->getType() == Types::ELECTRIC) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::ELECTRIC:
                        //Weak: GROUND
                        if (move->getType() == Types::GROUND) {
                            modifier = modifier * 2;
                        }
                        //Resist: FLYING, ELECTRIC, STEEL
                        if (move->getType() == Types::FLYING || move->getType() == Types::ELECTRIC || move->getType() == Types::STEEL) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::FAIRY:
                        //Weak: POISON, STEEL
                        if (move->getType() == Types::POISON || move->getType() == Types::STEEL) {
                            modifier = modifier * 2;
                        }
                        //Resist: BUG, DARK, FIGHTING
                        if (move->getType() == Types::BUG || move->getType() == Types::DARK || move->getType() == Types::FIGHTING) {
                            modifier = modifier / 2;
                        }
                        //Immune: DRAGON
                        if (move->getType() == Types::DRAGON) {
                            modifier = 0;
                        }
                        break;

                        case Types::FIGHTING:
                        //Weak: FAIRY, FLYING, PSYCHIC
                        if (move->getType() == Types::FAIRY || move->getType() == Types::FLYING || move->getType() == Types::PSYCHIC) {
                            modifier = modifier * 2;
                        }
                        //Resist: BUG, DARK, ROCK
                        if (move->getType() == Types::BUG || move->getType() == Types::DARK || move->getType() == Types::ROCK) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::FIRE:
                        //Weak: Ground, Rock, Water
                        if (move->getType() == Types::GROUND || move->getType() == Types::ROCK || move->getType() == Types::WATER) {
                            modifier = modifier * 2;
                        }
                        //Resist: Bug, Steel, Fire, Grass, Ice, Fairy
                        if (move->getType() == Types::BUG || move->getType() == Types::STEEL || move->getType() == Types::FIRE ||
                            move->getType() == Types::GRASS || move->getType() == Types::ICE || move->getType() == Types::FAIRY) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::FLYING:
                        //Weak: Electric, Ice, Rock
                        if (move->getType() == Types::ELECTRIC || move->getType() == Types::ICE || move->getType() == Types::ROCK) {
                            modifier = modifier * 2;
                           }
                        //Resist: Bug, Fighting, Grass
                        if (move->getType() == Types::BUG || move->getType() == Types::FIGHTING || move->getType() == Types::GRASS) {
                            modifier = modifier / 2;
                        }
                        //Immune: Ground
                        if (move->getType() == Types::GROUND) {
                            modifier = 0;
                        }
                        break;
        
                    case Types::GHOST:
                        //Weak: DARK, GHOST
                        if (move->getType() == Types::DARK || move->getType() == Types::GHOST) {
                            modifier = modifier * 2;
                        }
                        //Resist: BUG, POISON
                        if (move->getType() == Types::BUG || move->getType() == Types::POISON) {
                            modifier = modifier / 2;
                        }
                        //Immune: NORMAL, FIGHTING
                        if (move->getType() == Types::NORMAL || move->getType() == Types::FIGHTING) {
                            modifier = 0;
                        }
                        break;
        
                    case Types::GRASS:
                        //Weak: Bug, Fire, Flying, Ice, Poison
                        if (move->getType() == Types::BUG || move->getType() == Types::FIRE || move->getType() == Types::FLYING ||
                            move->getType() == Types::ICE || move->getType() == Types::POISON) {
                            modifier = modifier * 2;
                            }
                        //Resist: Electric, Grass, Ground, Water
                        if (move->getType() == Types::ELECTRIC || move->getType() == Types::GRASS || move->getType() == Types::GROUND || move->getType() == Types::WATER) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::GROUND:
                        //Weak: WATER, GRASS, ICE
                        if (move->getType() == Types::WATER || move->getType() == Types::GRASS || move->getType() == Types::ICE) {
                            modifier = modifier * 2;
                        }
                        //Resist: POISON, ROCK
                        if (move->getType() == Types::POISON || move->getType() == Types::ROCK) {
                            modifier = modifier / 2;
                        }
                        //Immune: ELECTRIC
                        if (move->getType() == Types::ELECTRIC) {
                            modifier = 0;
                        }
                        break;
        
                    case Types::ICE:
                        //Weak: FIGHTING, ROCK, STEEL, FIRE
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::ROCK || move->getType() == Types::STEEL || move->getType() == Types::FIRE) {
                            modifier = modifier * 2;
                        }
                        //Resist: ICE
                        if (move->getType() == Types::ICE) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::NORMAL:
                        //Weak: FIGHTING
                        if (move->getType() == Types::FIGHTING) {
                            modifier = modifier * 2;
                        }
                        //Immune: GHOST
                        if (move->getType() == Types::GHOST) {
                            modifier = 0;
                        }
                        break;
        
                    case Types::POISON:
                        //Weak: Ground, Psychic
                        if (move->getType() == Types::GROUND || move->getType() == Types::PSYCHIC) {
                            modifier = modifier * 2;
                        }
                        //Resist: Fighting, Poison, Bug, Grass, FAIRY
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::POISON || move->getType() == Types::BUG ||
                            move->getType() == Types::GRASS || move->getType() == Types::FAIRY) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::PSYCHIC:
                        //Weak: BUG, DARK, GHOST
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::POISON || move->getType() == Types::BUG) {
                            modifier = modifier * 2;
                        }
                        //Resist: FIGHTING, PSYCHIC
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::PSYCHIC) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::ROCK:
                        //Weak: FIGHTING, GROUND, STEEL, WATER, GRASS
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::GROUND || move->getType() == Types::STEEL||
                            move->getType() == Types::GRASS || move->getType() == Types::GRASS) {
                            modifier = modifier * 2;
                        }
                        //Resist: NORMAL, FLYING, POISON, FIRE
                        if (move->getType() == Types::NORMAL || move->getType() == Types::FLYING || move->getType() == Types::POISON || move->getType() == Types::FIRE) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::STEEL:
                        //Weak: GROUND, FIGHTING, FIRE
                        if (move->getType() == Types::GROUND || move->getType() == Types::FIGHTING || move->getType() == Types::FIRE) {
                            modifier = modifier * 2;
                        }
                        //Resist: NORMAL, FLYING, ROCK, BUG, STEEL, GRASS, PSYCHIC, ICE, FAIRY, DRAGON
                        if (move->getType() == Types::NORMAL || move->getType() == Types::FLYING || move->getType() == Types::ROCK || move->getType() == Types::BUG ||
                            move->getType() == Types::STEEL || move->getType() == Types::GRASS || move->getType() == Types::PSYCHIC || move->getType() == Types::ICE ||
                            move->getType() == Types::FAIRY || move->getType() == Types::DRAGON) {
                            modifier = modifier / 2;
                        }
                        //Immune: POISON
                        if (move->getType() == Types::POISON) {
                            modifier = 0;
                        }
                        break;
                
                    case Types::WATER:
                        //Weak: Electric, Grass
                        if (move->getType() == Types::ELECTRIC || move->getType() == Types::GRASS) {
                            modifier = modifier * 2;
                        }
                        //Resist: Steel, Fire, Water, Ice
                        if (move->getType() == Types::STEEL || move->getType() == Types::FIRE || move->getType() == Types::WATER || move->getType() == Types::ICE) {
                            modifier = modifier / 2;
                        }
                        break;
                }
            }

            if (defender->getTypeB() != Types::NONE) { // Adjust as necessary to handle null or no type
                switch (defender->getTypeB()) {
                    case Types::BUG:
                        // Weak: Flying, Rock, Fire
                        if (move->getType() == Types::FLYING || move->getType() == Types::ROCK || move->getType() == Types::FIRE) {
                            modifier *= 2;
                        }
                        // Resist: Fighting, Ground, Grass
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::GROUND || move->getType() == Types::GRASS) {
                            modifier /= 2;
                        }
                        break;

                    case Types::DARK:
                        //Weak: BUG, FAIRY, FIGHTING
                        if (move->getType() == Types::BUG || move->getType() == Types::FAIRY || move->getType() == Types::FIGHTING) {
                            modifier = modifier * 2;
                        }
                        //Resist: GHOST, DARK
                        if (move->getType() == Types::GHOST || move->getType() == Types::DARK) {
                            modifier = modifier / 2;
                        }
                        //Immune: Psychic
                        if (move->getType() == Types::PSYCHIC) {
                            modifier = 0;
                        }
                        break;

                    case Types::DRAGON:
                        //Weak: DRAGON, FAIRY, ICE
                        if (move->getType() == Types::DRAGON || move->getType() == Types::FAIRY || move->getType() == Types::ICE) {
                            modifier = modifier * 2;
                        }
                        //Resist: FIRE, WATER, GRASS, ELECTRIC
                        if (move->getType() == Types::FIRE || move->getType() == Types::WATER || move->getType() == Types::GRASS || move->getType() == Types::ELECTRIC) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::ELECTRIC:
                        //Weak: GROUND
                        if (move->getType() == Types::GROUND) {
                            modifier = modifier * 2;
                        }
                        //Resist: FLYING, ELECTRIC, STEEL
                        if (move->getType() == Types::FLYING || move->getType() == Types::ELECTRIC || move->getType() == Types::STEEL) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::FAIRY:
                        //Weak: POISON, STEEL
                        if (move->getType() == Types::POISON || move->getType() == Types::STEEL) {
                            modifier = modifier * 2;
                        }
                        //Resist: BUG, DARK, FIGHTING
                        if (move->getType() == Types::BUG || move->getType() == Types::DARK || move->getType() == Types::FIGHTING) {
                            modifier = modifier / 2;
                        }
                        //Immune: DRAGON
                        if (move->getType() == Types::DRAGON) {
                            modifier = 0;
                        }
                        break;

                        case Types::FIGHTING:
                        //Weak: FAIRY, FLYING, PSYCHIC
                        if (move->getType() == Types::FAIRY || move->getType() == Types::FLYING || move->getType() == Types::PSYCHIC) {
                            modifier = modifier * 2;
                        }
                        //Resist: BUG, DARK, ROCK
                        if (move->getType() == Types::BUG || move->getType() == Types::DARK || move->getType() == Types::ROCK) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::FIRE:
                        //Weak: Ground, Rock, Water
                        if (move->getType() == Types::GROUND || move->getType() == Types::ROCK || move->getType() == Types::WATER) {
                            modifier = modifier * 2;
                        }
                        //Resist: Bug, Steel, Fire, Grass, Ice, Fairy
                        if (move->getType() == Types::BUG || move->getType() == Types::STEEL || move->getType() == Types::FIRE ||
                            move->getType() == Types::GRASS || move->getType() == Types::ICE || move->getType() == Types::FAIRY) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::FLYING:
                        //Weak: Electric, Ice, Rock
                        if (move->getType() == Types::ELECTRIC || move->getType() == Types::ICE || move->getType() == Types::ROCK) {
                            modifier = modifier * 2;
                           }
                        //Resist: Bug, Fighting, Grass
                        if (move->getType() == Types::BUG || move->getType() == Types::FIGHTING || move->getType() == Types::GRASS) {
                            modifier = modifier / 2;
                        }
                        //Immune: Ground
                        if (move->getType() == Types::GROUND) {
                            modifier = 0;
                        }
                        break;
        
                    case Types::GHOST:
                        //Weak: DARK, GHOST
                        if (move->getType() == Types::DARK || move->getType() == Types::GHOST) {
                            modifier = modifier * 2;
                        }
                        //Resist: BUG, POISON
                        if (move->getType() == Types::BUG || move->getType() == Types::POISON) {
                            modifier = modifier / 2;
                        }
                        //Immune: NORMAL, FIGHTING
                        if (move->getType() == Types::NORMAL || move->getType() == Types::FIGHTING) {
                            modifier = 0;
                        }
                        break;
        
                    case Types::GRASS:
                        //Weak: Bug, Fire, Flying, Ice, Poison
                        if (move->getType() == Types::BUG || move->getType() == Types::FIRE || move->getType() == Types::FLYING ||
                            move->getType() == Types::ICE || move->getType() == Types::POISON) {
                            modifier = modifier * 2;
                            }
                        //Resist: Electric, Grass, Ground, Water
                        if (move->getType() == Types::ELECTRIC || move->getType() == Types::GRASS || move->getType() == Types::GROUND || move->getType() == Types::WATER) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::GROUND:
                        //Weak: WATER, GRASS, ICE
                        if (move->getType() == Types::WATER || move->getType() == Types::GRASS || move->getType() == Types::ICE) {
                            modifier = modifier * 2;
                        }
                        //Resist: POISON, ROCK
                        if (move->getType() == Types::POISON || move->getType() == Types::ROCK) {
                            modifier = modifier / 2;
                        }
                        //Immune: ELECTRIC
                        if (move->getType() == Types::ELECTRIC) {
                            modifier = 0;
                        }
                        break;
        
                    case Types::ICE:
                        //Weak: FIGHTING, ROCK, STEEL, FIRE
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::ROCK || move->getType() == Types::STEEL || move->getType() == Types::FIRE) {
                            modifier = modifier * 2;
                        }
                        //Resist: ICE
                        if (move->getType() == Types::ICE) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::NORMAL:
                        //Weak: FIGHTING
                        if (move->getType() == Types::FIGHTING) {
                            modifier = modifier * 2;
                        }
                        //Immune: GHOST
                        if (move->getType() == Types::GHOST) {
                            modifier = 0;
                        }
                        break;
        
                    case Types::POISON:
                        //Weak: Ground, Psychic
                        if (move->getType() == Types::GROUND || move->getType() == Types::PSYCHIC) {
                            modifier = modifier * 2;
                        }
                        //Resist: Fighting, Poison, Bug, Grass, FAIRY
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::POISON || move->getType() == Types::BUG ||
                            move->getType() == Types::GRASS || move->getType() == Types::FAIRY) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::PSYCHIC:
                        //Weak: BUG, DARK, GHOST
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::POISON || move->getType() == Types::BUG) {
                            modifier = modifier * 2;
                        }
                        //Resist: FIGHTING, PSYCHIC
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::PSYCHIC) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::ROCK:
                        //Weak: FIGHTING, GROUND, STEEL, WATER, GRASS
                        if (move->getType() == Types::FIGHTING || move->getType() == Types::GROUND || move->getType() == Types::STEEL||
                            move->getType() == Types::GRASS || move->getType() == Types::GRASS) {
                            modifier = modifier * 2;
                        }
                        //Resist: NORMAL, FLYING, POISON, FIRE
                        if (move->getType() == Types::NORMAL || move->getType() == Types::FLYING || move->getType() == Types::POISON || move->getType() == Types::FIRE) {
                            modifier = modifier / 2;
                        }
                        break;
        
                    case Types::STEEL:
                        //Weak: GROUND, FIGHTING, FIRE
                        if (move->getType() == Types::GROUND || move->getType() == Types::FIGHTING || move->getType() == Types::FIRE) {
                            modifier = modifier * 2;
                        }
                        //Resist: NORMAL, FLYING, ROCK, BUG, STEEL, GRASS, PSYCHIC, ICE, FAIRY, DRAGON
                        if (move->getType() == Types::NORMAL || move->getType() == Types::FLYING || move->getType() == Types::ROCK || move->getType() == Types::BUG ||
                            move->getType() == Types::STEEL || move->getType() == Types::GRASS || move->getType() == Types::PSYCHIC || move->getType() == Types::ICE ||
                            move->getType() == Types::FAIRY || move->getType() == Types::DRAGON) {
                            modifier = modifier / 2;
                        }
                        //Immune: POISON
                        if (move->getType() == Types::POISON) {
                            modifier = 0;
                        }
                        break;
                
                    case Types::WATER:
                        //Weak: Electric, Grass
                        if (move->getType() == Types::ELECTRIC || move->getType() == Types::GRASS) {
                            modifier = modifier * 2;
                        }
                        //Resist: Steel, Fire, Water, Ice
                        if (move->getType() == Types::STEEL || move->getType() == Types::FIRE || move->getType() == Types::WATER || move->getType() == Types::ICE) {
                            modifier = modifier / 2;
                        }
                        break;
                }
            }

            if (modifier > 1) {
                superEff++;
            } else if (modifier == 0) {
                noEff++;
            } else if (modifier < 1) {
                notVeryEff++;
            }

            damage = (int)(damage * modifier);
            dmgArray[0] = damage;
            dmgArray[1] = superEff;
            dmgArray[2] = notVeryEff;
            dmgArray[3] = noEff;  // Update as necessary for no effect cases
            return dmgArray;
        }

        static void damageCalc (Pokemon* attacker, Pokemon* defender, Move* move){
            // Initialize random number generator
            std::srand(static_cast<unsigned int>(std::time(0)));

            double critCalc = 0;
            double stab = 1.0;
            double randFact = 0;
            double force = 0;
            double object = 0;

            // Physical or special attack calculation
            if (move->getCat() == 1) {
                force = attacker->getAtk();
                object = defender->getDef();
            } else if (move->getCat() == 2) {
                force = attacker->getSpa();
                object = defender->getSpd();
            }

            // Critical hit calculation
            critCalc = std::rand() % 256;
            if (critCalc < (attacker->getSpe() / 2)) {
                critCalc = 1.5;
                std::cout << "It's a critical hit!" << std::endl;
            } else {
                critCalc = 1.0;
            }

            // Random factor calculation
            randFact = (std::rand() % 16 + 85) / 100.0;

            // Same Type Attack Bonus (STAB)
            if (move->getType() == attacker->getTypeA() || move->getType() == attacker->getTypeB()) {
                stab = 1.5;
            }

            // Base damage calculation
            int baseDamage = static_cast<int>((((22) * move->getPow() * (force / object)) / (50.0 + 2)) * critCalc * randFact * stab);

            // Get type multiplier
            std::vector<int> dmgArray = typeMultiplier(baseDamage, move, defender);
            baseDamage = dmgArray[0];

            // Determine effectiveness
            if (dmgArray[1] == 1) {
                std::cout << "It's super effective!" << std::endl;
            } else if (dmgArray[2] == 1) {
                std::cout << "It's not very effective..." << std::endl;
            } else if (dmgArray[3] == 1) {
                std::cout << "It doesn't affect " << defender->getName() << "..." << std::endl;
            }

            // Apply damage to defender's HP
            defender->setHP(defender->getHP() - baseDamage);
            std::cout << baseDamage << " damage!" << std::endl;
        }

        void statusCalc(Pokemon* attacker, Pokemon* defender, Move* move) {
            // {buff/debuff, atk, def, spa, spd, spe, acc, eva}
            std::array<int, 8> effect = move->getEff();
            double mult;
            int multStage;
        
            if (effect[0] == 0) { // If buffing self
                if (effect[1] != 0) { // Buff attack
                    multStage = effect[1];
                    attacker->setAtkStage(multStage);
                    multStage = attacker->getAtkStage();
                    mult = statMultiplier[multStage];
                    int newAtk = static_cast<int>(mult * attacker->getAtk());
                    attacker->setAtk(newAtk);
                    std::cout << attacker->getName() << "'s attack rose!" << std::endl;
                }
                if (effect[2] != 0) { // Buff defense
                    multStage = effect[2];
                    attacker->setDefStage(multStage);
                    multStage = attacker->getDefStage();
                    mult = statMultiplier[multStage];
                    int newDef = static_cast<int>(mult * attacker->getDef());
                    attacker->setDef(newDef);
                    std::cout << attacker->getName() << "'s defense rose!" << std::endl;
                }
                if (effect[3] != 0) { // Buff special attack
                    multStage = effect[3];
                    attacker->setSpaStage(multStage);
                    multStage = attacker->getSpaStage();
                    mult = statMultiplier[multStage];
                    int newSpa = static_cast<int>(mult * attacker->getSpa());
                    attacker->setSpa(newSpa);
                    std::cout << attacker->getName() << "'s special attack rose!" << std::endl;
                }
                if (effect[4] != 0) { // Buff special defense
                    multStage = effect[4];
                    attacker->setSpdStage(multStage);
                    multStage = attacker->getSpdStage();
                    mult = statMultiplier[multStage];
                    int newSpd = static_cast<int>(mult * attacker->getSpd());
                    attacker->setSpd(newSpd);
                    std::cout << attacker->getName() << "'s special defense rose!" << std::endl;
                }
                if (effect[5] != 0) { // Buff speed
                    multStage = effect[5];
                    attacker->setSpeStage(multStage);
                    multStage = attacker->getSpeStage();
                    mult = statMultiplier[multStage];
                    int newSpe = static_cast<int>(mult * attacker->getSpe());
                    attacker->setSpe(newSpe);
                    std::cout << attacker->getName() << "'s speed rose!" << std::endl;
                }
                if (effect[6] != 0) { // Buff accuracy
                    std::cout << attacker->getName() << "'s accuracy rose!" << std::endl;
                }
                if (effect[7] != 0) { // Buff evasion
                    std::cout << attacker->getName() << "'s evasion rose!" << std::endl;
                }
            } else if (effect[0] == 1) { // Debuffing opponent
                if (effect[1] != 0) { // Debuff attack
                    multStage = effect[1];
                    defender->setAtkStage(multStage);
                    multStage = defender->getAtkStage();
                    mult = statMultiplier[multStage];
                    int newAtk = static_cast<int>(mult * defender->getAtk());
                    defender->setAtk(newAtk);
                    std::cout << defender->getName() << "'s attack fell!" << std::endl;
                }
                if (effect[2] != 0) { // Debuff defense
                    multStage = effect[2];
                    defender->setDefStage(multStage);
                    multStage = defender->getDefStage();
                    mult = statMultiplier[multStage];
                    int newDef = static_cast<int>(mult * defender->getDef());
                    defender->setDef(newDef);
                    std::cout << defender->getName() << "'s defense fell!" << std::endl;
                }
                if (effect[3] != 0) { // Debuff special attack
                    multStage = effect[3];
                    defender->setSpaStage(multStage);
                    multStage = defender->getSpaStage();
                    mult = statMultiplier[multStage];
                    int newSpa = static_cast<int>(mult * defender->getSpa());
                    defender->setSpa(newSpa);
                    std::cout << defender->getName() << "'s special attack fell!" << std::endl;
                }
                if (effect[4] != 0) { // Debuff special defense
                    multStage = effect[4];
                    defender->setSpdStage(multStage);
                    multStage = defender->getSpdStage();
                    mult = statMultiplier[multStage];
                    int newSpd = static_cast<int>(mult * defender->getSpd());
                    defender->setSpd(newSpd);
                    std::cout << defender->getName() << "'s special defense fell!" << std::endl;
                }
                if (effect[5] != 0) { // Debuff speed
                    multStage = effect[5];
                    defender->setSpeStage(multStage);
                    multStage = defender->getSpeStage();
                    mult = statMultiplier[multStage];
                    int newSpe = static_cast<int>(mult * defender->getSpe());
                    defender->setSpe(newSpe);
                    std::cout << defender->getName() << "'s speed fell!" << std::endl;
                }
                if (effect[6] != 0) { // Debuff accuracy
                    std::cout << defender->getName() << "'s accuracy fell!" << std::endl;
                }
                if (effect[7] != 0) { // Debuff evasion
                    std::cout << defender->getName() << "'s evasion fell!" << std::endl;
                }
            }
        }

        Pokemon* battle(Pokemon* friend_pokemon, Pokemon* foe) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            
            std::cout << foe->getName() << " appears!" << std::endl;
        
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<> dist(0, 100);
        
            // Until KO
            while (friend_pokemon->getHP() >= 1 && foe->getHP() >= 1) {
                if (friend_pokemon->getSpe() > foe->getSpe()) {
                    // Friend attacks first
                    Move selected = friend_pokemon->getMove(rng() % friend_pokemon->getMovesNum());
                    std::cout << friend_pokemon->getName() << " uses " << selected.getName() << "!" << std::endl;
        
                    if (selected.getCat() == 3) {
                        statusCalc(friend_pokemon, foe, &selected);
                    } else {
                        damageCalc(friend_pokemon, foe, &selected);
                    }
        
                    // Pause after every attack
                    std::this_thread::sleep_for(std::chrono::seconds(3));
        
                    if (foe->getHP() < 1) break;
        
                    // Foe attacks
                    Move selected = foe->getMove(rng() % foe->getMovesNum());
                    std::cout << foe->getName() << " uses " << selected.getName() << "!" << std::endl;
        
                    if (selected.getCat() == 3) {
                        statusCalc(foe, friend_pokemon, &selected);
                    } else {
                        damageCalc(foe, friend_pokemon, &selected);
                    }
        
                    // Pause after every attack
                    std::this_thread::sleep_for(std::chrono::seconds(3));
        
                } else {
                    // Foe attacks first
                    Move selected = foe->getMove(rng() % foe->getMovesNum());
                    std::cout << foe->getName() << " uses " << selected.getName() << "!" << std::endl;
        
                    if (selected.getCat() == 3) {
                        statusCalc(foe, friend_pokemon, &selected);
                    } else {
                        damageCalc(foe, friend_pokemon, &selected);
                    }
        
                    // Pause after every attack
                    std::this_thread::sleep_for(std::chrono::seconds(3));
        
                    if (friend_pokemon->getHP() < 1) break;
        
                    // Friend attacks
                    Move selected = friend_pokemon->getMove(rng() % friend_pokemon->getMovesNum());
                    std::cout << friend_pokemon->getName() << " uses " << selected.getName() << "!" << std::endl;
        
                    if (selected.getCat() == 3) {
                        statusCalc(friend_pokemon, foe, &selected);
                    } else {
                        damageCalc(friend_pokemon, foe, &selected);
                    }
        
                    // Pause after every attack
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }
            }
        
            if (foe->getHP() < 1) {
                std::cout << "The enemy " << foe->getName() << " fainted!" << std::endl;
                return friend_pokemon;
            } else {
                std::cout << friend_pokemon->getName() << " fainted..." << std::endl;
                return foe;
            }
        }

        int main() {
            // Populate AttackDex and PokeDex
            AttackDex attackdex;
            attackdex.populate();
            PokeDex pokedex;
            pokedex.populate();
            multiPopulate();
        
            // User Charmander vs enemy Squirtle
            Pokemon* winner = battle(pokedex.pokedex[4], pokedex.pokedex[7]);
            std::cout << winner->getName() << " wins!" << std::endl;
        
            return 0;
        }

};