/*
Paul Johnston, Section 1, pjohnst5@icloud.com
Purpose: Tokenize all sorts of symbols.
Input: file name to read from.
Output: List of tokens which have a token type, value and line number.
*/
#include "Scanner.h"

void Scanner::Scan()
{
   ifstream myFile;

   myFile.open(fileName.c_str());

   myFile.get(myChar);
   while (!(myFile.eof())) {
      switch(myChar) {
         case ',': {
            Token myToken(COMMA,",",lineNum);
            myVector.push_back(myToken);
            break;
         }
         case '.': {
            Token myToken(PERIOD,".",lineNum);
            myVector.push_back(myToken);
            break;
         }
         case '?': {
            Token myToken(Q_MARK,"?",lineNum);
            myVector.push_back(myToken);
            break;
          }
          case '(': {
             Token myToken(LEFT_PAREN,"(",lineNum);
             myVector.push_back(myToken);
             break;
          }
          case ')': {
             Token myToken(RIGHT_PAREN,")",lineNum);
             myVector.push_back(myToken);
             break;
          }
          case ':': {
             if (myFile.peek() == '-'){
                myFile.get(myChar);
                Token myToken(COLON_DASH,":-",lineNum);
                myVector.push_back(myToken);
             }
             else {
                Token myToken(COLON,":",lineNum);
                myVector.push_back(myToken);
              }
              break;
          }
          case '*': {
             Token myToken(MULTIPLY,"*",lineNum);
             myVector.push_back(myToken);
             break;
          }
          case '+': {
             Token myToken(ADD,"+",lineNum);
             myVector.push_back(myToken);
             break;
          }
          case '\n': {
             lineNum++;
             break;
          }
          case ' ': {   //Ignores whitespace
             break;
          }
          case '\t':{
             break;
          }
          case '\v':{
             break;
          }
          case '\f': {
             break;
          }
          case '\r':{
             break;
          }
          case '#':{
             temp += "#";
             lineNumStartedOn = lineNum;
             CommentMaker(myFile);
             temp = "";
             break;
          }
          case '\'': {
             temp += "\'";
             lineNumStartedOn = lineNum;
             StringMaker(myFile);
             temp = "";
             break;
          }
          case 's': {
             //temp += "s";
             ReadID(myFile);
             break;
          }
          default: {
             if (isalpha(myChar)){
                ReadID(myFile);
             }
             else {
                temp += myChar;
                Token myToken(UNDEFINED,temp,lineNum);
                myVector.push_back(myToken);
                temp = "";
             }
             break;
          }
       }
       myFile.get(myChar);
  }
  Token myToken(MYEOF,"",lineNum);
  myVector.push_back(myToken);
}

void Scanner::CommentMaker(ifstream& myFile)
{
   myFile.get(myChar);
   if (myChar != '|'){ //Line comment
      while (!(myFile.eof())){
         if (myChar == '\n'){
            lineNum++;
            Token myToken(COMMENT,temp,lineNumStartedOn);
          //  myVector.push_back(myToken);
            return;
         }
         temp += myChar;
         myFile.get(myChar);
      }
      Token myToken(COMMENT,temp,lineNumStartedOn);
      //myVector.push_back(myToken);
      return;
   }
   else {    //BlockComment
     temp += myChar;
     BlockCommentMaker(myFile);
     temp = "";
   }
   return;
}

void Scanner::BlockCommentMaker(ifstream& myFile)
{
   myFile.get(myChar);
   while (!(myFile.eof())) {
      temp += myChar;
      if ((myChar == '|') && (myFile.peek() == '#')){
         myFile.get(myChar);
         temp += myChar;
         Token myToken(COMMENT,temp,lineNumStartedOn);
        // myVector.push_back(myToken);
         temp = "";
      //lineNumStartedOn = 1;
         return;
     }
     if (myChar == '\n'){
        ++lineNum;
     }
      myFile.get(myChar);
   }
  //Illegal Block Comment
   Token myToken (UNDEFINED,temp,lineNumStartedOn);
   myVector.push_back(myToken);
   temp = "";
   lineNumStartedOn = 1;
}

void Scanner::StringMaker(ifstream& myFile)
{
   myFile.get(myChar);
   while (!(myFile.eof())) {
      switch(myChar) {
         case '\n': {
            temp += '\n';
            lineNum++;
            break;
         }
         case '\'': {
            temp += '\'';
            if (myFile.peek() == '\'') {
               temp += '\'';
               myFile.get(myChar);
            }
            else {
               Token myToken(STRING,temp,lineNumStartedOn);
               myVector.push_back(myToken);
               temp = "";
               lineNumStartedOn = 1;
               return;
            }
            break;
         }
         default: {
            temp += myChar;
            break;
         }
       }
       myFile.get(myChar);
    }
    //String is UNDEFINED
    Token myToken (UNDEFINED,temp,lineNumStartedOn);
    myVector.push_back(myToken);
    temp = "";
    lineNumStartedOn = 1;
    return;
}

void Scanner::ReadWords(ifstream& myFile)
{
   if (temp == "Schemes"){
      Token myToken(SCHEMES,temp,lineNum);
      myVector.push_back(myToken);
      temp = "";
   }
   else if (temp == "Facts"){
      Token myToken(FACTS,temp,lineNum);
      myVector.push_back(myToken);
      temp = "";
   }
   else if (temp == "Rules"){
      Token myToken(RULES,temp,lineNum);
      myVector.push_back(myToken);
      temp = "";
   }
   else if (temp == "Queries"){
      Token myToken(QUERIES,temp,lineNum);
      myVector.push_back(myToken);
      temp = "";
   }
   else {
      Token myToken(ID,temp,lineNum);
      myVector.push_back(myToken);
      temp = "";
   }
}

void Scanner::ReadID(ifstream& myFile)
{
   while (isalnum(myChar)) {
      temp += myChar;
      if (isalnum(myFile.peek())){
         myFile.get(myChar);
      }
      else {
         break;
      }
   }
   ReadWords(myFile);
}

void Scanner::Print()
{
  cout << endl;
   for (unsigned int i = 0; i < myVector.size(); ++i) {
      myVector.at(i).ToString();
   }
   cout << "Total Tokens = " << myVector.size() << endl << endl;
   return;
}



vector<Token> Scanner::getTokens() const
{
  return myVector;
}
