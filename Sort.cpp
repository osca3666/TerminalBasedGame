#include <iostream>
#include <string>
#include "Sort.h"

using namespace std;
void Sort::setName(string name){
    name_ = name;
}

string Sort::getName() const{
    return name_;
} 
void Sort::setScore(int score){
    score_ = score;
}

int Sort::getScore() const{
    return score_;
}