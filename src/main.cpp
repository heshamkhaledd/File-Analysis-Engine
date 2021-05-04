#include "../inc/inord_list.h"
using namespace std;

int main()
{
    List myList;
    string word;
    char ch;
    unsigned int charCount = 0;
    unsigned int line = 1;
    bool flag;
    ifstream inFile;
    inFile.open("File.txt",std::ifstream::in);
    if (inFile.is_open())
    {
        while(inFile.get(ch))
        {
            charCount++;
            if (ch == ',' || ch == ';' || ch == ':' || ch == '&' || ch == '.' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == 34 || ch == 39)
                continue;
   
            else if (ch == ' ' || ch == '\n')
            {
                if (ch == '\n')
                    line++;

                flag = myList.Insert(word,line);
                word = "";

                if (!flag)
                {
                    cout<<"ERROR Allocating a Word!";
                    exit(1);
                }
            }
            else
                word += ch;
        }
        flag = myList.Insert(word,line);
    }
    
    else
    {
        cout<<"Can't Open File"<<endl;
        exit (1);
    }
    myList.Clean();
    myList.Print();

    return 0;
}