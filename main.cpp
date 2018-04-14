/*
Paul Johnston, Section 1, pjohnst5@icloud.com
Purpose: Tokenize all sorts of symbols.
Input: file name to read from.
Output: List of tokens which have a token type, value and line number.
*/
#include <iostream>
#include "DatalogProgram.h"
#include "Database.h"
#include "Scanner.h"
#include "Parser.h"

using namespace std;

int main(int arg, char* args[])
{
    Scanner myScanner(args[1]);
    DatalogProgram myDatalogProgram;
    Database myDatabase;

    myScanner.Scan();
    //myScanner.Print();
    Parser myParser(myScanner.getTokens());

    myDatalogProgram = myParser.Parse();

    if (myParser.getFailedOrNot() == false){
      //myDatalogProgram.Print();
      
      myDatabase.SetDatalogProgram(myDatalogProgram);
      myDatabase.ConstructRelations();
    //  myDatabase.Print();
      myDatabase.InterpretRules();
      myDatabase.InterpretQueries();
    }


  return 0;
}
