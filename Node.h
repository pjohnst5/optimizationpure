#pragma once
#include <iostream>
#include <set>

using namespace std;

class Node
{
public:
  Node() {visited = false; dependsOnItself = false;}
  void AddToAdjList(int &);
  void SetNodeToDependsOnItself();
  bool GetDependsOnItself();
  void Clear();
  void Print();
  bool GetVisited();
  void SetAsVisited();
  set<int> GetAdjList();
  int GetAdjListSize();
private:
  set<int> adjList;
  bool visited;
  bool dependsOnItself;
};
