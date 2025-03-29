#include <iostream>
#include <unordered_map>
#include <string>
#include "Move.h"
#include "Types.h"

class AttackDex{
    public:
        std::unordered_map<std::string, Move> attackdex;

        void populate(){
            attackdex["Tackle"] = Move("Tackle", Types::NORMAL, 1, 40, 100, 35, {});
            attackdex["Scratch"] = Move("Scratch", Types::NORMAL, 1, 40, 100, 35, {});

            std::array status = {1, -1, 0, 0, 0, 0, 0, 0}; // lower target attack by one stage
            attackdex["Growl"] = Move("Growl", Types::NORMAL, 3, 0, 100, 40, status);

            status = {1, 0, -1, 0, 0, 0, 0, 0};
            attackdex["Tail Whip"] = Move("Tail Whip", Types::NORMAL, 3, 0, 100, 40, status);
            attackdex["Vine Whip"] = Move("Vine Whip", Types::GRASS, 1, 45, 100, 25, {});
            attackdex["Water Gun"] = Move("Water Gun", Types::WATER, 2, 40, 100, 25, {});
            attackdex["Ember"] = Move("Ember", Types::FIRE, 2, 40, 100, 25, {});

            status = {0, 1, 0, 1, 0, 0, 0, 0}; // raise user atk and spa by one stage
            attackdex["Growth"] = Move("Growth", Types::NORMAL, 3, 0, 0, 20, status);

            status = {0, 0, 1, 0, 0, 0, 0, 0}; // raise user def one stage
            attackdex["Withdraw"] = Move("Withdraw", Types::WATER, 3, 0, 0, 40, status);
            
            status = {1, 0, 0, 0, 0, 0, -1, 0}; // lower target acc one stage
            attackdex["Smokescreen"] = Move("Smokescreen", Types::NORMAL, 3, 0, 100, 20, status);
        }

};