#ifndef MISFORTUNE_H
#define MISFORTUNE_H
#include "Party.h"
#include "Player.h"
#include <iostream>
#include <vector>
using namespace std;

class Misfortune{

    private:
    bool misfortune;

    public:
    void computeMisfortune(Player&, vector<Party>& party);
    // bool getMisfortune() const;

};

#endif