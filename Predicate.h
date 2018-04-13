#pragma once
#include "Parameter.h"
#include <sstream>

using namespace std;

class Predicate
{
public:
  Predicate();
  void Clear();
  void SetHeadID(Token);
  void AddParameter(Parameter);
  vector<Parameter> GetParameters();
  string GetHeadID();
  string ToString();


private:
  bool myBool;
  string headID;
  vector<Parameter> listOfParameters;
  string out;
};
