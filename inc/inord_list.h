#ifndef INORD_LIST_H
#define INORD_LIST_H

#include <iostream>

#include <string>

#include <fstream>

#include <vector>

#include <algorithm>

#include <sstream>

using namespace std;

typedef string ListElemType;

class List {

    private:
        struct node {
            ListElemType data;
            struct node * next;
            vector <unsigned int> line;
            unsigned int frequency;
        };
        node *head;
        node *current;
        bool InsertAtAny(const ListElemType data, unsigned int location, unsigned int line);
        bool DeleteDuplicate(const ListElemType data, unsigned int & frequency);
        
    public:
        List();
        ~List();
        bool Insert(const ListElemType data, unsigned int line);
        bool Clean();
        bool wordCount(unsigned int &wordCount);
        bool distWords(unsigned int &distWordsNum);
        bool frequentWord(string &requiredStr);
        bool countWord (const string requiredStr, unsigned int &wordCount);
        bool genericSearch (const string str, string &requiredStr, const char type);
        void Print();

};
#endif