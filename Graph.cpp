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


vector< vector<int> > Graph::DFSForward(stack<int> &localStack)
{
  int ruleIndex = 0;

  while (!localStack.empty()){
    ruleIndex = localStack.top();
    localStack.pop();

    innerSet.clear();
    if (graphMap[ruleIndex].GetVisited() == false){
      graphMap[ruleIndex].SetAsVisited();
      innerSet.push_back(ruleIndex);
      DFSscc(ruleIndex);
      mySets.push_back(innerSet);
    }
  }
  return mySets;
}

void Graph::DFSscc(int localInt)
{
  Node tempNode = graphMap[localInt];
  set<int> localAdjList = tempNode.GetAdjList();

  set<int>::iterator it;

  for (it = localAdjList.begin(); it != localAdjList.end(); ++it) {
    int indexOfNode = *it; // Note the "*" here

    if (graphMap[indexOfNode].GetVisited() == false){
      graphMap[indexOfNode].SetAsVisited();
      innerSet.push_back(indexOfNode);
      DFSscc(indexOfNode);
    }
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
