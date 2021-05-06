#include "../inc/inord_list.h"

using namespace std;

unsigned int charCount = 0;

int main() {

    List myList;
    string word;
    char ch;
    unsigned int line = 1;
    bool flag = true;
    ifstream inFile, cmdFile;

    inFile.open("File.txt", std::ifstream:: in );
    // cmdFile.open("Commands.txt",std::ifstream::in);

    if (inFile.is_open()) {
        while (inFile.get(ch)) {
            charCount++;
            ch = tolower(ch);
            if (ch == ',' || ch == ';' || ch == ':' || ch == '&' || ch == '.' ||
                ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '(' ||
                ch == ')' || ch == 34 || ch == 39)
                continue;

            else if (ch == ' ' || ch == '\n') {

                if (word.length() != 0 && word.find(" ") == string::npos){
                    flag = myList.Insert(word, line);
                    word.clear();
                }
                
                if (!flag) {
                    cout << "ERROR Allocating a Word!";
                    exit(1);
                }

                if (ch == '\n') line++;
            }

            else word += ch;
        }

        if (word.length() != 0 && word.find(" ") == string::npos)
            flag = myList.Insert(word, line);
    } else {
        cout << "Can't Open File" << endl;
        exit(1);
    }
    myList.Clean();
    myList.Print();
    return 0;
}