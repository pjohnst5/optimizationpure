/*
Paul Johnston, Section 1, pjohnst5@icloud.com
Purpose: Tokenize all sorts of symbols.
Input: file name to read from.
Output: List of tokens which have a token type, value and line number.
*/
#pragma once
#include <fstream>
#include "Token.h"

using namespace std;

class Scanner
{

public:
   Scanner(string myFile) {fileName = myFile; lineNum = 1; myChar = 0; temp = ""; lineNumStartedOn = 1;}
   ~Scanner() {myChar = 0; lineNum = 1; fileName = ""; temp = ""; lineNumStartedOn = 1;}
   void Scan();
   void Print();
   void CommentMaker(ifstream& myFile);
   void BlockCommentMaker(ifstream& myFile);
   void StringMaker(ifstream& myFile);
   void ReadWords(ifstream& myFile);
   void ReadID(ifstream& myFile);
   vector<Token> getTokens() const;
private:
   int lineNumStartedOn;
   string temp;
   char myChar;
   string fileName;
   int lineNum;
   vector<Token> myVector;
};
