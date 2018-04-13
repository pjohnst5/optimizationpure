#pragma once
#include "Rule.h"
#include "Predicate.h"
#include <set>

using namespace std;

class DatalogProgram
{
public:
  DatalogProgram() {}
  DatalogProgram(vector<Token>);
  void AddSchemes(Predicate);
  void AddFacts(Predicate);
  void AddToSet(string);
  void AddToRules(Rule);
  void AddQueries(Predicate);
  void Print();
  vector<Predicate> GetSchemes();
  vector<Predicate> GetFacts();
  vector<Predicate> GetQueries();
  vector<Rule> GetRules();

private:
  int index;
  set<string> mySet;
  vector<Token> tokenVector;
  vector<Predicate> schemes;
  vector<Predicate> facts;
  vector<Rule> rules;
  vector<Predicate> queries;
};
