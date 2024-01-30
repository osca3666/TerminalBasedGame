#ifndef GAME_H
#define GAME_H

#include<iostream>
#include "Map.h"
#include "Npc.h"
#include "Party.h"
#include "Player.h"
#include "Battle.h"
#include "Misfortune.h"

using namespace std;

class Game    //this will be the main class to run the game
{
    private:

    public:
        void runGame();
};
#endif

/*
Phase 1:
Algorithm for actually running the game:
1. Directions for the game/ start screen
2. Ask player for their name & name of their 4 companions 
    2a. Make sure they are set to the default start conditions
3. Generate map
4. Display status 
5. Visit merchant / display merchant menu

Phase 2: 
Show user their options:
    1. Move
        a. move to new location
        b. every party member has a 20% chcance of their hunger dropping
        c. if its an unexplored area, sorceror anger increases by 1
    2. Investigate
        a. space already investigated?
            -end move
        b. space not already investigated?
            -10% chance of finding key
            -20% chance of finding treasure
            -20% chance to fight monster
                -go into option 3 
            -50% chance everyone's fullness drops by 1 pt
    3. Pick a fight
        a. if no weapon, only option is to surrender
        b. if weapon, they can fight or surrender
            - is monster defeated?
                = add 10 * c gold (c=challenge rating)
                = add 5 * c ingredients 
                = 10% chance monster drops key
                -monster is removed from the monster list
            - is monster not defeated?
                = player loses a quarter of their gold reserve rounded downt ot he nearest int
                = they lose upto 30kg of ingredients
                = each party member excluding player independantly has 10% chance of being slain, 5% if wearing armor
                    -print message if party member dies
            - player surrendered?
                = one random party member excluding player is trapped and dies
        c. regardless of result, every party member's fullness has 50% chance to lose

    
    4. Cook and eat
        a. player choose how much ingredient to cook
        b. every 5kg increases fullness by one point
    5. Give up
        ***GAME ENDS***

Phase 3: Game ending conditions

1. Player chooses to quit
2. Player has explored all five rooms and killed all the monsters defeated
3. Sorceror's anger reaches 100
4. Player dies
5. All player's companions have died

*/