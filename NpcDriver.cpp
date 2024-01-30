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
    Npc npc;
    cout<<npc.displayRiddle("riddles.txt");

}