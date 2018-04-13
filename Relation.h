#pragma once
#include "Tuple.h"
#include "Schema.h"
#include <set>
#include <iomanip>
#include <unordered_map>

using namespace std;

class Relation
{
public:
  Relation() {}
  Relation(string, Schema, set<Tuple>);
  Relation Select(int, string);
  Relation Select(int, int);
  Relation Project(vector<int>);
  Relation Rename(Schema);
  Relation Union(Relation &);
  Relation Join(Relation &);
  vector<int> CheckForMatchingIDs(Schema);
  bool Joinable(Schema,Schema,Tuple,Tuple);
  Tuple ActuallyJoinTwoTuples(Tuple,Tuple,vector<int>);
  Relation MakeNewRelation(vector<int>, Schema);
  void AddToSet(Tuple);
  Schema GetSchema();
  set<Tuple> GetSetOfTuples();
  void SetTuples(set<Tuple> &);
  void Print();
  int GetSize();

private:
  string name;
  Schema mySchema;
  set<Tuple> mySetOfTuples;
  Tuple myT;

};
