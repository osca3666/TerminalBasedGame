#include "Battle.h"
#include "Player.h"
#include "Party.h"
#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <ctime>
#include <vector>

using namespace std;

/**
 * ranGenerator3(): generates a random number between min and max 
 * 
 * algo:
 * 1) performs the computation to get the random number 
 * 2) stores value in random 
 * 
 * returns:
 * int random: random number generated
*/

int ranGenerator3(int max, int min){
    //if we want b/w min and max --> rand() % (max - min + 1) + min
    int random = 0;

    random = rand() % (max - min + 1) + min;

    return random; 
}


/**
 * setMonsterLevel()
 * 
 * algo:
 * 1) reads a file
 * 2) looks for a comma on each line of the tile 
 * 3) stores the character next to the ',' to find the level
 * 4) creates a substring from the start of the line to the index where the comma was and stores it in temp 
 * 5) stores temp in the corresponding vector depending on it's level
 * 
 * parameters:
 * (sting) filename: the file to be evaluated
 * 
 * return:
 * does not return anything
*/

void Battle::setMosterLevel(string filename){
    string line;
    string temp;
    // vector<string> monsters_lv1; //5
    // vector<string> monsters_lv2; //4
    // vector<string> monsters_lv3; //4
    // vector<string> monsters_lv4; //4
    // vector<string> monsters_lv5; //6
    int temp_level = 0;
    ifstream fin(filename);
    // string sourcer;

    if(fin.fail()){
        cout<<"file does not exist"<<endl;
        return;
    }

    while(getline(fin, line)){
        int line_length = line.length();

        for(int i = 0; i < line_length; i++){
            if(line[i] == ','){ //gets the level of each monster inside of mosters.txt
                temp = line[i + 1];
                temp_level = stoi(temp);

                temp = line.substr(0,i);

                switch(temp_level){ //populates vectors with monsters of the corresponding level
                    case 1:
                        monsters_lv1.push_back(temp);
                    break;
                    case 2:
                        monsters_lv2.push_back(temp);
                    break;
                    case 3:
                        monsters_lv3.push_back(temp);
                    break;
                    case 4:
                        monsters_lv4.push_back(temp);
                    break;
                    case 5:
                        monsters_lv5.push_back(temp);
                    break;
                    case 6:
                        sourcer = temp;
                    break;
                }
            }
                
        }
    }
}

/**
 * getMonsterLevel(int monster_lvl): returns a monster of the desired level 
 * 1)sets vec_size to the size of the vector in question
 * 2) sets max to the size of the vector -1 
 * 3)calls the ranGenerator3 function to get a random number within the vector size
 * 4)returns the monster in the index corresponding to the random number generated
 * 5) if monster_lvl is 6 returns the sourcer
 * 
 * parameters:
 * (int) monster_lvl: the level of the moster to be returned
 * 
 * returns
 * (string) temo_monster: a random monster of the desired level 
*/

string Battle::getMosterLevel(int monster_lvl) const{
    int random_num = 0;
    int vec_size = 0;
    int min = 0, max = 0;
    string temp_monster;
    switch(monster_lvl){
        //case 0:
        case 1:
            vec_size = monsters_lv1.size();
            max = vec_size - 1;

            random_num = ranGenerator3(max, min);
            temp_monster = monsters_lv1.at(random_num);
            // monsters_lv1.erase(monsters_lv1.begin() + random_num); //not working for some reason

            return temp_monster;

        break;
        case 2:
            vec_size = monsters_lv2.size();
            max = vec_size - 1;

            random_num = ranGenerator3(max, min);
            temp_monster = monsters_lv2.at(random_num);

            return temp_monster;
        break;
        case 3:
            vec_size = monsters_lv3.size();
            max = vec_size - 1;

            random_num = ranGenerator3(max, min);
            temp_monster = monsters_lv3.at(random_num);

            return temp_monster;
        break;
        case 4:
            vec_size = monsters_lv4.size();
            max = vec_size - 1;

            random_num = ranGenerator3(max, min);
            temp_monster = monsters_lv4.at(random_num);

            return temp_monster;
        break;
        case 5:
            vec_size = monsters_lv5.size();
            max = vec_size - 1;

            random_num = ranGenerator3(max, min);
            temp_monster = monsters_lv5.at(random_num);

            return temp_monster;
        break;
        case 6:
            return sourcer;
        break;
    }
    return temp_monster;
}

/**
 * figth(): determine whether or not the party defeats a monster 
 * 
 * algo:
 * 1) determines the value of weapon --> w: (num of weapons) + (upgraded wapon)
 * 2) performs calculation to determine the outcome of the battle
 *     .-r1) ran num 1-6, r2) ran num 1-6 independent from r1, w) value of weapons, d = 4 if each party member has a different weapon else d = 0
 *     .- a) number of armor sets of the pary, c) challenge level of the monster
 *    .- formula to determine outcome of the figth--->(r1 * w + d) - (r2*c)/a
 * 3) if the result of formula is > 0 then the party wins the battle
 * 4) else monster wins the battle
 * 5) if monster is defeated, that mosnter will not appear again 
 * 6) if party is defeated, then they loose a quarter of their gold, they loose up to 30kg of incridients and each party member 
 *    excluding the player has a 10% chance of dying if they are not wearing any armor, 5% if they are
 * 7) every party member has a 50% chance of getting their hp reduced by 1 pt
*/

int Battle::Figth(Player& temp_player, int challenge_level, vector<Party>& party, string monster){ //note party can only attack if they have atleast one weapon.

    int num_weapons =0, num_keys = 0;
    int weapons = 0, diff_weapons_bonus = 0;
    int bonus_count = 0, armor = 0;
    bool flag = true;
    int ran_num1, ran_num2;
    int battle_outcome = 0;
    int temp_gold = 0, temp_ingredients = 0;
    int temp_num =0, temp_fullness;
    int size = 0;
    string temp, name;
    bool death = false;
    vector <string> dead_name;

    if(challenge_level == 1 && monsters_lv1.size() == 0){ // migth need to change function to make it an int rather than bool.
        cout<<"You have already defeated every monster in the area, clear more rooms to fight stronger monsters"<<endl;
        return -1;
    }
    else if(challenge_level == 2 && monsters_lv2.size() == 0){
        cout<<"You have already defeated every monster in the area, clear more rooms to fight stronger monsters"<<endl;
        return -1;
    }
    else if(challenge_level == 3 && monsters_lv3.size() == 0){
        cout<<"You have already defeated every monster in the area, clear more rooms to fight stronger monsters"<<endl;
        return -1;
    }
    else if(challenge_level == 4 && monsters_lv4.size() == 0){
        cout<<"You have already defeated every monster in the area, clear more rooms to fight stronger monsters"<<endl;
        return -1;
    }
    else if(challenge_level == 5 && monsters_lv5.size() == 0){
        cout<<"You have already defeated every monster in the area, clear more rooms to fight stronger monsters"<<endl;
        return -1;
    }

    num_weapons = temp_player.getWeaponAmount(party);
    //cout<<"num weapons: "<<num_weapons<<endl;
    armor = temp_player.getArmor();
    if(armor == 0 ){ // iin order to avoid dividing by 0; 
        armor = 1;
    }

    if(temp_player.getWeapon(2) != 0){ // checks if there are any rapiers in the inventory 
        bonus_count++;
    }
    if(temp_player.getWeapon(3) != 0){ //checks if there are any Battle axes in the inventory 
        bonus_count += 2;
    }
    if(temp_player.getWeapon(4) != 0){ // checks if there are any Long swords in the inventory 
        bonus_count += 3;
    }

    num_weapons += bonus_count;
    //cout<<"num weapons: "<<num_weapons<<endl;

    for(int i = 0; i < 5; i++){ //checks if every party member has a different weapon 
        if(temp_player.getWeapon(i) == 0){
            flag = false;
        }
    }
    if(flag){ //gives the 4 bonus points for having different weapons 
        diff_weapons_bonus = 4;
    }

    ran_num1 = ranGenerator3(6, 1);
    ran_num2 = ranGenerator3(6, 1);

    // cout<<"____________________"<<endl;
    // cout<<ran_num1<<", "<<ran_num2<<endl;
    // cout<<"diff_weapon: "<<diff_weapons_bonus<<endl;
    // cout<<"outcome: "<<battle_outcome<<endl;
    // cout<<"num weapons: "<<num_weapons<<endl;
    // cout<<"challenge level: "<< challenge_level<<endl;
    // cout<<"armor: "<<armor<<endl;
    // cout<<"____________________"<<endl;

    
    battle_outcome = (ran_num1 * num_weapons + diff_weapons_bonus) - (ran_num2 * challenge_level / armor); //decides the outcome of the battle
    //cout<<"outcome: "<<battle_outcome<<endl;
    if(battle_outcome > 0){ //party wins the battle 

        cout<<"Your party defeated the "<< monster <<endl;
        temp_gold = temp_player.getGold();
        temp_ingredients = temp_player.getIngredients();

        temp_gold += 10 * challenge_level;
        temp_ingredients += 5 * challenge_level;

        temp_player.setGold(temp_gold);
        temp_player.setIngredients(temp_ingredients);

        temp_num = ranGenerator3(100, 1);

        if(temp_num >=1 && temp_num <=10){
            num_keys = temp_player.getKeysFound();
            num_keys++;

            temp_player.setKeysFound(num_keys);
        }

        if(challenge_level == 1 ){ //erases monsters from becktor 
            //size = monsters_lv1.size();
            for(int i = 0; i < monsters_lv1.size(); i++){
                //temp = monsters_lv1.at(i);

                if(monsters_lv1.at(i) == monster){
                    monsters_lv1.erase(monsters_lv1.begin()+i);
                }
            }

        }
        if(challenge_level == 2 ){
            //size = monsters_lv2.size();
            for(int i = 0; i < monsters_lv2.size(); i++){
                //temp = monsters_lv2.at(i);

                if(monsters_lv2.at(i) == monster){
                    monsters_lv2.erase(monsters_lv2.begin()+i);
                }
            }

        }
        if(challenge_level == 3 ){
            //size = monsters_lv3.size();
            for(int i = 0; i < monsters_lv3.size(); i++){
                //temp = monsters_lv3.at(i);

                if(monsters_lv3.at(i) == monster){
                    monsters_lv3.erase(monsters_lv3.begin()+i);
                }
            }

        }
        if(challenge_level == 4 ){
            //size = monsters_lv4.size();
            for(int i = 0; i < monsters_lv4.size(); i++){
                //temp = monsters_lv4.at(i);

                if(monsters_lv4.at(i) == monster){
                    monsters_lv4.erase(monsters_lv4.begin()+i);
                }
            }

        }
        if(challenge_level == 5 ){
            //size = monsters_lv5.size();
            for(int i = 0; i < monsters_lv5.size(); i++){
                //temp = monsters_lv5.at(i);

                if(monsters_lv5.at(i) == monster){
                    monsters_lv5.erase(monsters_lv5.begin()+i);
                }
            }

        }
        for(int i = 0; i< party.size(); i++){ // every party member includin gthe player has a 50% chance of loosing one fullness point
            temp_num = ranGenerator3(2,1);

            if(temp_num == 1){
                temp_fullness = party.at(i).getPartyMemberFullness();
                temp_fullness -= 1;

                if(temp_fullness <= 0){
                    party.at(i).setPartyMemberFullness(0);
                    name =  party.at(i).getPartyMemberName();
                    party.erase(party.begin() + i);
                    cout << name << "died"<<endl;

                }
                else{
                    cout<<party.at(i).getPartyMemberName()<<" lost one fullness point"<<endl;
                    party.at(i).setPartyMemberFullness(temp_fullness);
                }
            }
        }
        temp_num = ranGenerator3(2,1);

        if(temp_num == 1){
            temp_fullness = temp_player.getPlayerFullness();
            temp_fullness -= 1;
            if(temp_fullness <= 0){
                cout<<temp_player.getPlayerName()<<" died, game over!."<< endl;
                temp_player.setPlayerFullness(0);
            }
            else{
                cout<<temp_player.getPlayerName()<<" lost one fullness point"<<endl;
                temp_player.setPlayerFullness(temp_fullness);
            }
        
        }
        //I have to remove the moster from the vector 
        return 1;
    }
    else{  //party looses 

        cout<<"Your party, couldn't defeat the monster. You lost the battle"<<endl;
        temp_gold = temp_player.getGold();
        temp_gold *= 0.75;

        temp_player.setGold(temp_gold);

        temp_num = ranGenerator3(30, 1);

        temp_ingredients = temp_player.getIngredients();

        temp_ingredients -= temp_num;

        if(temp_ingredients < 0){
            temp_ingredients = 0;
        }

        temp_player.setIngredients(temp_ingredients);

        size = party.size();
        

        armor = temp_player.getArmor();
        
        size -= armor;
        

        for(int i = 0; i < armor; i++){
            temp_num = ranGenerator3(100, 1);
            
            

            if(temp_num >= 1 && temp_num <= 5){
                name = party.at(i).getPartyMemberName();

                dead_name.push_back(name);

                party.erase(party.begin() + i);

                death = true;
                

                
            }

        }
        for(int i = 0; i < size; i++){
            temp_num = ranGenerator3(100, 1);
            
            

            if(temp_num >= 1 && temp_num <= 10){
                name = party.at(i).getPartyMemberName();

                dead_name.push_back(name);

                party.erase(party.begin() + i);

                death = true;
                
            }
        }

        if(death){
            size = dead_name.size();
            // cout<<"dead players: "<<size<<endl;

            for(int i = 0; i < size ; i++){

                cout<<dead_name.at(i);
                if(size > 1 && i + 1 != size){
                    cout<<", ";
                }
            }
            if(size > 1){
                cout<<" were slained by the "<<monster<<" "<<endl;
            }
            else{
                cout<<" was slained by the "<<monster<< " "<<endl;
            }
        }

        for(int i = 0; i< party.size(); i++){ // every party member includin gthe player has a 50% chance of loosing one fullness point
            temp_num = ranGenerator3(2,1);

            if(temp_num == 1){
                temp_fullness = party.at(i).getPartyMemberFullness();
                temp_fullness -= 1;

                if(temp_fullness <= 0){
                    party.at(i).setPartyMemberFullness(0);
                    name =  party.at(i).getPartyMemberName();
                    party.erase(party.begin() + i);
                    cout << name << "died"<<endl;

                }
                else{
                    cout<<party.at(i).getPartyMemberName()<<" lost one fullness point"<<endl;
                    party.at(i).setPartyMemberFullness(temp_fullness);
                }
            }
        }
        temp_num = ranGenerator3(2,1);

        if(temp_num == 1){
            temp_fullness = temp_player.getPlayerFullness();
            temp_fullness -= 1;
            if(temp_fullness <= 0){
                cout<<temp_player.getPlayerName()<<" died, game over!."<< endl;
                temp_player.setPlayerFullness(0);
            }
            else{
                cout<<temp_player.getPlayerName()<<" lost one fullness point"<<endl;
                temp_player.setPlayerFullness(temp_fullness);
            }
        
        }       
        return 0;
    }


    return 0;

}

/**
 * surrender(): eliminates a random member of the party, excluding the player
 * 
 * algo:
 * 1) calls the ranGenerator3 function to get a random number between zero and the number of party members -1
 * 2) eliminates the paty member whos index corresponds to the random number generated
 * 3)every party member has a 50% chance of getting their hp reduced by 1 pt
 * 
*/
void Battle::Surrender(vector<Party>& party){
    int size = 0;
    int ran_num = 0;
    string name;
    size = party.size();
    

    size -= 1;
    
    ran_num = ranGenerator3(size, 0);

    name = party.at(ran_num).getPartyMemberName();

    party.erase(party.begin()+ran_num);

    cout<<"Your party decided to surrender "<< name << " was unabele to scape the monster and was left behind."<<endl;

    //I still have to include the 50% chance of every party member loosing 1 hp, but im tired lol, ill do it tomorrow

        
    
} //also have to discuss with oscar about how we're handling the party members 