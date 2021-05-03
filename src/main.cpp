#include "../inc/inord_list.h"
using namespace std;

int main()
{
    string str;
    List myList;
    bool flag;
    for (int Idx = 0; Idx < 10 ; Idx++)
    {
        cin>>str;
        flag = myList.Insert(str,1);
        if (flag == false)
        {
            cout<<"ERROR!";
            return 0;
        }
    }

    myList.CleanList();
    myList.Print();
    return 0;
}