#ifndef PARTY_H
#define PARTY_H

#include <iostream>
#include <vector>

using namespace std;

class Party         
{
    private:
        //each party member info:
        string party_member_name;
        int party_member_fullness;

    public:

        //default constructors
        Party();
        void resetParty();

        string getPartyMemberName();
        int getPartyMemberFullness();

        void setPartyMemberName(string party_member_name_);
        void setPartyMemberFullness(int fullness_);

};

#endif