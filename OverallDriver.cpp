#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <cstdlib> //we need this header to use random nums
#include <ctime>
#include "Map.h"
#include "Npc.h"
#include "Party.h"
#include "Player.h"
#include "Battle.h"
#include "Misfortune.h"
#include "Game.h"

using namespace std;

int main()   
{
    //*** Map files were not changed

    srand(time(0));
    Game game;
    game.runGame();
    // vector<Party> party(4);
    // // Party class
    //     //default constructor
    // party.at(0).resetParty();
    // assert(party.at(0).getFullness() == 50);
    // assert(party.at(0).getPartyMemberName() == "");
    
    // party.at(0).setFullness(-20); //subtracts 20 from fullness
    // party.at(0).setPartyMemberName("Bobby");
    // assert(party.at(0).getFullness() == 30);
    // assert(party.at(0).getPartyMemberName() == "Bobby");

    //player class
    // Player player;
    // Npc npc;
    //     //checking default constructor
    // player.resetPlayer();
    // player.setGold(200);

    // player = npc.displayMenu(player); //used up all the gold
    // cout<<player.getGold()<<endl; //therefore returns 0 gold
    // assert(player.getPlayerFullness() == 50);
    // assert(player.getPlayerName() == "");
    // assert(player.getWeapon(5) == 0);
    // assert(player.getArmor() == 0);
    // assert(player.getGold() == 100);
    // assert(player.getIngredients() == 0);
    // assert(player.getCookware(3) == 0);
    // assert(player.getKeysFound() == 0);
    // assert(player.getTreasures(5) == 0);
    // assert(player.getAngerLevel() == 0);


    
    // player.setPlayerFullness(-20); //subtracts 20 from fullness
    // player.setPlayerName("Timmy");
    // player.setWeapon(2,0);
    // player.setArmor(2);
    // player.setGold(200);
    // player.setIngredients(5);
    // player.setCookware(2,0);
    // player.setKeysFound(1);
    // player.setTreasures(2,0);
    // player.setAngerLevel(12);
    // assert(player.getPlayerFullness() == 30);
    // assert(player.getPlayerName() == "Timmy");
    // assert(player.getWeapon(0) == 2);
    // assert(player.getArmor() == 2);
    // assert(player.getGold() == 200);
    // assert(player.getIngredients() == 5);
    // assert(player.getCookware(0) == 2);
    // assert(player.getKeysFound() == 1);
    // assert(player.getTreasures(0) == 2);
    // assert(player.getAngerLevel() == 12);







    return 0;
}