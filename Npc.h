#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <vector>
#include "Player.h"
#include "Party.h"
using namespace std;

class Npc //merchant
{
    private:

    public:
        Player displayMenu(Player player,vector <Party> party);
        int displayRiddle(string file_name);

};

#endif