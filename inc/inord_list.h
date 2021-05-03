#ifndef INORD_LIST_H
#define INORD_LIST_H

#include <iostream>
#include <string>

typedef string  ListElemType;

class List{

    private:
            struct node{
                ListElemType data;
                struct node *next;
                unsigned int line;
                unsigned int frequency;
            };
            node*    head;
            node*    tail;
            node*    current;
            node*    previous;
            List();
            bool InsertAtFirst(const ListElemType data, unsigned int line);
            bool InsertAtLast(const ListElemType data, unsigned int line);
            bool InsertAtAny(const ListElemType data, unsigned int location, unsigned int line);
            ~List();
    public:
            bool            Insert(const ListElemType data, unsigned int line);
            bool            DeleteDuplicate(const ListElemType data);
            ListElemType    Fetch(ListElemType &data);

};


#endif