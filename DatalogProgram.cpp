#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(vector<Token> tokenVector)
{
  index = 0;
  this->tokenVector = tokenVector;
}

void DatalogProgram::AddSchemes(Predicate p)
{
  schemes.push_back(p);
}

void DatalogProgram::AddFacts(Predicate p)
{
  facts.push_back(p);
}

void DatalogProgram::AddToSet(string s)
{
  mySet.insert(s);
  return;
}

void DatalogProgram::AddToRules(Rule r)
{
  rules.push_back(r);
}

void DatalogProgram::AddQueries(Predicate p)
{
  queries.push_back(p);
}

void DatalogProgram::Print()
{
  cout << "Schemes(" << schemes.size() << "):" << endl;
  for (unsigned int i = 0; i < schemes.size(); ++i){
    cout << "  ";
    cout << schemes.at(i).ToString();
    cout << endl;
  }
  cout << "Facts(" << facts.size() << "):" << endl;
  for (unsigned int i = 0; i < facts.size(); ++i){
    cout << "  ";
    cout << facts.at(i).ToString();
    cout << "." << endl;
  }
  cout << "Rules(" << rules.size() << "):" << endl;
  for (unsigned int i = 0; i < rules.size(); ++i) {
    cout << "  ";
    cout << rules.at(i).ToString();
    cout << endl;
  }
  cout << "Queries(" << queries.size() << "):" << endl;
  for (unsigned int i = 0; i < queries.size(); ++i){
    cout << "  ";
    cout << queries.at(i).ToString();
    cout << "?";
    cout << endl;
  }
  cout << "Domain(" << mySet.size() << "):" << endl;
  for (set<string>::iterator it=mySet.begin(); it!=mySet.end(); ++it) {
    cout << "  ";
    cout << *it;
    cout<<"\n";
  }
}

vector<Predicate> DatalogProgram::GetSchemes()
{
  return schemes;
}

vector<Predicate> DatalogProgram::GetFacts()
{
  return facts;
}

vector<Predicate> DatalogProgram::GetQueries()
{
  return queries;
}

vector<Rule> DatalogProgram::GetRules()
{
  return rules;
}
