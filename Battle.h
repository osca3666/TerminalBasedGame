#ifndef Battle_H
#define Battle_H


#include <iostream>
#include <string>
#include "Player.h"
#include "Party.h"
#include <vector>
using namespace std;

class Battle{

    private:
        string Moster;
        int moster_level = 0;
        vector<string> monsters_lv1; //5
        vector<string> monsters_lv2; //4
        vector<string> monsters_lv3; //4
        vector<string> monsters_lv4; //4
        vector<string> monsters_lv5;
        string sourcer;
        
    public:
        void setMosterLevel(string filename); // sorts each monster to a vector of monsters depending on it's level
        string getMosterLevel(int monster_lvl) const;

        int Figth(Player&, int challenge_level, vector<Party>& party, string monster);
        void Surrender(vector<Party>& party);



};

#endif