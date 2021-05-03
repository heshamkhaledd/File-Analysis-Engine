#include "../inc/inord_list.h"
using namespace std;

static unsigned int nodeCount = 0;

List::List()
{
    head = NULL;
    tail = NULL;
    current = NULL;
}

List::~List()
{
    if (head == NULL)
        return;
    
    current = head;
    if (current->next == NULL)
    {
        delete current;
        return;
    }
    else
    {
        previous = head->next;
        while (current != NULL)
        {
            delete current;
            current = previous;
            previous = previous->next;
        }
    }
}

bool List::InsertAtLast (const ListElemType data, unsigned int line)
{
    node *link = new node;
    if(link == NULL)
        return false;

    link->data = data;
    link->line = line;

    link->next = NULL;

    if (head = NULL)
    {
        head = link;
        return true;
    }
    else
    {
        current = head;
        tail->next = link;
        tail = link;

        return true;
    }
}

bool List::InsertAtFirst (const ListElemType data, unsigned int line)
{
    node *link = new node;
    if (link == NULL)
        return false;

    link->data = data;
    link->line = line;

    if (head == NULL)
        tail = link;

    link->next = head;
	head = link;

    return true;
}

bool List::InsertAtAny(const ListElemType data, unsigned int location, unsigned int line)
{
    node *link = new node;
    if (link == NULL)
        return false;

    link->data = data;
    link->line = line;

    if (head == NULL || location == 0)
    {
        link->next = head;
	    head = link;
        return true;
    }


    current = head;
    for (int Idx = 0 ; Idx<location-1 ; Idx++)
        current = current->next;

    link->next = current->next;
    current->next = link;
    return true;
}

bool List::Insert (const ListElemType data,unsigned int line)
{
    nodeCount++;
    bool flag;
    if (head == NULL)
    {
        flag = InsertAtLast(data,line);
        if (flag)
            return true;
        else
            return false;
    }

    current = head;
    unsigned int Itr = 0;
    while (current != NULL && data.compare(current->data) > 0)
    {
        current = current->next;
        Itr++;
    }

    flag = this->InsertAtAny(data,Itr,line);
        if (flag)
            return true;
        else
            return false;
}

bool List::DeleteDuplicate(const ListElemType data)
{
    bool firstPass = false;
    bool flag = false;
    unsigned int Itr = 0;
    unsigned int Idx = 0;
    if (head == NULL)
        return false;
    else
    {
        current = head;
        previous = head;
        while (current != NULL)
        {
            if(current->data != data)
            {
                current = current->next;
                Itr++;
                continue;
            }
            
            if (!firstPass)
            {
                firstPass = true;
                current = current->next;
                continue;
            }
            else
            {
                while(Idx<Itr)
                {
                    previous = previous->next;
                        Idx++;
                }
                
                previous->next = current->next;
                delete current;
                current = previous->next;
                nodeCount--;
                flag = true;
            }
        }
        if (!flag)
            return true;
        else
            return false;       
    }
}