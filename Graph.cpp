#include "Graph.h"

void Graph::AddToGraph(int first, int second)
{
  graphMap[first].AddToAdjList(second);
  return;
}

void Graph::AddToGraph(int first)
{
  graphMap[first];
  return;
}

void Graph::SetToDependsOnSelf(int i)
{
  graphMap[i].SetNodeToDependsOnItself();
  return;
}

map<int,Node> Graph::GetGraphMap()
{
  return graphMap;
}

void Graph::setStack(stack<int> in) {
  stackOInts = in;
}

stack<int> Graph::getStack() {
  return stackOInts;
}

vector< set<int> > Graph::DFSForward()
{
  //cout << "HI " << endl;
  while (!stackOInts.empty()){
    DFSscc(stackOInts.top());
    stackOInts.pop();
    if (test.size() != 0){
      for (unsigned int i = 0; i < test.size(); i++){
        outputSet.insert(test.at(i));
      }
      mySets.push_back(outputSet);
      test.clear();
      outputSet.clear();
    }
  }
  return mySets;
}

void Graph::DFSscc(int localInt)
{
  if (!graphMap[localInt].GetVisited()){
    graphMap[localInt].SetAsVisited();
    set<int>::iterator it;
    for (it = (graphMap[localInt].GetAdjList()).begin(); it != (graphMap[localInt].GetAdjList()).end(); ++it) {
      DFSscc(*it);
    }
    test.push_back(localInt);
  }
  return;
}


stack<int> Graph::DFSReverse()
{
  map<int, Node>::iterator it = graphMap.begin();
  while (it != graphMap.end())
  {
    DFSMini(it->first);
    it++;
  }
  return stackOInts;
}

void Graph::DFSMini(int localInt)
{
  if (!graphMap[localInt].GetVisited()){
    graphMap[localInt].SetAsVisited();
    set<int>::iterator it;
    for (it = graphMap[localInt].GetAdjList().begin(); it != graphMap[localInt].GetAdjList().end(); ++it) {
      DFSMini(*it);
    }
    stackOInts.push(localInt);
  }
  return;
}
