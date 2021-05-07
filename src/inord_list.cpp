#include "../inc/inord_list.h"

using namespace std;

static unsigned int nodeCount = 0;
extern unsigned int charCount;

List::List() {

   head = NULL;
   current = NULL;
}

List::~List() {

   List::node *nodePtr;
    if (head == NULL)
        return;
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

bool List::InsertAtAny(const ListElemType data, unsigned int location, unsigned int line) {

   node * link = new node;
   if (link == NULL)
      return false;

   link -> data = data;
   link -> line.push_back(line);
   link -> frequency = 0;

   if (head == NULL || location == 0) {
      link -> next = head;
      head = link;
      return true;
   }

   current = head;
   for (unsigned int Idx = 0; Idx < location - 1; Idx++)
      current = current -> next;

   link -> next = current -> next;
   current -> next = link;
   return true;
}

bool List::DeleteDuplicate(const ListElemType data, unsigned int & frequency) {

   bool firstPass = false;
   bool flag = false;
   unsigned int Itr = 0;
   unsigned int Idx = 0;
   bool lineIdc = false;
   List::node *previous;
   List::node *mainNode = NULL;
   
   if (head == NULL)
      return false;

   else {
      current = head;
      previous = head;
      while (current != NULL) {
         if (current -> data != data) {
            current = current -> next;
            Itr++;
            continue;
         }

         if (!firstPass) {
            firstPass = true;
            mainNode = current;
            current = current -> next;
            continue;
         } else {
            while (Idx < Itr) {
               previous = previous -> next;
               Idx++;
            }
            previous -> next = current -> next;

            vector < unsigned int > ::iterator it = std::find(mainNode -> line.begin(), mainNode -> line.end(), current -> line[0]);
            if (it == mainNode -> line.end())
               mainNode -> line.push_back(current -> line[0]);

            delete current;

            current = previous -> next;
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
         sort(nodePtr -> line.begin(), nodePtr -> line.end());
         nodePtr = nodePtr -> next;
         frequency = 0;
      }
      return true;
   }
}

bool List::Insert(const ListElemType data, unsigned int line) {

   nodeCount++;
   bool flag;

   if (head == NULL) {
      flag = InsertAtAny(data, 0, line);

      if (flag)
         return true;

      else
         return false;
   }

   current = head;
   unsigned int Itr = 0;
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

bool List::distWords (unsigned int &distWordsNum) {
   distWordsNum = nodeCount;
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

bool List::countWord (const string requiredStr, unsigned int &wordCount) {
   if (head == NULL)
      return false;
   
   else {
      current = head;
      while (current != NULL) {
         if (!(current -> data.compare(requiredStr)))
            wordCount = current->frequency;
         current = current -> next;
      }
      return true;
   }
}

bool List::genericSearch (const string str, string &requiredStr, const char type){
   if (head == NULL)
      return false;
   else {
      current = head;
      unsigned int Idx = 0;
      while (current != NULL) {
         Idx = current -> data.find(str);
         if (type == 'a' && Idx == 0) {
               requiredStr = requiredStr + current -> data + ":" + " " + to_string(current -> frequency) + "   ";
         }
         else if (type == 'b' && Idx != string::npos) {
               requiredStr = requiredStr + current -> data + ":" + " " + to_string(current -> frequency) + "   ";
         }
         else if (type == 'c' && Idx != string::npos) {
            requiredStr = requiredStr + current -> data + ":   lines ";
            for (unsigned int Element: current -> line)
               requiredStr += to_string(Element) + " ";

         requiredStr.erase(requiredStr.length()-1,1);
         requiredStr += "\n";
         }
         current = current -> next;
      }
      requiredStr.erase(requiredStr.length()-1,1);
      return true;
   }
}

void List::Print() {
   current = head;

   while (current != NULL) {
      cout <<endl<<"Word: " << current -> data << " " << " Frequency: " << current -> frequency << " Lines: ";
      for (int Element: current -> line)
         cout << Element << " ";
      current = current -> next;
   }
   cout << endl << "nodeCount: " << nodeCount << endl;
   cout << "charCount: " << charCount << endl;
}