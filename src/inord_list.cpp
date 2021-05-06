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
        current2 = head->next;
        while (current2 != NULL)
        {
            delete current;
            current = current2;
            current2 = current2->next;
        }
        delete current;
    }
    return;
}

bool List::InsertAtAny(const ListElemType data, unsigned int location, unsigned int line)
{
    node* link = new node;
    if (link == NULL)
        return false;

    link->data = data;
    link->line.push_back(line);
    link->frequency = 0;

    if (head == NULL || location == 0)
    {
        link->next = head;
        head = link;
        return true;
    }

    current = head;
    for (int Idx = 0; Idx < location - 1; Idx++)
        current = current->next;

    link->next = current->next;
    current->next = link;
    return true;
}

bool List::DeleteDuplicate(const ListElemType data, unsigned int& frequency)
{
    bool firstPass = false;
    bool flag = false;
    unsigned int Itr = 0;
    unsigned int Idx = 0;
    bool lineIdc = false;
    if (head == NULL)
        return false;
    else
    {
        current = head;
        previous = head;
        while (current != NULL)
        {
            if (current->data != data)
            {
                current = current->next;
                Itr++;
                continue;
            }

            if (!firstPass)
            {
                firstPass = true;
                current3 = current;
                current = current->next;
                continue;
            }
            else
            {
                while (Idx < Itr)
                {
                    previous = previous->next;
                    Idx++;
                }
                previous->next = current->next;

                vector <unsigned int>::iterator it = std::find(current3->line.begin(), current3->line.end(), current->line[0]);
                if (it == current3->line.end())
                    current3->line.push_back(current->line[0]);

                delete current;
                
                current = previous->next;
                nodeCount--;
                frequency++;

                flag = true;
            }
        }
        if (!flag)
            return true;
        else
            return false;
    }
}

bool List::Clean()
{
    bool flag = false;
    unsigned int frequency = 0;
    if (head == NULL)
        return false;
    else
    {
        current2 = head;
        for (int Idx = 0; Idx < nodeCount; Idx++)
        {
            flag = DeleteDuplicate(current2->data, frequency);
            current2->frequency = frequency + 1;
            sort(current2->line.begin(), current2->line.end());
            current2 = current2->next;
            frequency = 0;
        }
        return true;
    }
}

bool List::Insert(const ListElemType data, unsigned int line)
{
    nodeCount++;
    bool flag;
    if (head == NULL)
    {
        flag = InsertAtAny(data, 0 , line);
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
    flag = this->InsertAtAny(data, Itr, line);
    if (flag)
        return true;
    else
        return false;
}


void List::Print()
{
    current = head;

    while (current != NULL)
    {
        cout << endl << "Word: " << current->data << " " << " Frequency: " << current->frequency<< " Lines: ";
        for (int Element : current->line)
            cout << Element << " ";
        current = current->next;
    }
    cout << endl << "NodeCount: " << nodeCount << endl;
}