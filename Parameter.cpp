#include "Parameter.h"

Parameter::Parameter() //Took out Token t
{
  value = "";
}

void Parameter::Clear()
{
  value = "";
}

void Parameter::AddToString(string s)
{
  if (value == ""){
    value = s;
  }
  else {
    value += s;
  }
}

string Parameter::ToString()
{
  return value;
}
