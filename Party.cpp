#include <iostream>
#include "Party.h"

using namespace std;

//party default constructor
Party::Party()
{
    resetParty();
}
void Party::resetParty()
{
    party_member_name = "";
    party_member_fullness = 50; 
}
//return party member name
string Party::getPartyMemberName()
{
    return party_member_name;
}
//return party member fullness
int Party::getPartyMemberFullness()
{
    return party_member_fullness;
}


//setters
//per party member
//set new party member name to the argument
void Party::setPartyMemberName(string party_member_name_)
{
    party_member_name = party_member_name_;
}
//compute new fullness by adding the argument to the previous fullness
//if new fullness is more than or equal to 50, change it 50
//else make fullness the new fullness
void Party::setPartyMemberFullness(int fullness_)
{
    int new_fullness = party_member_fullness + fullness_;
    if (new_fullness >= 50) //cap fullness at 50
    {
        party_member_fullness = 50;
    }
    else
    {
        party_member_fullness = new_fullness;
    }
    //If any party member's fullness level drops to zero, they will perish from starvation at the end of the next turn
}


