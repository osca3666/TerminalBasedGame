#include <iostream>
#include <fstream>
#include "Npc.h"
#include "Player.h"
#include "Party.h"

using namespace std;


int ranGenerator5(int min, int max){
    //if we want b/w min and max --> rand() % (max - min + 1) + min
    int random = 0;

    random = rand() % (max - min + 1) + min;

    return random; 
}



/*
    Algorithm in NPC:
    1. Create a loop that only terminates if user choice is 6 which is to exit the menu
    2. The choices are: 1. weapon, 2. armour, 3. ingredients, 4. cookware, 5. sell treasures, 6. and exit
    3. Use a switch statement for these options so it is easier to read
    4. For weapon:
        a. check if maximum weapons already reached
    5. For armour
        a. check if maximum armor already met, if so exit
        b. if maximum armor not met, print how many they want
        c. if how many they want added to existing armor is more than max, print error
        d. if they can't afford it print error
        e. if they can afford it, print an are you sure?
        f. update armour count if bought sucessfully
    6. For ingredients
        a. print how much they want
        b. if valid input, see if they can afford it, if not, print error
        c. if they can afford it, print an are you sure statement
        d. update ingredients if bought sucessfully
    7. For cookware
        a. print what they want
        b. print how many of the item they want 
        c. if valid input, see if they can afford it
        d. if they can afford it, print are you sure statement
        e. update ingredients if boought sucessfullly

*/

int split2(string input_string, char separator, string arr[], int arr_size)
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


Player Npc::displayMenu(Player player,vector <Party> party) //add a loot crate option??
{
    string user_menu_choice;
    int user_menu_choice_integer = -1;
    int weapon_choice = -1;
    int cookware_choice = -1;
    int treasure_choice = -1;
    int temp_weapon_amount = 0;
    int weaponY = 0;

    int amount = -1; //amount of item user wants
    char yes_no_choice = 'a';
    double mult = 1 + 0.25 * player.getRoomsCleared();

    while (user_menu_choice_integer != 6)
    {
        cout<<"======Main Menu====="<<endl<<"1. Weapons"<<endl<<"2. Armour"<<endl<<"3. Ingredients"<<endl<<"4. Cookware"<<endl<<"5. Sell treasures"<<endl<<"6. peace brotha"<<endl;
        cin>>user_menu_choice;
        bool is_digit = true;

        if (isdigit(user_menu_choice[0]) == false)
        {
            is_digit = false;
        }
        if (is_digit == true)
        {
            user_menu_choice_integer = stoi (user_menu_choice);

            switch (user_menu_choice_integer)
            {
                case 1: //Option 1: Weapon choice
                {
                    amount =-1; //amount of item user wants
                    cout<<"> The best companion is a trusty weapon. What would you like? Only one per person!"<<endl<< "Choose one of the following:"<<endl<<"1. Stone Club [2 Gold]"<<endl<<"2. Iron Spear [2 Gold]"<<endl<<"3. (+1) Mythril Rapier [5 Gold]"<<endl<<"4. (+2) Flaming Battle-Axe [15 Gold]"<<endl<<"5. (+3) Vorpal Longsword [50 Gold]"<<endl<<"6. Cancel"<<endl;
                    cin>>weapon_choice;
                    for (int i = 0; i < party.size() + 1; i++)
                    {
                        weaponY += player.getWeapon(i);
                    }
                    if (weaponY >= party.size() + 1) //checks if maxed weapon amount
                    {
                        cout<<"> Your party already has the max number of weapons. Choose something else!"<<endl;
                        user_menu_choice_integer = -2;
                    }
                    else
                    {
                        switch (weapon_choice)
                        {
                            case 1: //  1. Stone Club [2 Gold]
                            {
                                while (amount < 0)
                                {
                                    cout<<"> How many would you like? (Enter a positive integer, or 0 to cancel)"<<endl;     // 1. Stone Club [2 Gold]
                                    cin>> amount;
                                    if (amount == 0) //0 to cancel
                                    {
                                        break;
                                    }
                                    if (amount * 2 * mult > player.getGold()) //meaning plyr can't afford it
                                    {
                                        cout<<"> Not enough gold! Choose another quantity"<<endl;
                                        amount = -1; //so that the while loop continues
                                    }
                                    if (amount + weaponY > party.size() + 1) // checks if player wants more weapons than the maximum
                                    {
                                        cout<<"> You can't have more than one weapon per person"<<endl;
                                        amount = -1;
                                    }
                                }

                                
                                if (amount == 0) //0 to cancel
                                {
                                    break;
                                }

                                yes_no_choice = 'a';
                                while (yes_no_choice != 'y' && yes_no_choice != 'n')
                                {
                                    cout<<"> You want to buy " <<amount <<" Stone Club for "<<amount * 2 * mult<<" Gold? (y/n)"<<endl;
                                    cin>>yes_no_choice;
                                }
                                if (yes_no_choice == 'y')
                                {
                                        int gold_new = player.getGold() - amount * 2 * mult;
                                        int new_weapon_amount = player.getWeapon(0) + amount;

                                        player.setGold(gold_new);  // update plyr gold
                                        player.setWeapon(new_weapon_amount,0);  // update plyr weapons inventory by adding weapon

                                }
                                else
                                {
                                    cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                                }

                                break;
                            }
                            case 2: //  2. Iron Spear [2 Gold]
                            {
                                while (amount < 0)
                                {
                                    cout<<"> How many would you like? (Enter a positive integer, or 0 to cancel)"<<endl;     // 1. Stone Club [2 Gold]
                                    cin>> amount;
                                    if (amount == 0) //0 to cancel
                                    {
                                        break;
                                    }
                                    if (amount * 2 * mult > player.getGold()) //meaning plyr can't afford it
                                    {
                                        cout<<"> Not enough gold! Choose another quantity"<<endl;
                                        amount = -1; //so that the while loop continues
                                    }
                                    if (amount + weaponY > party.size() + 1) // checks if player wants more weapons than the maximum
                                    {
                                        cout<<"> You can't have more than one weapon per person"<<endl;
                                        amount = -1;
                                    }
                                }
                                if (amount == 0) //0 to cancel
                                {
                                    break;
                                }                    
                                yes_no_choice = 'a';
                                while (yes_no_choice != 'y' && yes_no_choice != 'n')
                                {
                                    cout<<"> You want to buy " <<amount <<" Iron Spear for "<<amount * 2 * mult<<" Gold? (y/n)"<<endl;
                                    cin>>yes_no_choice;
                                }
                                if (yes_no_choice == 'y')
                                {
                                        int gold_new = player.getGold() - amount * 2 * mult;
                                        int new_weapon_amount = player.getWeapon(1) + amount;

                                        player.setGold(gold_new);  // update plyr gold
                                        player.setWeapon(new_weapon_amount,1);  // update plyr weapons inventory by adding weapon
                                }
                                else
                                {
                                    cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                                }    

                                break;
                            }
                            case 3: // 3. (+1) Mythril Rapier [5 Gold]
                            {

                                    while (amount < 0)
                                    {

                                        cout<<"> How many would you like? (Enter a positive integer, or 0 to cancel)"<<endl;     // 1. Stone Club [2 Gold]
                                        cin>> amount;
                                        if (amount == 0) //0 to cancel
                                        {
                                            break;
                                        }
                                        if (amount * 5 * mult > player.getGold()) //meaning plyr can't afford it
                                        {
                                            cout<<"> Not enough gold! Choose another quantity"<<endl;
                                            amount = -1; //so that the while loop continues
                                        }
                                        if (amount + weaponY > party.size() + 1) // checks if player wants more weapons than the maximum
                                        {
                                            cout<<"> You can't have more than one weapon per person"<<endl;
                                            amount = -1;
                                        }
                                    }
                                    if (amount == 0) //0 to cancel
                                    {
                                        break;
                                    } 
                                    yes_no_choice = 'a';
                                    while (yes_no_choice != 'y' && yes_no_choice != 'n')
                                    {
                                        cout<<"> You want to buy " <<amount <<" (+1) Mythril Rapier for "<<amount * 5 * mult<<" Gold? (y/n)"<<endl;
                                        cin>>yes_no_choice;
                                    }
                                    if (yes_no_choice == 'y')
                                    {
                                            int gold_new = player.getGold() - amount * 5 * mult;
                                            int new_weapon_amount = player.getWeapon(2) + amount;

                                            player.setGold(gold_new);  // update plyr gold
                                            player.setWeapon(new_weapon_amount,2);  // update plyr weapons inventory by adding weapon
                                    }
                                    else
                                    {
                                        cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                                    }    
                                
                                break;
                            }
                            case 4: // 4. (+2) Flaming Battle-Axe [15 Gold]
                            {
                                while (amount < 0)
                                {
                                    cout<<"> How many would you like? (Enter a positive integer, or 0 to cancel)"<<endl;     // 1. Stone Club [2 Gold]
                                    cin>> amount;
                                    if (amount == 0) //0 to cancel
                                    {
                                        break;
                                    }
                                    if (amount * 15 * mult > player.getGold()) //meaning plyr can't afford it
                                    {
                                        cout<<"> Not enough gold! Choose another quantity"<<endl;
                                        amount = -1; //so that the while loop continues
                                    }
                                    if (amount + weaponY > party.size() + 1) // checks if player wants more weapons than the maximum
                                    {
                                        cout<<"> You can't have more than one weapon per person"<<endl;
                                        amount = -1;
                                    }
                                }
                                if (amount == 0) //0 to cancel
                                {
                                    break;
                                } 
                                yes_no_choice = 'a';
                                while (yes_no_choice != 'y' && yes_no_choice != 'n')
                                {
                                    cout<<"> You want to buy " <<amount <<" (+2) Flaming Battle-Axe "<<amount * 15 * mult<<" Gold? (y/n)"<<endl;
                                    cin>>yes_no_choice;
                                }
                                if (yes_no_choice == 'y')
                                {
                                        int gold_new = player.getGold() - amount * 15 * mult;
                                        int new_weapon_amount = player.getWeapon(3) + amount;

                                        player.setGold(gold_new);  // update plyr gold
                                        player.setWeapon(new_weapon_amount,3);  // update plyr weapons inventory by adding weapon
                                }
                                else
                                {
                                    cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                                }    

                                break;
                            }
                            case 5: // 5. (+3) Vorpal Longsword [50 Gold]
                            {
                                while (amount < 0)
                                {
                                    cout<<"> How many would you like? (Enter a positive integer, or 0 to cancel)"<<endl;     // 1. Stone Club [2 Gold]
                                    cin>> amount;
                                    if (amount == 0) //0 to cancel
                                    {
                                        break;
                                    }
                                    if (amount * 50 * mult > player.getGold()) //meaning plyr can't afford it
                                    {
                                        cout<<"> Not enough gold! Choose another quantity"<<endl;
                                        amount = -1; //so that the while loop continues
                                    }
                                        if (amount + weaponY > party.size() + 1) // checks if player wants more weapons than the maximum
                                    {
                                        cout<<"> You can't have more than one weapon per person"<<endl;
                                        amount = -1;
                                    }
                                }
                                if (amount == 0) //0 to cancel
                                {
                                    break;
                                } 
                                yes_no_choice = 'a';
                                while (yes_no_choice != 'y' && yes_no_choice != 'n')
                                {
                                    cout<<"> You want to buy " <<amount<<" (+3) Vorpal Longsword "<<amount * 50 * mult<<" Gold? (y/n)"<<endl;
                                    cin>>yes_no_choice;
                                }
                                if (yes_no_choice == 'y')
                                {
                                        int gold_new = player.getGold() - amount * 50 * mult;
                                        int new_weapon_amount = player.getWeapon(4) + amount;

                                        player.setGold(gold_new);  // update plyr gold
                                        player.setWeapon(new_weapon_amount,4);  // update plyr weapons inventory by adding weapon
                                }
                                else
                                {
                                    cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                                }    

                                break;
                            }
                            case 6: // 6. Cancel
                            {
                                cout<<"> Good bye!"<<endl;
                                break;
                            }
                            default: cout<<"> That was not a choice I gave you"<<endl;break;
                        }
                    }
                    break;
                }
                case 2: //Option 2: Armor choice
                {
                        int armor_count = -1;
                        if (player.getArmor() >= party.size() + 1) //checks if max amount of armor reached
                        {
                            cout<<"> Everyone is already wearing armor. Choose something else!"<<endl;
                            break;
                        }
                        while (armor_count < 0)
                        {
                            cout<<"> How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)"<<endl;
                            cin>> armor_count;

                            if (armor_count * 5 * mult > player.getGold()) //meaning plyr can't afford it
                            {
                                cout<<"> Not enough gold! Choose another quantity"<<endl;
                                armor_count = -1; //so that the while loop continues
                            }
                            if (armor_count + player.getArmor() > party.size() + 1) // checks if buying more than max armor
                            {
                                cout<<"> You can't wear more than one armor per person."<<endl;
                                armor_count = -1;
                            }
                        }
                        if (armor_count == 0) //0 to cancel
                        {
                            break;
                        }
                        yes_no_choice = 'a';
                        while (yes_no_choice != 'y' && yes_no_choice != 'n')
                        {
                            cout<<"> You want to buy "<<armor_count<<" suit(s) of armor for "<<armor_count * 5 * mult<<" Gold? (y/n)"<<endl;
                            cin>>yes_no_choice;
                        }
                        if (yes_no_choice == 'y')
                        {
                                int gold_new = player.getGold() - armor_count * 5 * mult;
                                int new_armor_amount = player.getArmor() + armor_count;
                                player.setGold(gold_new);  // update plyr gold
                                player.setArmor(new_armor_amount);  // update plyr armor count by adding weapon
                                cout<<"> Thank you for your patronage! What else can I get for you?"<<endl;
                        }
                        else
                        {
                            cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                        }
                    break;
                }
                case 3: //Option 3: Ingredients
                {
                        int ingredient_weight = -1;
                        while (ingredient_weight < 0)
                        {
                            cout<<"> How many kilograms of ingredients do you want? (Enter a positive integer, or 0 to cancel)"<<endl;
                            cin>> ingredient_weight;

                            if (ingredient_weight * mult > player.getGold()) //meaning plyr can't afford it
                            {
                                cout<<"> Not enough gold! Choose another quantity"<<endl;
                                ingredient_weight = -1; //so that the while loop continues
                            }
                        }
                        if (ingredient_weight == 0) //0 to cancel
                        {
                            break;
                        }
                        yes_no_choice = 'a';
                        while (yes_no_choice != 'y' && yes_no_choice != 'n')
                        {
                            cout<<"> You want to buy "<<ingredient_weight<<" kilogram(s) of ingredients for "<<ingredient_weight<< " Gold? (y/n)"<<endl;
                            cin>>yes_no_choice;
                        }
                        if (yes_no_choice == 'y')
                        {
                                int gold_new = player.getGold() - ingredient_weight * mult;
                                int new_ingredients_amount = player.getIngredients() + ingredient_weight;

                                player.setGold(gold_new);  // update plyr gold
                                player.setIngredients(new_ingredients_amount);  // update player ingrdients
                                cout<<"> Thank you for your patronage! What else can I get for you?"<<endl;
                        }
                        else
                        {
                            cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                        }

                    break;
                }
                case 4: //cookware
                {
                    cout<<"> I have a several types of cookware, which one would you like?"<<endl<<"Each type has a different probability of breaking when used, marked with (XX%)"<<endl<<"Choose one of the following:"<<endl<<"1. (25%) Ceramic Pot [2 Gold]"<<endl<<"2. (10%) Frying Pan [10 Gold]" <<endl<<"3. ( 2%) Cauldron [20 Gold]"<<endl<<"4. Cancel"<<endl;
                    cin>>cookware_choice;
                    amount =-1; //amount of item user wants

                        switch (cookware_choice)
                        {
                            case 1: // 1. (25%) Ceramic Pot [2 Gold]
                            {
                                while (amount < 0)
                                {
                                    cout<<"> How many would you like? (Enter a positive integer, or 0 to cancel)"<<endl;   
                                    cin>> amount;

                                    if (amount * 2 * mult > player.getGold()) //meaning plyr can't afford it
                                    {
                                        cout<<"> Not enough gold! Choose another quantity"<<endl;
                                        amount = -1; //so that the while loop continues
                                    }
                                }
                                if (amount == 0) //0 to cancel
                                {
                                    break;
                                }
                                yes_no_choice = 'a';
                                while (yes_no_choice != 'y' && yes_no_choice != 'n')
                                {
                                    cout<<"> You want to buy " <<amount <<" Ceramic Pot(s) for "<<amount * 2 * mult<<" Gold? (y/n)"<<endl;
                                    cin>>yes_no_choice;
                                }
                                if (yes_no_choice == 'y')
                                {
                                        int gold_new = player.getGold() - amount * 2 * mult;
                                        int new_cookware_amount = player.getCookware(0) + amount;

                                        player.setGold(gold_new);  // update plyr gold
                                        player.setCookware(new_cookware_amount,0);  // update plyr cookware inventory by adding weapon
                                }
                                else
                                {
                                    cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                                }
                        
                                break;
                            }
                            case 2: // 2. (10%) Frying Pan [10 Gold]
                            {
                                while (amount < 0)
                                {
                                    cout<<"> How many would you like? (Enter a positive integer, or 0 to cancel)"<<endl;     // 1. Stone Club [2 Gold]
                                    cin>> amount;

                                    if (amount * 10 * mult > player.getGold()) //meaning plyr can't afford it
                                    {
                                        cout<<"> Not enough gold! Choose another quantity"<<endl;
                                        amount = -1; //so that the while loop continues
                                    }
                                }
                                if (amount == 0) //0 to cancel
                                {
                                    break;
                                }
                                yes_no_choice = 'a';
                                while (yes_no_choice != 'y' && yes_no_choice != 'n')
                                {
                                    cout<<"> You want to buy " <<amount <<" Frying Pan(s) for "<<amount * 10 * mult<<" Gold? (y/n)"<<endl;
                                    cin>>yes_no_choice;
                                }
                                if (yes_no_choice == 'y')
                                {
                                        int gold_new = player.getGold() - amount * 10 * mult;
                                        int new_cookware_amount = player.getCookware(1) + amount;

                                        player.setGold(gold_new);  // update plyr gold
                                        player.setCookware(new_cookware_amount,1);  // update plyr cookware inventory by adding weapon
                                }
                                else
                                {
                                    cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                                }
                        
                                break;
                            }
                            case 3: // 3. ( 2%) Cauldron [20 Gold]
                            {
                                while (amount < 0)
                                {
                                    cout<<"> How many would you like? (Enter a positive integer, or 0 to cancel)"<<endl;     // 1. Stone Club [2 Gold]
                                    cin>> amount;

                                    if (amount * 20 * mult > player.getGold()) //meaning plyr can't afford it
                                    {
                                        cout<<"> Not enough gold! Choose another quantity"<<endl;
                                        amount = -1; //so that the while loop continues
                                    }
                                }
                                if (amount == 0) //0 to cancel
                                {
                                    break;
                                }
                                yes_no_choice = 'a';
                                while (yes_no_choice != 'y' && yes_no_choice != 'n')
                                {
                                    cout<<"> You want to buy " <<amount <<" Cauldron(s) for "<<amount * 20 * mult<<" Gold? (y/n)"<<endl;
                                    cin>>yes_no_choice;
                                }
                                if (yes_no_choice == 'y')
                                {
                                        int gold_new = player.getGold() - amount * 20 * mult;
                                        int new_cookware_amount = player.getCookware(1) + amount;

                                        player.setGold(gold_new);  // update plyr gold
                                        player.setCookware(new_cookware_amount,2);  // update plyr cookware inventory by adding weapon
                                }
                                else
                                {
                                    cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                                }
                        
                                break;
                            }
                            case 4:
                            {
                                user_menu_choice_integer = -2; //so the loop continues
                                break;
                            }
                            default: cout<<"> That was not a choice I gave you"<<endl;break;
                        }
                    break;
                }
                case 5: //sell treasures
                {
                    cout<<"> What do you want to sell me: "<<endl<<"1. Silver ring (R) - 10 gold pieces each"<<endl<<"2. Ruby necklace (N) - 20 gold pieces each"<<endl<<"3. Emerald bracelet (B) - 30 gold pieces each"<<endl<<"4. Diamond circlet (C) - 40 gold pieces each"<<endl<<"5. Gem-encrusted goblet (G) - 50 gold pieces each"<<endl;
                    cin>>treasure_choice;
                    amount = -1;

                    switch(treasure_choice)
                    {
                        case 1: //1. Silver ring (R) - 10 gold pieces each
                        {
                            if (player.getTreasures(0) == 0)
                            {
                                cout<<"> You have none of that to sell. Choose something else"<<endl;
                                break;
                            }
                            while (amount < 0)
                            {
                                cout<<"> How many would you like to sell? (Enter a positive integer, or 0 to cancel)"<<endl;   
                                cin>> amount;

                                if (amount > player.getTreasures(0)) // plyr doesn't have enough
                                {
                                    cout<<"> You don't have that many, choose another amount to sell"<<endl;
                                    amount = -1; //so that the while loop continues
                                }
                            }
                            if (amount == 0) //0 to cancel
                            {
                                break;
                            }
                            yes_no_choice = 'a';
                            while (yes_no_choice != 'y' && yes_no_choice != 'n')
                            {
                                cout<<"> You want to sell " <<amount <<" Silver ring(s) for "<<amount * 10<<" Gold? (y/n)"<<endl;
                                cin>>yes_no_choice;
                            }
                            if (yes_no_choice == 'y')
                            {

                                    int gold_new = player.getGold() + amount * 10;
                                    int new_treasure_amount = player.getCookware(0) - amount; //initial amount of the treasure minus how much is sold

                                    player.setGold(gold_new);  // update plyr gold
                                    player.setTreasures(new_treasure_amount,0);  // update plyr cookware inventory by adding weapon
                            }
                            else
                            {
                                cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                            }
                    
                            break;
                        }
                        case 2: //2. Ruby necklace (N) - 20 gold pieces each
                        {
                            if (player.getTreasures(1) == 0)
                            {
                                cout<<"> You have none of that to sell. Choose something else"<<endl;
                                break;
                            }
                            while (amount < 0)
                            {
                                cout<<"> How many would you like to sell? (Enter a positive integer, or 0 to cancel)"<<endl;   
                                cin>> amount;

                                if (amount > player.getTreasures(1)) // plyr doesn't have enough
                                {
                                    cout<<"> You don't have that many, choose another amount to sell"<<endl;
                                    amount = -1; //so that the while loop continues
                                }
                            }
                            if (amount == 0) //0 to cancel
                            {
                                break;
                            }
                            yes_no_choice = 'a';
                            while (yes_no_choice != 'y' && yes_no_choice != 'n')
                            {
                                cout<<"> You want to sell " <<amount <<" Silver ring(s) for "<<amount * 10<<" Gold? (y/n)"<<endl;
                                cin>>yes_no_choice;
                            }
                            if (yes_no_choice == 'y')
                            {

                                    int gold_new = player.getGold() + amount * 10;
                                    int new_treasure_amount = player.getTreasures(1) - amount; //initial amount of the treasure minus how much is sold

                                    player.setGold(gold_new);  // update plyr gold
                                    player.setTreasures(new_treasure_amount,1);  // update plyr cookware inventory by adding weapon
                            }
                            else
                            {
                                cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                            }
                    
                            break;
                        }
                        case 3: //3. Emerald bracelet (B) - 30 gold pieces each
                        {
                            if (player.getTreasures(2) == 0)
                            {
                                cout<<"> You have none of that to sell. Choose something else"<<endl;
                                break;
                            }
                            while (amount < 0)
                            {
                                cout<<"> How many would you like to sell? (Enter a positive integer, or 0 to cancel)"<<endl;   
                                cin>> amount;

                                if (amount > player.getTreasures(2)) // plyr doesn't have enough
                                {
                                    cout<<"> You don't have that many, choose another amount to sell"<<endl;
                                    amount = -1; //so that the while loop continues
                                }
                            }
                            if (amount == 0) //0 to cancel
                            {
                                break;
                            }
                            yes_no_choice = 'a';
                            while (yes_no_choice != 'y' && yes_no_choice != 'n')
                            {
                                cout<<"> You want to sell " <<amount <<" Silver ring(s) for "<<amount * 10<<" Gold? (y/n)"<<endl;
                                cin>>yes_no_choice;
                            }
                            if (yes_no_choice == 'y')
                            {

                                    int gold_new = player.getGold() + amount * 10;
                                    int new_treasure_amount = player.getTreasures(2) - amount; //initial amount of the treasure minus how much is sold

                                    player.setGold(gold_new);  // update plyr gold
                                    player.setTreasures(new_treasure_amount,2);  // update plyr cookware inventory by adding weapon
                            }
                            else
                            {
                                cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                            }
                    
                            break;
                        }
                        case 4: //4.Diamond circlet (C) - 40 gold pieces each
                        {
                            if (player.getTreasures(3) == 0)
                            {
                                cout<<"> You have none of that to sell. Choose something else"<<endl;
                                break;
                            }
                            while (amount < 0)
                            {
                                cout<<"> How many would you like to sell? (Enter a positive integer, or 0 to cancel)"<<endl;   
                                cin>> amount;

                                if (amount > player.getTreasures(3)) // plyr doesn't have enough
                                {
                                    cout<<"> You don't have that many, choose another amount to sell"<<endl;
                                    amount = -1; //so that the while loop continues
                                }
                            }
                            if (amount == 0) //0 to cancel
                            {
                                break;
                            }
                            yes_no_choice = 'a';
                            while (yes_no_choice != 'y' && yes_no_choice != 'n')
                            {
                                cout<<"> You want to sell " <<amount <<" Silver ring(s) for "<<amount * 10<<" Gold? (y/n)"<<endl;
                                cin>>yes_no_choice;
                            }
                            if (yes_no_choice == 'y')
                            {

                                    int gold_new = player.getGold() + amount * 10;
                                    int new_treasure_amount = player.getTreasures(3) - amount; //initial amount of the treasure minus how much is sold

                                    player.setGold(gold_new);  // update plyr gold
                                    player.setTreasures(new_treasure_amount,3);  // update plyr cookware inventory by adding weapon
                            }
                            else
                            {
                                cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                            }
                    
                            break;
                        }
                        case 5: //5. Gem-encrusted goblet (G) - 50 gold pieces each
                        {
                            if (player.getTreasures(4) == 0)
                            {
                                cout<<"> You have none of that to sell. Choose something else"<<endl;
                                break;
                            }
                            while (amount < 0)
                            {
                                cout<<"> How many would you like to sell? (Enter a positive integer, or 0 to cancel)"<<endl;   
                                cin>> amount;

                                if (amount > player.getTreasures(4)) // plyr doesn't have enough
                                {
                                    cout<<"> You don't have that many, choose another amount to sell"<<endl;
                                    amount = -1; //so that the while loop continues
                                }
                            }
                            if (amount == 0) //0 to cancel
                            {
                                break;
                            }
                            yes_no_choice = 'a';
                            while (yes_no_choice != 'y' && yes_no_choice != 'n')
                            {
                                cout<<"> You want to sell " <<amount <<" Silver ring(s) for "<<amount * 10<<" Gold? (y/n)"<<endl;
                                cin>>yes_no_choice;
                            }
                            if (yes_no_choice == 'y')
                            {

                                    int gold_new = player.getGold() + amount * 10;
                                    int new_treasure_amount = player.getTreasures(4) - amount; //initial amount of the treasure minus how much is sold

                                    player.setGold(gold_new);  // update plyr gold
                                    player.setTreasures(new_treasure_amount,4);  // update plyr cookware inventory by adding weapon
                            }
                            else
                            {
                                cout<<"> That's fine even though I went to the trouble of getting it all ready. You want anything else? Make it quick."<<endl;
                            }
                    
                            break;
                        }
                        default: cout<<"> That was not a choice I gave you"<<endl;break;
                    }
                    
                    break;
                }

                case 6: 
                {
                    yes_no_choice = 'a';
                    while (yes_no_choice != 'y' && yes_no_choice != 'n')
                    {
                        cout<<"> Are you sure you're finished? You won't be able to buy anything else from me! (y/n)"<<endl;
                        cin>>yes_no_choice;
                    }
                    if (yes_no_choice == 'y') //done
                    {
                        break;
                    }
                    else // not done 
                    {
                        user_menu_choice_integer = -2; //so that the menu resets
                    }
                    break; //Exit Menu, removes NPC
                }
                default: cout<<"> That was not a choice I gave you"<<endl;break;
            }
        }
        else
        {
            cout<<"Invalid choice"<<endl;
            user_menu_choice_integer = -2;
        }
    }
    return player;
}

//Riddle Algorithm:
//take in file
//split file into two parts- questions and answers
//use an random number generator to find question to ask
//ask question, and take in answer
//if answer correct, return true; 1 
//if answer false return false; 0 
//file not opened is reutnr -1

int Npc::displayRiddle(string file_name)
{
    ifstream fin;
    fin.open(file_name);
    string questions[20]; //every second index is the answer
    string answers[20];
    string line_component[2];
    string line;
    string answer;
    int split_result;
    int counter = 0;

    if (fin.fail()) //file doesn't open
    {
        return -1;
    }
    else //file opened sucess so store in answer
    {
        while (!fin.eof())
        {
            getline(fin,line);
            split_result = split2(line,'~',line_component,2);
            questions[counter] = line_component[0];
            answers[counter] = line_component[1];
            counter++;
        }
    }

    int randomx = ranGenerator5(0,19);
    cout<<questions[randomx]<<endl;
    cin>>answer;
    if (answer == answers[randomx])
    {
        return 1;
    }
    else
    {
        return 0;
    }

}




