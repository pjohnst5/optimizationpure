#include "Parser.h"

DatalogProgram Parser::Parse()
{
  try {
    MyDatalogProgram();
    Match(index,MYEOF);
    //cout << "Success!" << endl;
  }
  catch (Token badToken){
    failed = true;
    cout << "Failure!" << endl;
    cout << "  ";
    badToken.ToString();
  }
  return hello;
}

bool Parser::getFailedOrNot()
{
  return failed;
}

void Parser::MyDatalogProgram()   //Done
{
//  IgnoreComments();
  Match(index,SCHEMES);
  Match(index,COLON);
  scheme();
  schemeList();
  Match(index,FACTS);
  Match(index,COLON);
  factList();
  Match(index,RULES);
  Match(index,COLON);
  onRules = true;
  ruleList();
  onRules = false;
  Match(index,QUERIES);
  Match(index,COLON);
  query();
  queryList();
}

void Parser::scheme()  //Done
{
  //IgnoreComments();
  myPredicate.SetHeadID(myVector.at(index));
  Match(index,ID);
  Match(index,LEFT_PAREN);
  myParameter.AddToString(myVector.at(index).GetTokenString());
  myPredicate.AddParameter(myParameter);
  myParameter.Clear();
  Match(index,ID);

  idList();

  hello.AddSchemes(myPredicate);
  myPredicate.Clear();
  Match(index,RIGHT_PAREN);
  return;
}


void Parser::idList()   //Done
{
//  IgnoreComments();
  //cout << "DId I make it?" << endl;
  if (myVector.at(index).GetTokenType() == COMMA){
    Match(index, COMMA);
    //myParameter.SetParameter(myVector.at(index));
    myParameter.AddToString(myVector.at(index).GetTokenString());
    myPredicate.AddParameter(myParameter);
    myParameter.Clear();
    Match(index,ID);
    idList();
    return;
  }
  else {
    //cout << "I did nothing in idlist " << endl;
    return;
  }
}


void Parser::schemeList() //Done
{

  if (myVector.at(index).GetTokenType() == ID){
  //  cout << "I checked for ID" << endl;
    scheme();
    schemeList();
    return;
  }
  else {
  //  cout << "I did nothing in schemeList" << endl;
    return;
  }
}

void Parser::factList()   //Done
{
  //IgnoreComments();
  if (myVector.at(index).GetTokenType() == ID){
    fact();
    factList();
    return;
  }
  else {
    //cout << "I did nothing in factList" << endl;
    return;
  }
}

void Parser::fact()      //Done
{
  myPredicate.SetHeadID(myVector.at(index));
  Match(index,ID);
  Match(index,LEFT_PAREN);
  //myParameter.SetParameter(myVector.at(index));
  myParameter.AddToString(myVector.at(index).GetTokenString());
  hello.AddToSet(myParameter.ToString());
  myPredicate.AddParameter(myParameter);
  myParameter.Clear();
  Match(index,STRING);

  stringList();
  hello.AddFacts(myPredicate);
  myPredicate.Clear();
  Match(index,RIGHT_PAREN);
  Match(index,PERIOD);
}

void Parser::stringList()     //Done
{
//  IgnoreComments();
  if (myVector.at(index).GetTokenType() == COMMA){
    Match(index, COMMA);
  //  myParameter.SetParameter(myVector.at(index));
    myParameter.AddToString(myVector.at(index).GetTokenString());
    hello.AddToSet(myParameter.ToString());
    myPredicate.AddParameter(myParameter);
    myParameter.Clear();
    Match(index,STRING);
    stringList();
    return;
  }
  else {
  //  cout << "I did nothing in stringList" << endl;
    return;
  }
}

void Parser::ruleList()      //Done
{
  //IgnoreComments();
  if (myVector.at(index).GetTokenType() == ID){
    rule();
    ruleList();
    return;
  }
  else {
    //cout << "I did nothing in ruleList" << endl;
    return;
  }

}

void Parser::rule()   //Done
{
  //IgnoreComments();
  headPredicate();

  Match(index,COLON_DASH);

  predicate();
  predicateList();
  hello.AddToRules(myRule);
  myRule.Clear();
  Match(index,PERIOD);
  return;
}

void Parser::headPredicate()    //Done
{
    myPredicate.SetHeadID(myVector.at(index));
    Match(index, ID);
    Match(index,LEFT_PAREN);
    myParameter.AddToString(myVector.at(index).GetTokenString());
    myPredicate.AddParameter(myParameter);
    myParameter.Clear();
    Match(index, ID);

    idList();
    myRule.AddPredicate(myPredicate);
    myPredicate.Clear();
    Match(index,RIGHT_PAREN);
  return;
}

void Parser::predicate()  //Done
{
  myPredicate.SetHeadID(myVector.at(index));
  Match(index,ID);
  Match(index,LEFT_PAREN);

  parameter();

  parameterList();
  if (onRules){
    myRule.AddPredicate(myPredicate);
    myPredicate.Clear();
  }
  else {
    hello.AddQueries(myPredicate);
    myPredicate.Clear();
  }

  Match(index,RIGHT_PAREN);
  return;
}

void Parser::predicateList()    //Done
{
//  IgnoreComments();
  if (myVector.at(index).GetTokenType() == COMMA){
    Match(index, COMMA);
    predicate();
    predicateList();
    return;
  }
  else {
    //cout << "I did nothing in predicateList " << endl;
    return;
  }
}

void Parser::parameter()  //Done
{
//  IgnoreComments();
  if (myVector.at(index).GetTokenType() == STRING){
    myParameter.AddToString(myVector.at(index).GetTokenString());
    Match(index,STRING);
  }
  else if (myVector.at(index).GetTokenType() == ID){
    myParameter.AddToString(myVector.at(index).GetTokenString());
    Match(index,ID);
  }
  else {
    expression();
  }
  myPredicate.AddParameter(myParameter);
  myParameter.Clear();
  return;
}

void Parser::parameterList()  //Done
{
//  IgnoreComments();
  if (myVector.at(index).GetTokenType() == COMMA){
    Match(index, COMMA);
    parameter();
    parameterList();
    return;
  }
  else {
  //  cout << "I did nothing in paramterList" << endl;
    return;
  }

}

void Parser::expression()     //Done
{
  myParameter.AddToString(myVector.at(index).GetTokenString());
  Match(index,LEFT_PAREN);

  parameter();

  myOperator();

  parameter();
  myParameter.AddToString(myVector.at(index).GetTokenString());
  Match(index,RIGHT_PAREN);
  return;
}

void Parser::myOperator()   //Done
{
//  IgnoreComments();
  if (myVector.at(index).GetTokenType() == ADD){
    myParameter.AddToString(myVector.at(index).GetTokenString());
    Match(index,ADD);
  }
  else {
    myParameter.AddToString(myVector.at(index).GetTokenString());
    Match(index,MULTIPLY);
  }
  return;
}

void Parser::query()      //Done
{

  predicate();
  Match(index,Q_MARK);
  return;
}

void Parser::queryList()     //Done
{
//  IgnoreComments();
  if (myVector.at(index).GetTokenType() == ID){
    query();
    queryList();
    return;
  }
  else {
    //cout << "I did nothing in queryList" << endl;
    return;
  }
}

void Parser::Match(int& index, TokenType expected)
{
  /*
  while (myVector.at(index).GetTokenType() == COMMENT) {
  //  cout << "Comment ignored" << endl;
    index++;
  }
  */
  if (myVector.at(index).GetTokenType() == expected){
   //cout << expected << " TokenType matched" << endl;
    index++;
  }
  else {
  //  cout << "Throwing exception" << endl;
    throw myVector.at(index);
  }
  return;
}

/*
void Parser::IgnoreComments()
{
  while (myVector.at(index).GetTokenType() == COMMENT) {
    //cout << "Special Comment ignored" << endl;
    index++;
  }
}
*/
