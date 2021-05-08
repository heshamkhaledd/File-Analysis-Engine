 /******************************************************************************
 *
 * [File Name]:   main.cpp
 *
 * [Description]: File Analysis Engine main file. Responsible for reading the
 *                text file and the command file.
 *
 * [Date]:        4/5/2021
 *
 ******************************************************************************/

#include "../inc/inord_list.h"

using namespace std;

// Function prototypes
void readTextFile();
void getCommand();

unsigned int charCount = 0;
    List myList;
    string word,arg,str;
    char ch;
    unsigned int line = 1;
    bool flag = true;
    unsigned int var = 0;
    ifstream inFile, cmdFile;


int main(int argc, char *argv[]) {

    if (argc != 3) {
        cout<<"Incorrect number of arguments"<<endl;
        return 0;
    }

    // Open both files
    inFile.open(argv[1], std::ifstream::in);
    cmdFile.open(argv[2],std::ifstream::in);

    readTextFile();

    getCommand();

    return 0;
}

void readTextFile() {

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
        word.clear();
    } 
    else {
        cout << "File not found" << endl;
        exit(1);
    }

    myList.Clean();
}

void getCommand() {

    if (cmdFile.is_open()) {
        while (getline(cmdFile, word)) {
            istringstream stream(word);
            stream>>word;
            stream>>arg;
            for (int Idx = 0 ; Idx<arg.length() ; Idx++)
                arg[Idx] = tolower(arg[Idx]);
            
            if (!(word.compare("wordCount"))) {
                myList.wordCount(var);
                cout<<"wordCount: "<<var<<endl;
                var = 0;
            }
            else if (!(word.compare("distWords"))) {
                myList.distWords(var);
                cout<<"Distinct Words: "<<var<<endl;
                var = 0;
            }
            else if (!(word.compare("charCount"))) {
                cout<<"charCount: "<<charCount<<endl;
            }
            else if (!(word.compare("frequentWord"))) {
                myList.frequentWord(str);
                cout<<"Most Frequent Word: "<<str<<endl;
                str.clear();
            }
            else if (!(word.compare("countWord"))) {
                myList.countWord(arg,var);
                cout<<"Word Repetition: "<<var<<endl;
                var = 0;
            }
            else if (!(word.compare("starting"))) {
                myList.genericSearch(arg,str,'a');
                cout<<"Words with ("<<arg<<") as a start: "<<str<<endl;
                str.clear();
            }
            else if (!(word.compare("containing"))) {
                myList.genericSearch(arg,str,'b');
                cout<<"Words containing ("<<arg<<"): "<<str<<endl;
                str.clear();
            }
            else if (!(word.compare("search"))) {
                myList.genericSearch(arg,str,'c');
                cout<<"Words containing ("<<arg<<"): \n"<<str<<endl;
                str.clear();
            }
            else{
                cout<<"Undefined Command"<<endl;
            }
        }
    }
    else {
        cout<<"File not found"<<endl;
        exit (1);
    }
}