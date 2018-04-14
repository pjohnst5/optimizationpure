#include "Rule.h"


void Rule::AddPredicate(Predicate newPredicate)
{
    rulesPredicates.push_back(newPredicate);
}

void Rule::Clear()
{
  rulesPredicates.clear();
  out = "";
}

string Rule::ToString()
{
  out = rulesPredicates.at(0).ToString();
  out += " :- ";
  for (unsigned int i = 1; i < rulesPredicates.size(); ++i){
    out += rulesPredicates.at(i).ToString();
    if (i < rulesPredicates.size() - 1){
      out += ",";
    }
  }
  out += ".";
  return out;
}

string Rule::finalToString() 
{
    out = rulesPredicates.at(0).ToString();
    out += " :- ";
    for (unsigned int i = 1; i < rulesPredicates.size(); ++i){
      out += rulesPredicates.at(i).ToString();
      if (i < rulesPredicates.size() - 1){
        out += ",";
      }
    }
    return out;
}

vector<Predicate> Rule::GetPredicates()
{
  return rulesPredicates;
}

string Rule::GetRuleHeadID()
{
  return rulesPredicates.at(0).GetHeadID();
}
