/***********************************************************************
// 244-200 Workshop 1: Compiling modular source code
// File	w1.cpp
// Version 1.0
// Date	2020/01/10
// Author	Fardad Soleimanloo
// Description
// This provides some source code in a single file to break
// into modules and compile together
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
// Fardad
/////////////////////////////////////////////////////////////////
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include <cstring>
const int MAX_WORD_LEN = 21;
const int MAX_NO_OF_WORDS = 500;
using namespace std;
struct Word {
   char letters[MAX_WORD_LEN];
   int count;
};

void toLowerCaseAndAlphabeticCopy(char des[], const char source[]) {
   int i = 0, j = 0;
   char lower;
   for (; source[i] != 0;i++) {
      lower = tolower(source[i]);
      if (lower>='a' && lower <='z') {
         des[j++] = tolower(source[i]);
      }
   }
   des[j] = 0;
}


int searchWords(const Word words[], int num, const char word[]) {
   int i;
   int foundIndex = -1;  // will be set to found index; if not found sould be less than 0
   for (i = 0;foundIndex == -1 && i < num; i++) { // while not found and i is less than number of words
      if (strcmp(words[i].letters, word) == 0) { // if word is already read and found in the list of previous words
         foundIndex = i;   // set the index to be returned.
      }
   }
   return foundIndex;
}

void addWord(Word words[], int* index, const char newWord[]) {
   strcpy(words[*index].letters, newWord);
   words[*index].count++;
   (*index)++;
}


void title() {
   cout << "Text word stats: " << endl;
   cout << "Word: No of  occurrences." << endl << "------------------------------------------------" << endl;
}
void endList() {
   cout << "------------------------------------------------" << endl;
}
void totalWordsStat(int totNoWrds,int totalOverAll, int longestWord ) {
   cout << "Total number of words used: " << totNoWrds << endl;
   cout << "Total number of words overall: " << totalOverAll << endl;
   cout << "Longest word used had " << longestWord << " characters." << endl;
}
void print(const Word* w, bool gotoNextLine) {
   cout << w->letters << ": " << w->count ;
   if (gotoNextLine) cout << endl;
}
void report(const Word words[],int noOfWords, int longestWord){
   int i;
   int total;
   title();
   for (total = 0, i = 0; i < noOfWords; i++) {
      print(&words[i], true);
      total += words[i].count;
   }
   endList();
   totalWordsStat(noOfWords, total, longestWord);
}
void swap(Word* p1, Word* p2) {
   Word w;
   w = *p1;
   *p1 = *p2;
   *p2 = w;
}
void sort(Word words[], int cnt) {
   int i, j;
   for (i = 0; i < cnt - 1; i++){
      for (j = 0; j < cnt - i - 1; j++) {
         if (strcmp(words[j].letters, words[j + 1].letters) > 0) {
            swap(&words[j], &words[j + 1]);
         }
      }
   }
}

void wordStats(bool logOn) {
   Word words[MAX_NO_OF_WORDS] = { {"",0} };
   char word[MAX_WORD_LEN];
   char lowerCaseWord[MAX_WORD_LEN];
   int NoOfWords = 0;
   int maxLen = 0;
   int foundIndex = 0;
   while (!cin.fail()) {
      cin >> word;
      toLowerCaseAndAlphabeticCopy(lowerCaseWord, word);
      if (lowerCaseWord[0] != 0) {
         if (maxLen < (int)strlen(lowerCaseWord)) {
            maxLen = strlen(lowerCaseWord);
         }
         if (NoOfWords == 0) {
            addWord(words, &NoOfWords, lowerCaseWord);
         }
         else {
            foundIndex = searchWords(words, NoOfWords, lowerCaseWord);
            if (foundIndex < 0) { // word not found in list; so word is new and never read before
               foundIndex = NoOfWords;
               addWord(words, &NoOfWords, lowerCaseWord);
            }
            else {
               words[foundIndex].count++;
            }
         }
         if (logOn) {
            print(&words[foundIndex], false);
            cout << " read so far." << endl;
         }
      }
   }
   cout << "---------------------------------------------------" << endl << "End of data" << endl << "---------------------------------------------------" << endl;
   cout << "Sorting data " << endl;
   sort(words, NoOfWords);
   cout << "Sort ended" << endl;
   report(words, NoOfWords, maxLen);
}

void programTitle() {
   cout <<
      "This program reads a text file from the standard input and analyzes and reports" << endl <<
      "the number of words and their occurrences in the text file." << endl;
}
int main() {
   programTitle();
   wordStats(true);
   return 0;
}