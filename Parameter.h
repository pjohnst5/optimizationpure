#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "Token.h"


using namespace std;

class Parameter
{
public:
  Parameter();
  void AddToString(string);
  void Clear();
  string ToString();

private:
  string value;
  string out;
};
