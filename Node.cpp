#include "Node.h"

void Node::AddToAdjList(int &localInt)
{
  adjList.insert(localInt);
  return;
}

void Node::Clear()
{
  adjList.clear();
  visited = false;
}

void Node::Print()
{
  for (set<int>::iterator it=adjList.begin(); it!=adjList.end(); ++it) {
    int someInt = *it;
    cout << "R" << someInt;
    ++it;
    if(it != adjList.end()){
      cout << ",";
    }
    --it;
  }
}

bool Node::GetVisited()
{
  return visited;
}

void Node::SetAsVisited()
{
  visited = true;
}

set<int> Node::GetAdjList()
{
  return adjList;
}

int Node::GetAdjListSize()
{
  return adjList.size();
}

void Node::SetNodeToDependsOnItself()
{
  dependsOnItself = true;
  return;
}

bool Node::GetDependsOnItself()
{
  return dependsOnItself;
}
