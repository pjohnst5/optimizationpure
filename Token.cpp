/*
Paul Johnston, Section 1, pjohnst5@icloud.com
Purpose: Tokenize all sorts of symbols.
Input: file name to read from.
Output: List of tokens which have a token type, value and line number.
*/
#include "Token.h"

void Token::ToString()
{
   cout << "(" << myMap[myTokenType] << ",";
   cout << "\"" << value << "\"" << ",";
   cout << lineNum << ")" << endl;
   return;
}

TokenType Token::GetTokenType() const
{
  return myTokenType;
}

string Token::GetTokenString() const{
  return value;
}
