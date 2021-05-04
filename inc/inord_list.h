#ifndef INORD_LIST_H
#define INORD_LIST_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

typedef string  ListElemType;

class List{

    private:
            struct node{
                ListElemType data;
                struct node *next;
                string line;
                unsigned int frequency;
            };
            node*    head;
            node*    tail;
            node*    current;
            node*    current2;
            node*    current3;
            node*    previous;
            bool InsertAtLast(const ListElemType data, unsigned int line);
            bool InsertAtAny(const ListElemType data, unsigned int location, unsigned int line);
            bool DeleteDuplicate(const ListElemType data, unsigned int &frequency);
    public:
            List();
            ~List();
            bool            Insert(const ListElemType data, unsigned int line);
            bool            Clean();
            ListElemType    Fetch(ListElemType &data);
            void            Print();

};
#endif