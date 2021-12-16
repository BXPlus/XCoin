//
// Created by MIZIX on 13/12/2021.
//

#ifndef XBLOCKCHAIN_TRICOUNT_H
#define XBLOCKCHAIN_TRICOUNT_H

#include <iostream>
#include <string>
#include <list>

class Tricount {

};

//The goal of this class will be to deal with money transfers between users (who owes how much)
//For that we will want to have a dictionnary containing the user (his name or code or key or whichever) and then the money he has spent and the money he is owed
//For example users={'A':[100,0];'B':[50;-50];'C':[150;+50]}

//This function is divided in two parts: the expenses (compute how much has been paid) - the division (see who owes how much)

//This for now is a basic idea implementation

//class Tricount {
//public:
//    double total_spending;
//    std::list<char> users;

//    Tricount(){
//        total_spending=0;
//    }
//    ~Tricount(){
//        delete total_spending;
//    }
//    double get_tot_spending();  //See how much money was spent
//    void add_user(char user_name);            //Add users to the tricount
//    void add_expense(double money, char user1, char user2);         //Add expense to the total_spending
//    void add_money_transfer(double money, char user1, char user2);  //Somebody pays back what they owe

//};


#endif //XBLOCKCHAIN_TRICOUNT_H
