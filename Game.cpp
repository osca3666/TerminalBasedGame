#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <ctime>
#include <vector>
#include "Battle.h"
#include "Player.h"
#include "Party.h"
#include "Map.h"
#include "Misfortune.h"
#include "Game.h"
#include "Npc.h"
#include "Sort.h"

using namespace std;

void displaytitle(string file){
    string input;
    string line;
    ifstream fin(file);
    while(getline(fin, line)){
        cout<<line<<endl;
    }
    cout<<"Press any key to continue:"<<endl;
    getline(cin, input);
}

int ranGenerator(int min, int max){
    //if we want b/w min and max --> rand() % (max - min + 1) + min
    int random = 0;

    random = rand() % (max - min + 1) + min;

    return random; 
}


int split(string input_string, char separator, string arr[], int arr_size)
{
    //separator not found
    int input_string_len = input_string.length();
    if (input_string_len == 0) // if input string is empty
    {
        return 0;
    }


    string placeholder_string = "";
    int arr_index = 0;

    for (int i = 0;i < input_string_len;i++) //traverse the array
    {
            if (input_string[i] == separator) 
            {
                arr[arr_index] = placeholder_string; //store string prior to seperator into array 
                arr_index++;
                placeholder_string = ""; //empty it
            }
            else 
            {
                placeholder_string += input_string[i]; //when a separator is not encountered, extend the placeholder string by adding the new character
            }
    }
    arr[arr_index] = placeholder_string; //adding the last part past the last separator
    
    if (arr_index > arr_size - 1) //string is split into more pieces than the size of the array
    {
        return -1;
    }


    if (arr_index == 0) //seperator was not found
    {
        arr[arr_index] = input_string;
        return 1;
    }
    return arr_index + 1;
}

int RPC(){ //RPC stands for Boulder Parchment Spear. "Will return 1 if player wins, 2 if player looses and 3 if player ties 3 times"
    int user_move, number = 0;
    char user_decision;
    int ran_num = 0, tie_counter = 0;
    int first_time = 0;
    int game_outcome = 0, remaining = 3;

    if(number == 0){
        number = 1;
        cout<<"Door guardian: It looks like you don't have a key to unlock the door....."<<endl;
        cout<<"Luckily for you, there is another way you can get the door behind me open."<<endl;
        cout<<"If you beat me in a Boulder Parchment Spear game, I'll let you through"<<endl;
        cout<<"But, remember.... If you lose or there is no winner after 3 games, one of your party members will die."<<endl;
    
        do{
            cout<<"Are you up to the challenge?: (y/n)"<<endl;
            cin >> user_decision;
        }while(user_decision != 'y' && user_decision != 'n' && user_decision != 'Y' && user_decision != 'N');
    }

    if(user_decision == 'y' || user_decision == 'Y' && number > 0){
        
        cout<<"Perfect, shall the game begin!"<<endl;
        
        while(tie_counter != 3){
            cout<<"Make your move:"<<endl;
            cout<<"1) Boulder"<<endl;
            cout<<"2) Parchment"<<endl;
            cout<<"3) Shears"<<endl;
            cin >> user_move;
            while(user_move < 0 && user_move > 4){
                cout<<"Stop fooling arounnd...."<<endl;
                cout<<"Select a valid move"<<endl;
                cin >> user_move;
            }
            ran_num = ranGenerator(1,3);
            if(user_move == 1 ){ //migth need to ad number != 4; player chooses Boulder
                if(ran_num == 1){//oponent chooses boulder 
                    tie_counter++;
                    cout<<"Door guardian chose boulder, the game tied"<<endl;
                    cout<<"remaining attempts"<<remaining - tie_counter<<endl;

                    
                    if(tie_counter == 3){
                        game_outcome = 3;
                        return game_outcome;
                    }
                    //return RPC(number);
                }
                else if(ran_num == 2){ //looses the game, oponent chooses parchment
                    cout<<"Door guardian chose parchment, you lose."<<endl;
                    game_outcome = 2;
                    return game_outcome;
                }
                else if(ran_num == 3){ //wins the game, oponent chooses shears
                    cout<<"Door guardian chose shears, you won."<<endl;
                    game_outcome = 1;
                    return game_outcome;
                }
            }
            else if(user_move == 2 ){ //player chooses Parchment

                if(ran_num == 1){ //wins the game, oponent chooses boulder
                    cout<<"Door guardian chose shears, you won."<<endl; 
                    game_outcome = 1;

                    return game_outcome;
                }
                else if(ran_num == 2){ //ties the game, oponent chooses parchment 
                    tie_counter++;
                    cout<<"Door guardian chose parchment, the game tied"<<endl;
                    cout<<"remaining attempts"<<remaining - tie_counter<<endl;
                    
                    if(tie_counter == 3){
                        game_outcome = 3;
                        return game_outcome;
                    }
                    //return RPC(number);
                }
                else if(ran_num == 3){ //looses the game, oponent looses shears
                    cout<<"Door guardian chose parchment, you lose."<<endl;
                    game_outcome = 2;
                    return game_outcome;
                }

            }
            else if(user_move == 3){ //player chooses shears
                if(ran_num == 1){ //looses the game, oponent chooses boulder
                    cout<<"Door guardian chose parchment, you lose."<<endl;
                    game_outcome = 2;

                    return game_outcome;
                }
                else if(ran_num == 2){ //wins the game, oponent chooses parchment
                    cout<<"Door guardian chose shears, you won."<<endl;
                    game_outcome = 1;
                    return game_outcome; 
                }
                else if(ran_num == 3){ //ties the game, oponent chooses shears 
                    tie_counter++;
                    cout<<"Door guardian chose shears, the game tied"<<endl;
                    cout<<"remaining attempts"<<remaining - tie_counter<<endl;
                    
                    if(tie_counter == 3){
                        game_outcome = 3;
                        return game_outcome;
                    }
                    //return RPC(number);
                }
            }
        }
        
    }
    else if(user_decision == 'n' || user_decision == 'N'){
        cout<<"I see.... your choise."<<endl;
    }
    return game_outcome;

}



/*Game algorithm:
    1. Define all the objects and create their default constructors
    2. Print to user what their name is and the name of their party members
    3. Display merchant menu
    4. Display map
    5. While game_over = false,
        Show user their options:
            1. Move
                a. move to new location
                b. calculate number generator because every party member has a 20% chance of their hunger dropping
                c. if its an unexplored area, sorceror anger increases by 1
            2. Investigate
                a. if space already investigated
                    -end move
                b. else space not already investigated
                    -10% chance of finding key
                    -20% chance of finding treasure
                    -20% chance to fight monster
                        -go into option 3 
                    -50% chance everyone's fullness drops by 1 pt
            3. Pick a fight
                a. if no weapon, only option is to surrender
                b. if weapon, they can fight or surrender
                    - if player surrendered
                        = one random party member excluding player is trapped and dies
                    - if monster defeated
                        = add 10 * c gold (c=challenge rating)
                        = add 5 * c ingredients 
                        = 10% chance monster drops key
                        -monster is removed from the monster list
                    - else monster not defeated
                        = player loses a quarter of their gold reserve rounded downt ot he nearest int
                        = they lose upto 30kg of ingredients
                        = each party member excluding player independantly has 10% chance of being slain, 5% if wearing armor
                            -print message if party member dies

                c. regardless of result, every party member's fullness has 50% chance to lose

            4. Cook and eat
                a. use for loop to calculate total amount of cookware
                    -if 0, exit 
                b. if ingrdients is more than or equal to 5
                    -continue
                    -else exit
                a. calculate random number between 1 and 100 to find if cookware broke
                    if cookware broke, reduce cookware in inventory
                    else update hunger by dividing ingredients by 5 and adding that to previous hunger
                b. update ingredient amount
            5. Give up
                a. change the boolean game_over to true
                ***GAME ENDS***       
*/

void Game::runGame()
{
    displaytitle("title.txt");
    //Phase 1:
    Player player; 
    player.resetPlayer();
    Map map;
    vector<Party> party(4); //player's 4 companions
    party.at(0).resetParty();
    party.at(1).resetParty();
    party.at(2).resetParty();
    party.at(3).resetParty();

    Npc npc;
    Battle battle;
    Misfortune misfortune;

    string player_name_;
    string companion_1;
    string companion_2;
    string companion_3;
    string companion_4;

    int randomX; //coordinates for map item generation (room,npc, etc.)
    int randomY; 

    int user_choice;
    string user_choice_string;
    char move_choice;
    int cookware_choice;
    int ingredient_choice;
    int rounds_taken = 0;
    
    int rpc_result;
    string name;
    int size = 0, temp = 0;
    bool game_over = false;

    cout<<"> Hello young one. What is your name?"<<endl;
    cin>>player_name_;
    player.setPlayerName(player_name_);
    cout<<"> What are the names of your 4 companions?"<<endl;
    cin>>companion_1;
    cin>>companion_2;
    cin>>companion_3;
    cin>>companion_4;
    party.at(0).setPartyMemberName(companion_1);
    party.at(1).setPartyMemberName(companion_2);
    party.at(2).setPartyMemberName(companion_3);
    party.at(3).setPartyMemberName(companion_4);
    cout<<"> Here is a book to track your progress through the dungeon"<<endl;
    player.displayStatus(party); //have to set weapon maximum to 5 total
    cout<<"> You seem to have some gold. I can aid you with equipments for the journey ..."<<endl;
    npc.displayRiddle("riddles.txt");
    player = npc.displayMenu(player,party);
    cout<<"> Break a leg! Should fate favor you, you may find my cousins in the dungeon later who also sell valuable goods"<<endl;
    cout<<"> Wait!!"<<endl;
    cout<<"> I forgot to give you a map. Here ya go. Now peace!"<<endl;
    while (map.getRoomCount() < 5) //generate 5 rooms in random locations
    {
        randomX = ranGenerator(1,12);
        randomY = ranGenerator(1,12);
        map.addRoom(randomX,randomY);
    }
    while (map.getNPCCount() < 5) //generate 5 merchants in random locations
    {
        randomX = ranGenerator(1,12);
        randomY = ranGenerator(1,12);
        map.addNPC(randomX,randomY);
    }
    battle.setMosterLevel("Monsters.txt");
    string monster_name;



    //Phase 2:
    while (!game_over)
    {
        player.displayStatus(party); //show status
        map.displayMap();            //show map
        user_choice = -1;


        while(!(user_choice >=1 && user_choice <= 5)) //user choice to move, investigate, fight, cook, give up
        {
            cout<<"What should we do?"<<endl<<"1. Move"<<endl<<"2. Investigate"<<endl<<"3. Pick a Fight"<<endl<<"4. Cook and Eat"<<endl<<"5. Give Up"<<endl;
            cin>>user_choice_string;
            bool is_digit = true;

            for (int i = 0; i < user_choice_string.length();i++)
            {
                if (isdigit(user_choice_string[i]) == false)
                {
                    is_digit = false;
                }
            }

            if (is_digit == true)
            {
            user_choice = stoi(user_choice_string);
            switch(user_choice)
            {
                case 1: //move
                {
                    cin>>move_choice;
                    while (!(map.move(move_choice))) //checks if valid move location
                    {
                        cout<<"Invalid choice. Use w,a,s,d to move."<<endl;
                        cin>>move_choice;
                    }
                    if (!(map.isExplored(map.getPlayerRow(), map.getPlayerCol()))) //if unexplored area, anger level increases by 1
                    {
                        player.increaseAngerLevel();
                        if (player.getAngerLevel() == 85) //just a warning
                        {
                            cout<<player.getPlayerName()<<" did you hear that? I think the sorceror is getting real mad. We have to be quick!"<<endl;
                        }
                        if (player.getAngerLevel() == 100) // game ending condition reached
                        {
                            game_over = true;
                        }
                    }
                    randomX = ranGenerator(1,100);
                    if (randomX >= 1 && randomX <= 20) //every party member has a 20% chance of their hunger dropping
                    {
                        player.setPlayerFullness(-1);
                    }
                    for (int i = 0; i < party.size();i++) //every party member has a 20% chance of their hunger dropping
                    {
                        randomX = ranGenerator(1,100);
                        if (randomX >= 1 && randomX <= 20)
                        {
                            party.at(i).setPartyMemberFullness(-1);
                        }
                    }
                    break;
                }
                // case 2:
                // a. space already investigated?
                //     -end move
                // b. space not already investigated?
                //     -10% chance of finding key
                //     -20% chance of finding treasure
                //     -20% chance to fight monster
                //         -go into option 3 
                //     -50% chance everyone's fullness drops by 1 pt
                case 2: //investigate
                {
                    if (map.isExplored(map.getPlayerRow(), map.getPlayerCol()))
                    {
                        cout<<"You already explored this area."<<endl;
                        user_choice = -2; //so the choices are given again
                        break; //if already explored area, give user the choices again
                    }
                    else //area has not already been explored
                    {
                        map.exploreSpace(map.getPlayerRow(), map.getPlayerCol()); //mark area as explored

                        randomX = ranGenerator(1,100);
                        if (randomX >= 1 && randomX <= 10) //10% chance of finding key
                        {
                            player.setKeysFound(player.getKeysFound() + 1);
                        }
                        else if (randomX >= 11 && randomX <= 30) //20% chance of finding treasure
                        {
                            if (player.getRoomsCleared() == 5)
                            {
                                cout<<"You found a Gem-encrusted goblet!"<<endl;                                   
                                player.setTreasures(player.getTreasures(4) + 1,4); 
                            }
                            else
                            {
                                if (player.getRoomsCleared() == 0)
                                {
                                    cout<<"You found a Silver ring!"<<endl;
                                }
                                else if (player.getRoomsCleared() == 1)
                                {
                                    cout<<"You found a Ruby necklace!"<<endl;
                                }
                                else if (player.getRoomsCleared() == 2)
                                {
                                    cout<<"You found a Emerald bracelet!"<<endl;
                                }
                                else if (player.getRoomsCleared() == 3)
                                {
                                    cout<<"You found a Diamond circlet!"<<endl;
                                }
                                else if (player.getRoomsCleared() == 4)
                                {
                                    cout<<"You found a Gem-encrusted goblet!"<<endl;
                                }
                                player.setTreasures(player.getTreasures(player.getRoomsCleared()) + 1,player.getRoomsCleared()); 
                            }
                        }
                        else if (randomX >= 31 && randomX <= 50) //20% chance of fighting monster
                        {
                            monster_name = battle.getMosterLevel(player.getRoomsCleared());
                        }
                        else if (randomX >= 51 && randomX <= 100) //50% chance everyone's fullness drops by 1 pt
                        {
                            cout<<"You found nothing. Just hunger."<<endl;
                            player.setPlayerFullness(-1);
                            for (int i = 0; i < party.size();i++) 
                            {
                                    party.at(i).setPartyMemberFullness(-1);

                            }
                        }  
                        
                        randomX = ranGenerator(1,100);
                        if(randomX >= 1 && randomX <= 40)
                        {
                            misfortune.computeMisfortune(player, party);
                        }              
                    }
                    break;
                }
                case 3: //pick a fight
                {
                    if (player.getWeaponAmount(party) == 0)
                    {
                        user_choice = -2; //so the choices are given again
                        break;
                        cout<<"What are you gonna do? Use your hands? Lets go get a weapon to fight!"<<endl;
                    }
                    else
                    {
                        monster_name = battle.getMosterLevel(player.getRoomsCleared()+1);
                        battle.Figth(player,player.getRoomsCleared()+1,party,monster_name);
                        user_choice = -2; //so the choices are given again
                        break;
                    }
                    break;
                }
                case 4: //cook and eat
                {
                    int cookware_amount = 0;
                    for (int i = 0;i < 3;i++) //count how much cookware the player has
                    {
                        cookware_amount += player.getCookware(i);
                    }
                    if (cookware_amount = 0)
                    {
                        cout<<"You have no cookware to make food."<<endl;
                        user_choice = -2; break;
                    }
                    if (player.getIngredients() <= 5)
                    {
                        cout<<"You don't have enough ingredients to make food."<<endl;
                        user_choice = -2; break;
                    }
                    else
                    {
                        cookware_choice = -1;
                        ingredient_choice = -1;
                        cout<<"Which cookware should we use: "<<endl<<"1. Ceramic Pot: "<<player.getCookware(0)<<endl<<"2. Frying Pan: "<<player.getCookware(1)<<endl<<"3. Cauldron: "<<player.getCookware(2)<<endl;
                        cin>>cookware_choice;
                        while (player.getCookware(cookware_choice - 1) <= 0) //user chooses which cookware to use
                        {
                            cout<<"You don't have enough of that"<<endl;
                            cout<<"Which cookware should we use: "<<"1. Ceramic Pot: "<<player.getCookware(0)<<endl<<"2. Frying Pan: "<<player.getCookware(1)<<endl<<"3. Cauldron: "<<player.getCookware(2)<<endl;
                            cin>>cookware_choice;  
                        }
                        while (ingredient_choice < 5) //user chooses how much ingredient to cook
                        {
                            cout<<"How much ingredient do you wish to cook? 5 kg can feed a group. You have "<<player.getIngredients()<<" kg of ingredients."<<endl;
                            cin>>ingredient_choice;
                        }
                        
                        randomX = ranGenerator(1,100); // to check if cookware broke during cooking
                        if (cookware_choice == 1 && randomX >= 1 && randomX <= 25)
                        {
                            cout<<"Your Ceramic Pot broke while cooking! No food for you."<<endl;
                            player.setCookware(player.getCookware(cookware_choice - 1) - 1,cookware_choice - 1); //get rid of the cookware from the inventory
                            player.setIngredients(player.getIngredients() - ingredient_choice); //get rid of the ruined ingredients
                        }
                        else if (cookware_choice == 2 && randomX >= 1 && randomX <= 10)
                        {
                            cout<<"Your Frying Pan broke while cooking! No food for you."<<endl;
                            player.setCookware(player.getCookware(cookware_choice - 1) - 1,cookware_choice - 1); //get rid of the cookware from the inventory
                            player.setIngredients(player.getIngredients() - ingredient_choice); //get rid of the ruined ingredients
                        }
                        else if (cookware_choice == 3 && randomX >= 1 && randomX <= 2)
                        {
                            cout<<"Your Cauldron broke while cooking! No food for you."<<endl;
                            player.setCookware(player.getCookware(cookware_choice - 1) - 1,cookware_choice - 1); //get rid of the cookware from the inventory
                            player.setIngredients(player.getIngredients() - ingredient_choice); //get rid of the ruined ingredients
                        }
                        else //food cooked sucessfully
                        {
                            player.setPlayerFullness(ingredient_choice / 5);
                            for (int i = 0; i < party.size();i++) //every party member has a 20% chance of their hunger dropping
                            {
                                randomX = ranGenerator(1,100);
                                if (randomX >= 1 && randomX <= 20)
                                {
                                    party.at(i).setPartyMemberFullness(ingredient_choice % 5); //increase 
                                }
                            }  
                        }
                        randomX = ranGenerator(1,100);
                        if(randomX >= 1 && randomX <= 40)
                        {
                            misfortune.computeMisfortune(player, party);
                        }              
                    }
                    break;
                }
                case 5: //give up
                {
                    cout<<"Okay. Play again anytime :)"<<endl;
                    game_over = true; break;
                }
                default: cout<<"Invalid choice"<<endl;
            }
            rounds_taken++;
            }
            else
            {
                cout<<"Invalid choice"<<endl;
            }
        }

        if (!game_over) //check player position for what to do next
        {
            if (map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol())) //if merchant, display menu. remove merchant once player is done
            {
                cout<<"> Hello travelers, what can I get you?"<<endl;
                if (npc.displayRiddle("riddles.txt") == 1) //answered riddle correctly
                {
                    player = npc.displayMenu(player, party); //display merchant menu
                }
                else
                {
                    cout<<"I don't sell stuff to dummies."<<endl;
                }
                map.removeNPC(map.getPlayerRow(), map.getPlayerCol()); //map.move automatically marks NPC location as explored
            }
            else if (map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol())) //if room, fight monster boss
            {

                if (player.getKeysFound() >= 1) //if player has room keys
                {
                    monster_name = battle.getMosterLevel(player.getRoomsCleared()+2);
                    //battle.Figth(player,player.getRoomsCleared()+2,party,monster_name);
                    if (battle.Figth(player,player.getRoomsCleared()+2,party,monster_name) == true) //room battle won
                    {
                        player.increaseRoomsCleared();
                        map.removeRoom(map.getPlayerRow(), map.getPlayerCol());
                        randomX = ranGenerator(1,100);
                        if(randomX >= 1 && randomX <= 60){
                            misfortune.computeMisfortune(player, party);
                        }
                    }
                    else //lost battle in room
                    {
                        randomX = ranGenerator(1,100);
                        if(randomX >= 1 && randomX <= 40){
                            misfortune.computeMisfortune(player, party);
                        }
                        player.setKeysFound(player.getKeysFound() - 1);
                    }
                }
                else
                {
                    rpc_result = RPC();
                    if (rpc_result == 1) //win
                    {
                        monster_name = battle.getMosterLevel(player.getRoomsCleared()+2);
                        if (battle.Figth(player,player.getRoomsCleared()+2,party,monster_name) == true) //room battle won
                        {
                            player.increaseRoomsCleared();
                            map.removeRoom(map.getPlayerRow(), map.getPlayerCol());
                            randomX = ranGenerator(1,100);
                            if(randomX >= 1 && randomX <= 60){
                                misfortune.computeMisfortune(player, party);
                            }
                        }
                        else //lost battle in room
                        {
                            randomX = ranGenerator(1,100);
                            if(randomX >= 1 && randomX <= 40){
                                misfortune.computeMisfortune(player, party);
                            }
                            player.setKeysFound(player.getKeysFound() - 1);
                        }
                    }
                    else if (rpc_result == 2 || rpc_result == 3) //loss or tie 3 tiesm
                    {
                        //random member death 
                        size = party.size() - 1;
                        temp = ranGenerator(0,size);

                        name = party.at(temp).getPartyMemberName();
                        party.erase(party.begin() + temp);

                        cout<<"Door guardian: don't say, I didn't warn you..... "<<name<< " is in a better place now."<<endl;
                        
                    }
                }
            }
            else if (map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol()) && player.getRoomsCleared() == 5) //game ends if player has reached end and has cleared all boss rooms
            {
                cout<<"You have escaped this hellish dungeon with your companions. Make the most of your life."<<endl;
                game_over = true; 
                break;
            }
            else if (map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol()) && player.getRoomsCleared() < 5) //game ends if player has reached end and has cleared all boss rooms
            {
                cout<<"You haven't cleared all rooms yet. Go back!"<<endl;
            }


            if (player.getPlayerFullness() <= 0) //if player has died from hunger: game over!
            {
                cout<<"You have died from starvation."<<endl<<"May you have more food in your next life"<<endl;
                game_over = true;
            }
            for (int i = 0; i < party.size();i++) //checks if any party member is dead from hunger
            {
                if (party.at(i).getPartyMemberFullness() <= 0)
                {
                    cout<<"Oh no! "<<party.at(i).getPartyMemberName()<<" has passed away from starvation!"<<endl<<"Your party size has been reduced to "<<party.size()<<" members."<<endl;
                    //need to update party object by removing dead player
                    int temp_id = i;
                    for (int i = temp_id; i < party.size()-1;i++)
                    {
                        party.at(i) = party.at(i+1);
                    }
                    party.pop_back(); //remove the last one cause there is 2 of them
                }
            }
            //checks if only player is left: game over
            if (party.size() == 0)
            {
                cout<<"All your companions have died and you lose the will to continue."<<endl<<"May you have better company in your next life"<<endl;
                game_over = true;
            }

            if (player.getPlayerFullness() <= 10) //low fullness warning- player
            {
                cout<<"Warning: you are on the brink of starvation!"<<endl<<"You should cook and eat some food!"<<endl;
            }
    
            for (int i = 0; i < party.size();i++) //low fullness warning- party member
            {
                if (party.at(i).getPartyMemberFullness() <= 10)
                {
                    cout<<"Warning: "<<party.at(i).getPartyMemberName()<<" is on the brink of starvation!"<<endl<<"You should cook and eat some food!"<<endl;
                }
            }

        }
        
    }
    //put sorting algortihm there
    //1. read text file to see the top 5 scores
    //2. compare the turns taken in this game to the top 5 from the text file
    //3. if new score is lower than any of them, put it in the right spot
    //4. compare current run to vector. 

    //this writes the current score to the file
    // ofstream myfile;
    // myfile.open ("high_scores.txt");
    // myfile << player.getPlayerName()<<","<<rounds_taken;
    // myfile.close();

    ofstream myfile;
    myfile.open ("high_scores.txt",std::ios_base::app);
    myfile << endl<<player.getPlayerName()<<","<<rounds_taken;
    myfile.close();


    ifstream fin;
    fin.open("high_scores.txt");
    string line;
    string line_components[2]; //size = 51 b/c max posts is 50 + 1 username 
    string high_score_table[5];
    
    int linecount = 0;
    int split_result = 0;
    int num_likes = 0;
    string username;
    int index = 0; 
    if (fin.fail()) //file doesn't open
    {
    }
    else //file does open
    {
        while (!fin.eof()){
            getline(fin,line);
            linecount++;
        }
        fin.close();

        vector <Sort> unsorted(linecount);
        fin.open("high_scores.txt");
        while (getline(fin,line)) // when equal, there is no more space to input so exit loop
        {
            

            split_result = split(line,',',line_components,2); // {Leonardo, 1222}
            if(index <= linecount){
                unsorted.at(index).setName(line_components[0]);
                num_likes = stoi(line_components[1]);
                unsorted.at(index).setScore(num_likes);
            }
            index++;
            
        }
        for(int i = 0; i < unsorted.size(); i++){
            for(int j = 0; j < unsorted.size(); j++){
                if(unsorted[i].getScore() < unsorted[j].getScore()){
                    int temp_score = unsorted.at(j).getScore();
                    string temp_name = unsorted.at(j).getName();
                    unsorted.at(j).setName(unsorted.at(i).getName());
                    unsorted.at(j).setScore(unsorted.at(i).getScore());

                    unsorted.at(i).setName(temp_name);
                    unsorted.at(i).setScore(temp_score);
                }
            
            }
        }
        cout<<"=====Score ranking====="<<endl;
        int top = 1;
        for(int i = 0; i < 5; i++){
            cout<<top<<") "<<unsorted.at(i).getName()<<", "<<unsorted.at(i).getScore()<<endl;
            top++;
        }
        cout<<"======================"<<endl;

        fin.close();
    }

    

}



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
        b. every party member has a 20% chance of their hunger dropping
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