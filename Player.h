#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "Party.h"

using namespace std;

class Player
{
    private: 

        string player_name;
        int player_fullness;
    
                
        //store with player
        int weapon[5]; // C: 0 | S: 0 | R: 0 | B: 0 | L: 0
        int weapon_amount;
        int armor;
        int gold;
        int ingredients;
        int cookware[3]; //P: 1 | F: 1 | C: 1
        int rooms_cleared;
        int keys_found;
        int treasures[5]; // R: 1 | N: 0 | B: 0 | C: 0 | G: 0
        int anger_level;

    public: 
    
        //default constructors
        Player();
        void resetPlayer();

        void displayStatus(vector <Party> party);

        string getPlayerName();
        int getPlayerFullness();

        void setPlayerName(string player_name_);
        void setPlayerFullness(int player_fullness_);

        int getWeapon(int weapon_index); //C: 0 | S: 0 | R: 0 | B: 0 | L: 0
        int getWeaponAmount(vector<Party> party);
        int getArmor();
        int getGold();
        int getIngredients();
        int getCookware(int cookware_id);
        int getRoomsCleared();
        int getKeysFound();
        int getTreasures(int treasure_id);
        int getAngerLevel();


        void setWeapon(int weapon_amount, int weapon_index);
        void setWeaponAmount(int weapon_amount_);
        void setArmor(int armor_);
        void setGold(int gold_);
        void setIngredients(int ingredients_);
        void setCookware(int cookware_amount, int cookware_index);

        void setKeysFound(int keys_found_);
        void setTreasures(int treasure_amount, int treasure_index);

        void increaseRoomsCleared();//roomsCleared++
        void increaseAngerLevel(); // angerlevel++


};


#endif