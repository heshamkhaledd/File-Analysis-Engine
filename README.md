# File-Analysis-Engine
Implementing a C++ tool that analyzes a text file and returns information about its content. It also allows a simple search for words in the file, and even more.

## Supported User Commands
| Command       |   Arguments   |                                      Description                                       |
| ------------- | ------------- | -------------------------------------------------------------------------------------- |
|  wordCount    |     NULL      | Prints the number of all words in the file                                             |
|  distWords    |     NULL      | Prints the number of distinct words in the file                                        |
|  charCount    |     NULL      | Prints the number of characters in the whole file                                      |
|  frequentWord |     NULL      | Prints the most frequent word in the file                                              |
|  countWord    |     String    | Prints the number of occurences of a specific word                                     |
|  starting     |     String    | Prints all words that starts with the given argument, along with each word's frequency |
|  containing   |     String    | Prints all words that has the given argument in it, along with each word's frequency   |
|  search       |     String    | Prints all words that has the given argument in it, along with its line in the file    |

## Building
In the repository's root directory, run  
``` make -f makefile.mk ```

A ```build``` directory will be created in the root path containing the executable

## Running
Place your text file and Commands file in the build directory next to the executable and run  
``` ./File_Engine.exe <TextFileName> <CommandsFileName>```
