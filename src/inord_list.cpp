 /******************************************************************************
 *
 * [File Name]:   inord_list.cpp
 *
 * [Description]: List's data structure source code Implementation.
 *
 * [Date]:        4/5/2021
 *
 ******************************************************************************/
#include "../inc/inord_list.h"

using namespace std;

static unsigned int nodeCount = 0;
extern unsigned int charCount;

/******************************************************************************
 *
 * [Function Name]: List
 * 
 * [Type]:        Public
 *
 * [Description]: List constructor, responsible for initializing member
 *                pointers to NULL.
 *
 * [Arguments]:   void
 * [Return]:      void
 *
 *****************************************************************************/
List::List() {

   head = NULL;
   current = NULL;
}

/******************************************************************************
 *
 * [Function Name]: ~List
 * 
 * [Type]:        Public
 *
 * [Description]: List destructor, responsible for clearing the heap
 *                at list termination.
 *
 * [Arguments]:   void
 * [Return]:      void
 *
 *****************************************************************************/
List::~List() {

   List::node *nodePtr;
   // If the list is already empty, then, there's nothing to delete from heap.
    if (head == NULL)
        return;

   // Iterate on the list and delete it node by node.
    current = head;
    if (current -> next == NULL) {
        delete current;
        return;
    } else {
        nodePtr = head -> next;
        while (nodePtr != NULL) {
            delete current;
            current = nodePtr;
            nodePtr = nodePtr -> next;
        }
        delete current;
    }
    return;
}

/******************************************************************************
 *
 * [Function Name]: InsertAtAny
 * 
 * [Type]:        Private
 *
 * [Description]: Responsible for directly inserting nodes in the ordered list
 *                at any given location.
 *
 * [Arguments]:   const ListElemType, unsigned int, unsigned int
 * [Return]:      bool
 *
 *****************************************************************************/
bool List::InsertAtAny(const ListElemType data, unsigned int location, unsigned int line) {

   // Allocate and assign node's member values.
   node * link = new node;
   if (link == NULL)
      return false;

   link -> data = data;
   link -> line.push_back(line);
   link -> frequency = 0;

   // Corner case at which the list is empty or the node's insertion location is at head
   if (head == NULL || location == 0) {
      link -> next = head;
      head = link;
      return true;
   }

   // Iterate on list till you reach the required location, then insert the node.
   current = head;
   for (unsigned int Idx = 0; Idx < location - 1; Idx++)
      current = current -> next;

   link -> next = current -> next;
   current -> next = link;
   return true;
}

/******************************************************************************
 *
 * [Function Name]: DeleteDuplicate
 * 
 * [Type]:        Private
 *
 * [Description]: Responsible for directly deleting duplicate nodes in the 
 *                ordered list, keeping only distinct nodes, and registering
 *                node's frequency everytime an occurence happen.
 *
 * [Arguments]:   const ListElemType, unsigned int &
 * [Return]:      bool
 *
 *****************************************************************************/
bool List::DeleteDuplicate(const ListElemType data, unsigned int & frequency) {

   bool firstPass = false;  // a flag to indicate if the first occurence of a word is found or not.
   bool flag = false;      // a flag to indicate if any words are deleted from the list.
   unsigned int Itr = 0;
   unsigned int Idx = 0;
   List::node *previous;
   List::node *mainNode = NULL;
   
   // Corner case: the list is empty
   if (head == NULL)
      return false;

   else {
      current = head;
      previous = head;
      // Iterate till find the first occurence of a word, store 
      while (current != NULL) {
         if (current -> data != data) {
            current = current -> next;
            Itr++;
            continue;
         }

         // If I reached the first occurence of the word
         // Flip the flag, mark the node by pointing a pointer to it and keep iterating tell the next occurence
         if (!firstPass) {
            firstPass = true;
            mainNode = current;
            current = current -> next;
            continue;
         } else {
            // Mark the node behind the one to delete (the repeated word)
            while (Idx < Itr) {
               previous = previous -> next;
               Idx++;
            }
            previous -> next = current -> next;

            // Check if the repeated word's line is repeated or not in the main node.
            vector < unsigned int > ::iterator it = std::find(mainNode -> line.begin(), mainNode -> line.end(), current -> line[0]);
            if (it == mainNode -> line.end())
               mainNode -> line.push_back(current -> line[0]);

            // delete the repeated word, keep iterating on next nodes and increase the main word's frequency.
            delete current;
            current = previous -> next;
            frequency++;
            nodeCount--; // decrease the node count everytime a node is deleted.

            flag = true;
         }
      }
      if (!flag)
         return true;
      else
         return false;
   }
}

/******************************************************************************
 *
 * [Function Name]: Clean
 * 
 * [Type]:        Public
 *
 * [Description]: Responsible for clearing the list for any duplicates and
 *                assigning the frequency of repetition in each node.
 *
 * [Arguments]:   void
 * [Return]:      bool
 *
 *****************************************************************************/
bool List::Clean() {

   bool flag = false;
   unsigned int frequency = 0;
   List::node *nodePtr;
   
   if (head == NULL)
      return false;

   else {
      nodePtr = head;
      for (unsigned int Idx = 0; Idx < nodeCount; Idx++) {
         flag = DeleteDuplicate(nodePtr -> data, frequency);
         nodePtr -> frequency = frequency + 1;
         // sort the line member to print line occurences in order
         sort(nodePtr -> line.begin(), nodePtr -> line.end());
         nodePtr = nodePtr -> next;
         frequency = 0;
      }
      return true;
   }
}

/******************************************************************************
 *
 * [Function Name]: Insert
 * 
 * [Type]:        Public
 *
 * [Description]: Responsible for inserting a new node in its ordered place using
 *                insertion sort.
 *
 * [Arguments]:   const ListElemTypem unsigned int
 * [Return]:      bool
 *
 *****************************************************************************/
bool List::Insert(const ListElemType data, unsigned int line) {

   nodeCount++; //increase node count everytime this function is called.
   bool flag;

   // Corner case: if the list is empty
   if (head == NULL) {
      flag = InsertAtAny(data, 0, line);

      if (flag)
         return true;

      else
         return false;
   }

   current = head;
   unsigned int Itr = 0;
   // Determine the correct location of the word.
   while (current != NULL && data.compare(current -> data) > 0) {
      current = current -> next;
      Itr++;
   }

   flag = this -> InsertAtAny(data, Itr, line);
   
   if (flag)
      return true;
   else
      return false;
}

/******************************************************************************
 *
 * [Function Name]: wordCount
 * 
 * [Type]:        Public
 *
 * [Description]: Responsible for counting the number of words in the parsed file
 *
 * [Arguments]:   unsignedi int &
 * [Return]:      Explicit: bool
 *                Implicit: unsigned int
 *
 *****************************************************************************/
bool List::wordCount(unsigned int &wordCount) {

   if (head == NULL)
      return false;

   else{
      current = head;
      while (current != NULL) {
         wordCount += current->frequency;
         current = current->next;
      }
      return true;
   }

}

/******************************************************************************
 *
 * [Function Name]: distWords
 * 
 * [Type]:        Public
 *
 * [Description]: Responsible for counting the number of distinct words in the
 *                 parsed file
 *
 * [Arguments]:   unsigned int &
 * [Return]:      Explicit: bool
 *                Implicit: unsigned int
 *
 *****************************************************************************/
bool List::distWords (unsigned int &distWordsNum) {

   distWordsNum = nodeCount; // the list has no repeated words, so, n. of nodes == n. of distinct words.
   return true;
}

bool List::frequentWord(string &requiredStr) {
   if (head == NULL)
      return false;
   else {
      current = head;
      unsigned int max = current->frequency;
      while (current != NULL) {
         if (current->data == "a" || current->data == "an" || current->data == "the" || current->data == "in"
         || current->data == "on" || current->data == "of" || current->data == "and" || current->data == "is" 
         || current->data == "are") {

            current = current->next;
            continue;
         }
         else if (current -> frequency >= max) {
            
            if(current -> frequency > max){
               requiredStr.clear();
               requiredStr = requiredStr + " " + current->data;
               max = current -> frequency;
            }
            else requiredStr = requiredStr + " " + current->data;
         }
         current = current->next;
      }
      requiredStr.erase(0,1);
      return true;
   }
}

/******************************************************************************
 *
 * [Function Name]: countWord
 * 
 * [Type]:        Public
 *
 * [Description]: Responsible for counting the number of occurences of a
 *                speciic word
 *
 * [Arguments]:   const string, unsigned int &
 * [Return]:      Explicit: bool
 *                Implicit: unsigned int
 *
 *****************************************************************************/
bool List::countWord (const string Str, unsigned int &wordCount) {
   if (head == NULL)
      return false;
   
   else {
      current = head;
      while (current != NULL) {
         if (!(current -> data.compare(Str)))
            wordCount = current->frequency;
         current = current -> next;
      }
      return true;
   }
}

/******************************************************************************
 *
 * [Function Name]: genericSearch
 * 
 * [Type]:        Public
 *
 * [Description]: Has three types on search
 *                a) Search the initials of words in the text file for a specific
 *                   string occurence
 *                b) Search the whole word in the text file for a specific
 *                   string occurence
 *                c) Search the whole word in the text file for a specific
 *                   string occurence, Regarding word line.
 *
 * [Arguments]:   const string, string &, const char 
 * [Return]:      Explicit: bool
 *                Implicit: string
 *
 *****************************************************************************/
bool List::genericSearch (const string Str, string &requiredStr, const char type){
   if (head == NULL) {
      requiredStr = "Word not found";
      return false;
   }
   else {
      bool flag = false;
      current = head;
      unsigned int Idx = 0;
      while (current != NULL) {
         Idx = current -> data.find(Str);
         if (type == 'a' && Idx == 0) {
               requiredStr = requiredStr + current -> data + ":" + " " + to_string(current -> frequency) + "   ";
               flag = true;
         }
         else if (type == 'b' && Idx != string::npos) {
               requiredStr = requiredStr + current -> data + ":" + " " + to_string(current -> frequency) + "   ";
               flag = true;
         }
         else if (type == 'c' && Idx != string::npos) {
            requiredStr = requiredStr + current -> data + ":   lines ";
            flag = true;
            for (unsigned int Element: current -> line)
               requiredStr += to_string(Element) + " ";

         requiredStr.erase(requiredStr.length()-1,1);
         requiredStr += "\n";
         }
         current = current -> next;
      }

      if (!flag)
         requiredStr = "Word not found";
      else
         requiredStr.erase(requiredStr.length()-1,1);

      return true;
   }
}