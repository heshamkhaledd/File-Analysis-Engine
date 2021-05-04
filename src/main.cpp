#include "../inc/inord_list.h"
using namespace std;

int main()
{
    List myList;
    string word;
    char ch;
    unsigned int charCount = 0;
    unsigned int line = 0;
    bool flag;
    ifstream inFile;
    inFile.open("File.txt",std::ifstream::in);
    if (inFile.is_open())
    {
        while(inFile >> ch)
        {
            charCount++;
            if (ch == ',' || ch == ';' || ch == ':' || ch == '&' || ch == '.' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == 34 || ch == 39)
                continue;
                
            word += ch;
            if (ch == ' ')
            {
                word = word.erase(word.length(),1);
                flag = myList.Insert(word,line);
                if (!flag)
                {
                    cout<<"ERROR Allocating a Word!";
                    exit(1);
                }
                else
                    word.clear();
            }
            else if (ch == '\n')
                line++;
        }
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