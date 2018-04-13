#include "Database.h"

void Database::ConstructRelations()
{
  vector<Predicate> tempSchemes = myDP.GetSchemes();
  vector<Parameter> tempParameters;
  Schema tempSchema;
  Relation tempRelation;
  string tempNameOfRelation;
  set<Tuple> tempSet;

  for (unsigned int i = 0; i < tempSchemes.size(); ++i) {
    tempNameOfRelation = tempSchemes.at(i).GetHeadID();
    tempParameters = tempSchemes.at(i).GetParameters();
    for (unsigned int j = 0; j < tempParameters.size(); ++j){
      tempSchema.push_back((tempParameters.at(j)).ToString());
    }
    tempRelation = Relation(tempNameOfRelation,tempSchema,tempSet);
    myMapOfRelations[tempNameOfRelation] = tempRelation;
    tempSchema.clear();
  }
  PopulateRelations();
  return;
}

void Database::PopulateRelations()
{
  vector<Predicate> tempFacts = myDP.GetFacts();
  vector<Parameter> tempParameters;
  Tuple tempTuple;
  string tempNameOfRelation;

  for (unsigned int i = 0; i < tempFacts.size(); ++i){
    tempNameOfRelation = tempFacts.at(i).GetHeadID();
    tempParameters = tempFacts.at(i).GetParameters();
    for (unsigned int j = 0; j < tempParameters.size(); ++j){
      tempTuple.push_back((tempParameters.at(j)).ToString());
    }
    myMapOfRelations[tempNameOfRelation].AddToSet(tempTuple);
    tempTuple.clear();
  }
  return;
}

int Database::GetSizeOfDatabase()
{
  map<string, Relation>::iterator it = myMapOfRelations.begin();
  int totalSize = 0;

	while (it != myMapOfRelations.end())
	{
		Relation tempRelation = it->second;
    totalSize = totalSize + tempRelation.GetSize();
		it++;
	}

  return totalSize;
}


void Database::MakeForests()
{
  vector<Rule> tempRules = myDP.GetRules();
  vector<Predicate> tempPredicates;
  string headPredicateID;
  string otherHeadPredicateID;

  for (unsigned int i = 0; i < tempRules.size(); ++i){ //Just remember to start reading the predicates at index 1, not at 0.
    tempPredicates = tempRules.at(i).GetPredicates();
    for (unsigned int j = 1; j < tempPredicates.size(); ++j){
      headPredicateID = tempPredicates.at(j).GetHeadID();
      for (unsigned int k = 0; k < tempRules.size(); ++k){
        otherHeadPredicateID = tempRules.at(k).GetRuleHeadID();
        if (headPredicateID == otherHeadPredicateID && k == i){
          originalGraphNodes.AddToGraph(i,k);
          reverseForest.AddToGraph(k,i);
          originalGraphNodes.SetToDependsOnSelf(i);
        }
        else if (headPredicateID == otherHeadPredicateID){
          originalGraphNodes.AddToGraph(i,k);
          reverseForest.AddToGraph(k,i);
        }
        else {
          originalGraphNodes.AddToGraph(i);
          reverseForest.AddToGraph(k);
        }
      }
    }
  }
  /*
  cout << "Printing graph with original Nodes" << endl;
  PrintGraph(originalGraphNodes);
  cout << endl;
  cout << "Printing graph with reverse nodes" << endl;
  PrintGraph(reverseForest);
  */
  return;
}

void Database::ConstructSCCs()
{
  MakeForests();

  myStack = reverseForest.DFSReverse();
/*
  stack<int> myStackPrint = myStack;
  cout << "Printing the stack" << endl;

  while (!myStackPrint.empty()){
    int num = myStackPrint.top();
    cout << num << endl;
    myStackPrint.pop();
  }
  cout << endl;
*/
  mySccs = originalGraphNodes.DFSForward(myStack);

  MakeVectorOfRules();
}


void Database::MakeVectorOfRules()
{
  vector<Rule> tempRules;
  vector<Rule> realRules = myDP.GetRules();

  for (unsigned int i = 0; i < mySccs.size(); ++i){
    vector<int> tempScc = mySccs.at(i);
    for (unsigned int j = 0; j < tempScc.size(); ++j) {
      tempRules.push_back(realRules.at(tempScc.at(j)));
    }
    myRules.push_back(tempRules);
    tempRules.clear();
  }
  return;
}


void Database::InterpretRules()
{
  ConstructSCCs();
/*
  cout << "Printing vectors of Rules in their SCCs" << endl;
  for (unsigned int i = 0; i < myRules.size(); ++i){
    cout << "SCC: " << i << endl;
    for (unsigned int j = 0; j < myRules.at(i).size(); ++j){
      cout << myRules.at(i).at(j).ToString() << endl;
    }
    cout << endl;
  }
*/

  cout << "Dependency Graph" << endl;
  PrintGraph(originalGraphNodes);

/*
  cout <<"Geting depends on itself from the map" << endl;
  map<int,Node> localGraphMap = originalGraphNodes.GetGraphMap();
  map<int, Node>::iterator it = localGraphMap.begin();
  int nodeInt = 0;

  while (it != localGraphMap.end())
  {
    nodeInt = it->first;
    cout << "R" << nodeInt << ":";
    Node tempNode = it->second;
    if (tempNode.GetDependsOnItself()){
      cout << "IS dependent on itself" << endl;
    }
    else {
      cout << "Is NOT dependent on itself" << endl;
    }
    cout << endl;
    it++;
  }
  cout << endl;
*/

  map<int,Node> tempGraphMap = originalGraphNodes.GetGraphMap();

  cout << "Rule Evaluation" << endl;
  for (unsigned int i = 0; i < myRules.size(); ++i){
    if(myRules.at(i).size() == 1 && tempGraphMap[mySccs.at(i).at(0)].GetDependsOnItself() == false){
      EvaluateRules(myRules.at(i));
      cout << "1 passes: R" << mySccs.at(i).at(0) << endl;
    }
    else {
      int initialSize = 0;
      int endingSize = 0;
      numPasses = 0;
      do{
        initialSize = GetSizeOfDatabase();
        EvaluateRules(myRules.at(i));
        endingSize = GetSizeOfDatabase();
        numPasses++;
      } while(initialSize != endingSize);
      set<int> sccInts;
      for (unsigned int k = 0; k < mySccs.at(i).size(); ++k){ //makes set
        sccInts.insert(mySccs.at(i).at(k));
      }
      cout << numPasses << " passes: ";
      for (set<int>::iterator it=sccInts.begin(); it!=sccInts.end(); ++it){
        int someInt = *it;
        cout << "R" << someInt;
        ++it;
        if(it != sccInts.end()){
          cout << ",";
        }
        --it;
      }//End of printing set
      cout << endl;
    }//End of else
  }
cout << endl;
  return;
}


void Database::EvaluateRules(vector<Rule> &tempRules)
{
  Relation joinedRelation;
  Relation secondRelation ;
  //vector<Rule> tempRules = myDP.GetRules();
  vector<Predicate> tempPredicates;
  Schema headSchema;
  string headRelationName;
  vector<int> indexesToProject;
  Schema joinedSchema;

  for (unsigned int i = 0; i < tempRules.size(); ++i){
    tempPredicates = tempRules.at(i).GetPredicates();
    headRelationName = tempPredicates.at(0).GetHeadID();
    headSchema = MakeHeadSchema(tempPredicates.at(0));
    joinedRelation = EvaluateQuery(tempPredicates.at(1)); //make first predicate
    for (unsigned int j = 2; j < tempPredicates.size(); ++j){     //Join predicates (queries).
      secondRelation  = EvaluateQuery(tempPredicates.at(j));
      joinedRelation = joinedRelation.Join(secondRelation );
    }
    //now we project and union
    joinedSchema = joinedRelation.GetSchema();
    indexesToProject = MakeVectorOfIndexes(headSchema,joinedSchema);
    joinedRelation = joinedRelation.Project(indexesToProject);
    myMapOfRelations[headRelationName] = myMapOfRelations[headRelationName].Union(joinedRelation); //Does fetching a relation then setting it to something else change the original?
  }
  return;
}

vector<int> Database::MakeVectorOfIndexes(Schema headSchema, Schema joinedSchema)
{
  vector<int> returnVector;

  for (unsigned int i = 0; i < headSchema.size(); i++){
    for (unsigned int j = 0; j < joinedSchema.size(); j++){
      if (headSchema.at(i) == joinedSchema.at(j)){
        returnVector.push_back(j);
      }
    }
  }
  return returnVector;
}

Schema Database::MakeHeadSchema(Predicate headPredicate)
{
  Schema newSchema;
  vector<Parameter> tempParameters = headPredicate.GetParameters();

  for (unsigned int j = 0; j < tempParameters.size(); ++j){
    newSchema.push_back((tempParameters.at(j)).ToString());
  }
  return newSchema;
}


void Database::InterpretQueries()
{
  vector<Predicate> tempQueries = myDP.GetQueries();
  Relation result;
  vector<int> columnsToProject;
  Schema localSchema;
  set<Tuple> localSet;

  cout << "Query Evaluation" << endl;
  for (unsigned int i = 0; i < tempQueries.size(); ++i) {
    cout << tempQueries.at(i).ToString() << "?";
    result = EvaluateQuery(tempQueries.at(i));
    localSet = result.GetSetOfTuples();
    if (localSet.size() == 0){
      cout << " No" << endl;
    }
    else {
      cout << " Yes(" << localSet.size() << ")" << endl;
      if (noIDs == false){
        localSchema = result.GetSchema();
        for (set<Tuple>::iterator it=localSet.begin(); it!=localSet.end(); ++it) {
          Tuple innerTuple = *it;
          cout << "  ";
          for (unsigned int i = 0; i < localSchema.size(); i++){
            if (i != localSchema.size() -1){
              cout << localSchema.at(i) << "=" << innerTuple.at(i) << ", ";
            }
            else {
              cout << localSchema.at(i) << "=" << innerTuple.at(i) << endl;
            }
          }
        }
      }
    }
  }

  return;
}

Relation Database::EvaluateQuery(Predicate localQuery)
{
  Relation localRelation;
  localRelation = myMapOfRelations[localQuery.GetHeadID()];
  vector<Parameter> localParameters = localQuery.GetParameters();
  vector<int> columnsToProject;
  Schema newSchema;
  bool duplicateFound = false;
  noIDs = true;


  for (unsigned int i = 0; i < localParameters.size(); ++i) {
    if ((localParameters.at(i).ToString())[0] == '\''){ //Parameter is a string
      localRelation = localRelation.Select(i,localParameters.at(i).ToString());
    }
    else { //Parameter is an ID
      noIDs = false;
      duplicateFound = false;

      duplicateFound = IsThereADuplicate(localParameters,columnsToProject,i);
      /*
      for (unsigned int k = 0; k < columnsToProject.size(); ++k){
        if (localParameters.at(i).ToString() == localParameters.at(columnsToProject.at(k)).ToString()){
          duplicateFound = true;
        }
      }
      */
      if (duplicateFound == false){
        columnsToProject.push_back(i);
        newSchema.push_back(localParameters.at(i).ToString());
      }
      for (unsigned int j = i + 1; j < localParameters.size(); ++j) {
        if (localParameters.at(i).ToString() == localParameters.at(j).ToString()) {
          localRelation = localRelation.Select(i,j);
        }
      }
    }
  }
  if(noIDs == true){
    return localRelation;
  }
  localRelation = localRelation.Project(columnsToProject);
  localRelation = localRelation.Rename(newSchema);

  return localRelation;
}

bool Database::IsThereADuplicate(vector<Parameter> localParameters, vector<int> columnsToProject, int i)
{
  for (unsigned int k = 0; k < columnsToProject.size(); ++k){
    if (localParameters.at(i).ToString() == localParameters.at(columnsToProject.at(k)).ToString()){
      return true;
    }
  }
  return false;
}

void Database::SetDatalogProgram(DatalogProgram &localDP)
{
  myDP = localDP;
  return;
}

void Database::Print()
{
  map<string, Relation>::iterator it = myMapOfRelations.begin();

	while (it != myMapOfRelations.end())
	{
		Relation tempRelation = it->second;
    tempRelation.Print();
		it++;
	}
  return;
}

void Database::PrintGraph(Graph &localGraph)
{
  map<int,Node> localGraphMap = localGraph.GetGraphMap();
  map<int, Node>::iterator it = localGraphMap.begin();
  int nodeInt = 0;

  while (it != localGraphMap.end())
  {
    nodeInt = it->first;
    cout << "R" << nodeInt << ":";
    Node tempNode = it->second;
    tempNode.Print();
    cout << endl;
    it++;
  }
  cout << endl;
  return;
}
