#include <iostream>
#include "Misfortune.h"
#include "Party.h"
#include "Player.h"
#include <cstdlib> 
#include <ctime>


/**
 * ranGenerator(): generates a random number between min and max 
 * 
 * algo:
 * 1) performs the computation to get the random number 
 * 2) stores value in random 
 * 
 * returns:
 * int random: random number generated
*/

int ranGenerator2(int max, int min){
    //if we want b/w min and max --> rand() % (max - min + 1) + min
    int random = 0;

    random = rand() % (max - min + 1) + min;

    return random; 
}


/**
 * computeMisfortune(): performs the misfortune actions if the 30% chance is hit
 * 
 * algo:
 * 1) calls ranGenerator
 * 2) if number is =< 30 then a misfortune occurs (sets misfortune to true)
 * 3) if misfortune is true then calls ranGenerator again
 *      1)if the number is <= 10(a random weapon/armor piece gets broken)
 *      2) if the number is >10 and <= 40 (party randomly looses 10kg of ingredients, 1 item of cookware or 1 item )
 *      3)if the number is >40 and <=70 (a random party member gets food poisoning causing it to loose 10 fullness points, dies if fullness reaches 0)
 *      4) if number is >70 and <= 99 (one party member is left behind, if )
 *      5) if number is == 100 then all of the partymembers fullness points get reduced in half
 * 4)after the misfortuens have occured it sets misfortuen back to false
 *      
 *       
 *         
 * 
 * parameters: none
 * 
 * return: none
*/
void Misfortune::computeMisfortune(Player& player, vector<Party>& party){
    int randm_num = 0, temp_fullness = 0;
    int temp = 0, robbed = 0, temp2 = 0;
    bool flag = false;
    bool no_weapons = false;
    vector <int> cookware(3);
    vector <int> weapons(5);
    int index = -1;
    int no_weapon_count = 0;
    int size = 0, count = 0;
    string name;
    vector <string> dead_party_members;
    
    

    // randm_num = (rand() % 100) + 1; //generates a random number between 1- 100

    //randm_num = ranGenerator2(100, 1);
    
    // if(randm_num <= 30){
    //     misfortune = true;
    // }

    // if(misfortune){
    randm_num = ranGenerator2(100, 1);

    if(randm_num <= 10){ 
        //breaks a random piece of armor/tools
        /**
            breks a random weapon/ armor from a random party member
        
        */
        temp = ranGenerator2(2,1);

        if(temp == 1 ){ //a random weapon will break 

            index = ranGenerator2(4,0);
            // for(int i = 0; i < 5; i++){
            //     if(player.getWeapon(i) == 0){ //checks how many weapons of each kind the party has 
            //         flag = true;
            //         no_weapon_count++;
            //     }
            // }
            // if(no_weapon_count == 5){ //party has no weapons;
            //     no_weapons = true;
            // }

            
                
                
            temp2 = player.getWeapon(index);
            temp2 -= 1;
            if(temp2 < 0){
                return;
            }
            player.setWeapon(temp2, index);

            if(index == 0){
                cout<<"Oh no, your club broke!"<<endl;
            }
            else if(index == 1){
                cout<<"Oh no, your spear broke!"<<endl;
            }
            else if(index == 2){
                cout<<"Oh no, your +1 Rapier broke!"<<endl;
            }
            else if(index == 3){
                cout<<"Oh no, your +2 battle-axe broke!"<<endl;
            }
            else if(index == 4){
                cout<<"Oh no, your +3 longsword broke!"<<endl;
            }

            
            // else if(no_weapons == false){
            //     index = ranGenerator2(4,0);

            //     temp2 = player.getWeapon(index);
            //     temp2 -= 1;
            //     player.setWeapon(temp2, index);

            //     if(index == 0){
            //         cout<<"Oh no, your club broke!"<<endl;
            //     }
            //     else if(index == 1){
            //         cout<<"Oh no, your spear broke!"<<endl;
            //     }
            //     else if(index == 2){
            //         cout<<"Oh no, your +1 Rapier broke!"<<endl;
            //     }
            //     else if(index == 3){
            //         cout<<"Oh no, your +2 battle-axe broke!"<<endl;
            //     }
            //     else if(index == 4){
            //         cout<<"Oh no, your +3 longsword broke!"<<endl;
            //     }
            // }


            
        }
        if(temp == 2){//a piece od armor will break 
            temp2 = player.getArmor();
            temp2 -= 1;
            if(temp2 < 0){
                temp2 = 0;
            }
            else{
                player.setArmor(temp2);

                cout<<"Oh no, an armor set broke"<<endl;
            }

        }
    }
    else if(randm_num > 10 && randm_num <= 40){
        //your team gets robbed
        temp = ranGenerator2(3,1);
        switch(temp){
            case 1:
                robbed = player.getIngredients();
                if(robbed == 0){//chekcs if the party has any ingredients 
                    cout<<"the bandints tried robbing your ingredients, but you don't have any!. lucky you..."<<endl;
                }
                else{
                    if(robbed - 10 < 0){ //if the party has less than 10 kg of ingredients they will be left with 0 kg, no neg values 
                        cout<<"Oh no, your party was robbed!. The bandits took "<< robbed << " kg of your ingredients."<<endl;

                        robbed = 0;

                        cout<< "You are now left with " << robbed << " kg of ingredients."<<endl;
                    }
                    else{ //substracts 10 from the party's total ingredients 
                        robbed -= 10;
                        cout<<"Oh no, your party was robbed!. The bandints took 10 kg of your ingredients."<<endl;
                        cout<<"You are now left with "<< robbed << " kg of ingredients."<<endl;
                    }

                    player.setIngredients(robbed); //sets the new value for ingredients

                    
                }
            break;
            case 2:
                for(int i = 0; i < 3; i++){
                    if(player.getCookware(i) == 0){ //checks amounts of each cookware
                        count++;
                    }
                }
                if(count == 3){ //if the party doesn't have any cookware they can't be robbed
                    cout<<"the bandints tried robbing part of your cookware, but you don't have any!. lucky you..."<<endl;
                    return;
                }

                if(flag){

                    if(count == 2){
                        for(int i = 0; i < 3; i++){
                            if(cookware.at(i) != -1){
                                index = cookware.at(i);
                            }
                        }
                    }
                    else if(count == 1){
                        for(int i = 0; i< 3; i++){
                            if(cookware.at(i) == -1){
                                cookware.erase(cookware.begin()+i);
                                index = ranGenerator2(1,0);
                            }
                        }
                    }

                }
                else{
                    index =  ranGenerator2(2,0);
                }
                robbed = player.getCookware(index);

                robbed -= 1;

                player.setCookware(robbed, index);
                if(index == 0){
                    cout<<"The bandits took 1 ceramic pot from your party, you now have  "<< robbed << " pot(s)" <<endl;
                }
                else if(index == 1){
                    cout<<"The bandits took 1 frying pan from your party, you now have  "<< robbed << " frying pan(s)" <<endl;
                }
                else if(index == 2){
                    cout<<"The bandits took 1 cauldron from your party, you now have  "<< robbed << " cauldron(s)" <<endl;
                }

                //robbed = player.getCookware();

            break;
            case 3:
                robbed = player.getArmor();

                if(robbed == 0){
                    cout<<"The bandits tried to rob some of your armor, but you don't have any, lucky you... "<<endl;
                }
                else{
                    robbed -= 1;
                    player.setArmor(robbed);
                    cout<<"Oh no, your party was robbed!. The bandints took 1 piece of armor from you."<<endl;
                    cout<<"You now have "<< robbed << " set(s) of armor"<<endl;
                }

            break;
        }
        //cout<<"oh no, your party was robbed "<<randm_num<<endl;
    }
    else if(randm_num > 40 && randm_num <= 70){
        //food poisoning
        size = party.size();
        size -= 1;

        temp = ranGenerator2(size, 0);
        temp_fullness = party.at(temp).getPartyMemberFullness();
        temp_fullness -= 10;

        if(temp_fullness < 0){
            temp_fullness = 0; //sets fullness to 0, can't have negative fullness
            party.at(temp).setPartyMemberFullness(temp_fullness);

            name = party.at(temp).getPartyMemberName();
            party.erase(party.begin() + temp);

            cout<<name<< "died of hunger"<<endl;

        }
        else{
            party.at(temp).setPartyMemberFullness(-10);
            name = party.at(temp).getPartyMemberName();

            cout<<name<< " lost 10 pints of fullness due to food poisoning."<<endl;
        }

        
    }
    else if(randm_num > 70 && randm_num <= 99){
        //team member gets locked in previous room
        size = party.size();
        size -= 1;

        temp = ranGenerator2(size, 0);

        name = party.at(temp).getPartyMemberName();
        party.erase(party.begin() + temp);
        
        cout<< name <<" is locked in the previous room!, you will continue your adventure without him " <<endl;
    }
    else if(randm_num == 100){
        //everyone's life points get reduced by half 
        temp_fullness = player.getPlayerFullness();
        temp_fullness /= 2;
        player.setPlayerFullness(temp_fullness);

        size = party.size();

        for(int i = 0; i < size; i++){
            temp_fullness = party.at(i).getPartyMemberFullness();
            temp_fullness /= 2;
            if(temp_fullness < 0){
                party.at(i).setPartyMemberFullness(0);
                name = party.at(i).getPartyMemberName();
                dead_party_members.push_back(name);
                party.erase(party.begin() + size -1);

                flag = true;
                    
            }
            else{
                party.at(i).setPartyMemberFullness(temp_fullness);
            }

        }
        cout<<"everyones hp gets reduced by half "<<endl;
        if(flag){
            size = dead_party_members.size();
            for(int i = 0; i < size; i++){
                cout<<dead_party_members.at(i);
                if(i + 1 != size){
                    cout<<", ";
                }

            }
            cout<<" died as a result of this"<<endl;
        }
    }


    //}

    //misfortune = false;

}