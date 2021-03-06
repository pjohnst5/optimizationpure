#pragma once
#include "Predicate.h"

using namespace std;

class Rule
{
public:
  Rule() {}
  void AddPredicate(Predicate);
  void Clear();
  string ToString();
  string finalToString();
  vector<Predicate> GetPredicates();
  string GetRuleHeadID();

private:
  vector<Predicate> rulesPredicates;
  string out;
};
