#ifndef INORD_LIST_H
#define INORD_LIST_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef string  ListElemType;

class List {

private:
    struct node {
        ListElemType data;
        struct node* next;
        vector <unsigned int>line;
        unsigned int frequency;
    };
    node* head;
    node* tail;
    node* current;
    node* current2;
    node* current3;
    node* previous;
    bool InsertAtAny(const ListElemType data, unsigned int location, unsigned int line);
    bool DeleteDuplicate(const ListElemType data, unsigned int& frequency);
public:
    List();
    ~List();
    bool            Insert(const ListElemType data, unsigned int line);
    bool            Clean();
    void            Print();

};
#endif