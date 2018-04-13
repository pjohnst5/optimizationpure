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
  stack<int> DFSReverse();
  void DFSMini(int);

  vector< vector<int> > DFSForward(stack<int> &);
  void DFSscc(int);


private:
  map<int,Node> graphMap; //Node and its adjancey list
  stack<int> stackOInts;
  vector< vector<int> > mySets;
  vector<int> innerSet;
};
