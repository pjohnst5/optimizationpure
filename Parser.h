#pragma once
#include "Scanner.h"
#include "DatalogProgram.h"

using namespace std;

class Parser
{

public:
  Parser(vector<Token> input) {myVector = input; index = 0; onRules = false; failed = false;}
  ~Parser(){}
  DatalogProgram Parse();
  void MyDatalogProgram();
  void Match(int& index, TokenType expected);
  void scheme();
  void idList();
  void schemeList();
  void factList();
  void fact();
  void stringList();
  void ruleList();
  void rule();
  void headPredicate();
  void predicate();
  void predicateList();
  void parameter();
  void parameterList();
  void expression();
  void myOperator();
  void query();
  void queryList();
  bool getFailedOrNot();
  //void IgnoreComments();


private:
   bool failed;
   bool onRules;
   vector<Token> myVector;
   int index;
   Predicate tempPredicate;
   vector<Parameter> tempParameters;
   DatalogProgram hello;
   Predicate myPredicate;
   Parameter myParameter;
   Rule myRule;
};
