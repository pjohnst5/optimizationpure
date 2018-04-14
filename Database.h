#pragma once
#include "Relation.h"
#include "DatalogProgram.h"
#include "Graph.h"
#include <map>
#include <stack>
#include <iostream>

using namespace std;

class Database
{
public:
  Database() {noIDs = true; numPasses = 0;}
  void ConstructRelations();
  void PopulateRelations();
  void Print();
  void SetDatalogProgram(DatalogProgram &);
  void InterpretQueries();
  void ConstructSCCs();
  void MakeForests();
  void MakeVectorOfRules();
  void InterpretRules();
  void EvaluateRules(vector<Rule> &);
  int GetSizeOfDatabase();
  Schema MakeHeadSchema(Predicate &);
  vector<int> MakeVectorOfIndexes(Schema &,Schema &);
  Relation EvaluateQuery(Predicate);
  bool IsThereADuplicate(vector<Parameter> &,vector<int> &,int);
  void PrintGraph(Graph &);
  void PrintSCC(int);
private:
  DatalogProgram myDP;
  Graph originalGraphNodes;
  Graph reverseForest;
  map<string,Relation> myMapOfRelations;
  bool noIDs;
  int numPasses;
  stack<int> myStack;
  vector < set<int> > mySccs;
  vector< vector<Rule> > myRules;
};
