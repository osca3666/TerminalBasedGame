#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Party.h"
#include <vector>

using namespace std;

//player is automatically reset when it is created
Player::Player()
{
    resetPlayer();
}

//basic default data member values to start the game
void Player::resetPlayer()
{
    player_name = "";
    player_fullness = 50;
    //whole party info so assign it to the 1st index of party (the player)
    for (int i = 0; i < 5;i++)
    {
        weapon[i] = 0;
    }
    weapon_amount = 0;
    armor = 0;
    gold = 100;
    ingredients = 0;
    for (int i = 0; i < 3;i++)
    {
        cookware[i] = 0;
    }
    rooms_cleared = 0;
    keys_found = 0;
    for (int i = 0; i < 5;i++)
    {
        treasures[i] = 0;
    }
    anger_level = 0;
}

/*
Algorithm: 
Print the status page
*/
void Player::displayStatus(vector<Party> party)
{
    cout<<"___________________________________________________"<<endl<<"|                     PROGRESS                    |"<<endl;
    cout<<"---------------------------------------------------"<<endl<<"  Rooms Cleared: "<<rooms_cleared<<" | Keys: "<<keys_found<<" | Anger Level: "<<anger_level<<endl;
    cout<<"___________________________________________________"<<endl<<"|                    INVENTORY                    |"<<endl<<"---------------------------------------------------"<<endl;
    cout<<"  Gold        | "<<gold<<endl<<"  Weapons     | C: "<<weapon[0]<<" | S: "<<weapon[1]<<" | R: "<<weapon[2]<<" | B: "<<weapon[3]<<" | L: "<<weapon[4]<<endl;
    cout<<"  Armor       | "<<armor<<endl<<"  Ingredients | "<<ingredients<<" kg"<<endl;
    cout<<"  Cookware    | P: "<<cookware[0]<<" | F: "<<cookware[1]<<" | C: "<<cookware[2]<<endl;
    cout<<"  Treasures   | R: "<<treasures[0]<<" | N: "<<treasures[1]<<" | B: "<<treasures[2]<<" | C: "<<treasures[3]<<" | G: "<<treasures[4]<<endl;
    cout<<"___________________________________________________"<<endl<<"|                   PARTY STATUS                  |"<<endl<<"---------------------------------------------------"<<endl;
    cout<<"  "<<player_name<<" | Fullness: "<<player_fullness<<endl;
    for (int i = 0;i <party.size();i++)
    {
        cout<<"  "<<party.at(i).getPartyMemberName()<<" | Fullness: "<<party.at(i).getPartyMemberFullness()<<endl;       
    }
    cout<<"___________________________________________________"<<endl<<endl;
}

//return player name
string Player::getPlayerName()
{
    return player_name;
}
//return player fullness
int Player::getPlayerFullness()
{
    return player_fullness;
}
// return player weapon
int Player::getWeapon(int weapon_index)
{
    return weapon[weapon_index];
}
//return the total number of weapons
int Player::getWeaponAmount(vector<Party> party)
{
    for (int i = 0; i < party.size() + 1; i++)
    {
        weapon_amount += weapon[i];
    }
    return weapon_amount;
}
//return group armor total
int Player::getArmor()
{
    return armor;
}
//return group gold total
int Player::getGold()
{
    return gold;
}
//return group ingrdients total
int Player::getIngredients()
{
    return ingredients;
}
//return group cookware at specified index
int Player::getCookware(int cookware_id) //return cookware at specified choice
{
    return cookware[cookware_id];
}
//return total number of rooms cleared
int Player::getRoomsCleared()
{
    return rooms_cleared;
}
//return the number of keys in hand
int Player::getKeysFound()
{
    return keys_found;
}
//return the amount of treasures at specified index of the array
int Player::getTreasures(int treasure_id) //return treasure at specified choice
{
    return treasures[treasure_id];
}
//return sorceror anger level
int Player::getAngerLevel()
{
    return anger_level;
}



//setters
//per party member
//set player name by taking the input that is player name
void Player::setPlayerName(string player_name_)
{
    player_name = player_name_;
}
//set player fullness by taking in the input that is how much to change fullness by
//define new fullness which is the the existing fullness plus the requested change in fullness
//if fullness is greater than 50, change it back to 50 because it is the cap
//else make fullness the new fullness
void Player::setPlayerFullness(int player_fullness_)
{
    int new_fullness = player_fullness + player_fullness_;
    if (new_fullness >= 50) //cap fullness at 50
    {
        player_fullness = 50;
    }
    else
    {
        player_fullness = new_fullness;
    }
}


//Whole group. Only one per group
//set the weapon amount at the requested index to the requested weapon amount
void Player::setWeapon(int weapon_amount_, int weapon_index) 
{
    weapon[weapon_index] = weapon_amount_;
}
//set the total weapon amount to the request argument
void Player::setWeaponAmount(int weapon_amount_)
{
    weapon_amount = weapon_amount_;
}
//set the total armor to the requested armor
void Player::setArmor(int armor_)
{
    armor = armor_;
}
//get gold to the new gold
void Player::setGold(int gold_)
{
    gold = gold_;
}
//set ingredients amount to the new ingredients
void Player::setIngredients(int ingredients_)
{
    ingredients = ingredients_;
}
//set cookware at requested index to the requested amount
void Player::setCookware(int cookware_amount, int cookware_index) //vector. new cookware means add it to the cookware vector
{
    cookware[cookware_index] = cookware_amount;
}
//set keys found to the requested number 
void Player::setKeysFound(int keys_found_)
{
    if (keys_found_ <= 0)
    {
        keys_found = 0;
    }
    else
    {
        keys_found = keys_found_;
    }
}
//set treasures at requested index to the requested amount
void Player::setTreasures(int treasure_amount, int treasure_index) // vector. new treasure means add it to the treasure vector
{
    treasures[treasure_index] = treasure_amount;
}
//add one to rooms cleared when this function is called
void Player::increaseRoomsCleared()
{
    rooms_cleared++;
}
//if room cleared is not more than or equal to five, add one to anger level data member
// if anger level is 100 or more, print game over message 
void Player::increaseAngerLevel()
{
    if (!(rooms_cleared >= 5)) //anger level stops changing when all rooms cleared
    {
        anger_level++;
    }
          //this game end when anger level is more than or equal to 100 needs to be in the main driver
    if (anger_level >= 100)
    {
        cout<<"Game ends, Sorceror mad and kill you"<<endl;
    }

}
