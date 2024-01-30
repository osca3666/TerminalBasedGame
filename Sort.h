#ifndef SORT_H
#define SORT_H


#include <iostream>
#include <string>

using namespace std;

class Sort{

    private:
        int score_;
        string name_;
        
    public:
        void setName(string name);
        void setScore(int score);

        string getName() const; 
        int getScore() const;
        

        


};

#endif