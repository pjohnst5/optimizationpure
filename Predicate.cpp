#include "Predicate.h"

Predicate::Predicate() //Took out Token and bool here
{
  //this->myBool = myBool;
  //headID = someToken.GetTokenString();
}

void Predicate::Clear()
{
  listOfParameters.clear();
  headID = "";
}

void Predicate::SetHeadID(Token t)
{
  headID = t.GetTokenString();
}

void Predicate::AddParameter(Parameter p)
{
  listOfParameters.push_back(p);
}

vector<Parameter> Predicate::GetParameters()
{
  return listOfParameters;
}

string Predicate::GetHeadID()
{
  return headID;
}

string Predicate::ToString()
{
  out = headID + "(";
  for (unsigned int i = 0; i < listOfParameters.size(); ++i){
    out += listOfParameters.at(i).ToString();
    if (i < listOfParameters.size() - 1){
      out += ",";
    }
  }
  out += ")";
  return out;
}
