/*
Paul Johnston, Section 1, pjohnst5@icloud.com
Purpose: Tokenize all sorts of symbols.
Input: file name to read from.
Output: List of tokens which have a token type, value and line number.
*/

#pragma once
#include <iostream>
#include <istream>
#include <map>
#include <vector>

using namespace std;

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
   MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, MYEOF};

class Token
{
public:
  Token() {}
   Token(TokenType someToken, string someValue, int someLineNum) {
     myTokenType = someToken; value = someValue; lineNum = someLineNum;}
   void ToString();
   TokenType GetTokenType() const;
   string GetTokenString() const;

protected:
   map<TokenType, string> myMap = {
     {COMMA, "COMMA"},
     {PERIOD, "PERIOD"},
     {Q_MARK, "Q_MARK"},
     {LEFT_PAREN, "LEFT_PAREN"},
     {RIGHT_PAREN, "RIGHT_PAREN"},
     {COLON, "COLON"},
     {COLON_DASH, "COLON_DASH"},
     {MULTIPLY, "MULTIPLY"},
     {ADD, "ADD"},
     {SCHEMES, "SCHEMES"},
     {FACTS, "FACTS"},
     {RULES, "RULES"},
     {QUERIES, "QUERIES"},
     {ID, "ID"},
     {STRING, "STRING"},
     {COMMENT, "COMMENT"},
     {UNDEFINED, "UNDEFINED"},
     {MYEOF, "EOF"},
     };

private:
   TokenType myTokenType;
   string value;
   int lineNum;
};


//Threw in ID S before Schemes. Anytime theres an S, I made an extra ID. Also Unidentified are not numbers.
//'\t'
//Treated s as undefined, should be an ID s. It was after 'Here' and before another. Maybe I have one of them but not two of them
