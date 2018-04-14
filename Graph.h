#pragma once
#include "Node.h"
#include <map>
#include <stack>
#include <vector>
#include <set>

using namespace std;

class Graph: public map<int,Node>
{
public:
  Graph() {}
  void AddToGraph(int, int);
  void AddToGraph(int);
  void SetToDependsOnSelf(int);
  map<int,Node> GetGraphMap();
  stack<int>& DFSReverse();
  void DFSMini(int);

  vector< set<int> > DFSForward();
  void DFSscc(int);
  void setStack(stack<int> &);
  stack<int> getStack();


private:
  map<int,Node> graphMap; //Node and its adjancey list
  stack<int> stackOInts;
  vector< set<int> > mySets;
  //set<int> innerSet;
  vector<int> test;
  set<int> outputSet;
};
