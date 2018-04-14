#include "Relation.h"

Relation::Relation(string temp, Schema localSchema, set<Tuple> localTuples)
{
  name = temp;
  mySchema = localSchema;
  mySetOfTuples = localTuples;
}

Relation Relation::Select(int localInt, string localString)
{
  set<Tuple> newSet;

  for (set<Tuple>::iterator it=mySetOfTuples.begin(); it!=mySetOfTuples.end(); ++it) {
    Tuple innerTuple = *it;
      if (innerTuple.at(localInt) == localString){
        newSet.insert(innerTuple);
      }
  }
  Relation newRelation = Relation(name,mySchema,newSet);
  return newRelation;
}

Relation Relation::Select(int localInt, int secondInt)
{
  set<Tuple> newSet;

  for (set<Tuple>::iterator it=mySetOfTuples.begin(); it!=mySetOfTuples.end(); ++it) {
    Tuple innerTuple = *it;
      if (innerTuple.at(localInt) == innerTuple.at(secondInt)){
        newSet.insert(innerTuple);
      }
  }
  Relation newRelation = Relation(name,mySchema,newSet);
  return newRelation;
}

Relation Relation::Project(vector<int> & localVector)
{
  Schema newSchema;
  set<Tuple> newSet;
  vector<Tuple> tempV;
  Tuple tempTuple;
  Tuple innerTuple;
  Tuple newTuple;

  int index = 0;

  for (unsigned int i = 0; i < localVector.size(); ++i){
    index = localVector.at(i);
    newSchema.push_back(mySchema.at(index));

    if (i == 0) {
      for (set<Tuple>::iterator it=mySetOfTuples.begin(); it!=mySetOfTuples.end(); ++it) {
        innerTuple = *it;
        tempTuple.push_back(innerTuple.at(index));
        tempV.push_back(tempTuple);
        tempTuple.clear();
      }
    }
    else {
      int counter = 0;
      for (set<Tuple>::iterator it=mySetOfTuples.begin(); it!=mySetOfTuples.end(); ++it) {
        innerTuple = *it;
        tempV.at(counter).push_back(innerTuple.at(index));
        counter++;
      }
    }
  }

  for (unsigned int k = 0; k < tempV.size(); k++){
    newSet.insert(tempV.at(k));
  }
  Relation newRelation = Relation("New Relation",newSchema, newSet);
  return newRelation;
}

Relation Relation::Rename(Schema & localSchema)
{
  /*
  if (localSchema.size() != mySchema.size()){
    cout << "Number of arguments do not match" << endl;
    Relation oldRelation = Relation(name,mySchema,mySetOfTuples);
    return oldRelation;
  }
  */
  unordered_map<string, int> hashtable;
  for (unsigned int i = 0; i < localSchema.size(); ++i) {
    unordered_map<string,int>::const_iterator got = hashtable.find (localSchema.at(i));
    if (got == hashtable.end()){
    //  cout << "Duplicate not found, adding " << localSchema.at(i) << endl;
      hashtable.emplace(localSchema.at(i), i);
    }
    else {
      cout << "Found duplicate " << localSchema.at(i) << " , exiting out" << endl << endl;
      Relation oldRelation = Relation(name,mySchema,mySetOfTuples);
      return oldRelation;
    }
  }

  Relation newRelation = Relation(name, localSchema, mySetOfTuples);
  return newRelation;
}



Relation Relation::Union(Relation &givenRelation)
{
    Relation newRelation;
    set<Tuple> givenSet = givenRelation.GetSetOfTuples();
    set<Tuple> newSet = mySetOfTuples;

    for (set<Tuple>::iterator it=givenSet.begin(); it!=givenSet.end(); ++it) {
      Tuple innerTuple = *it;
      if (newSet.insert(innerTuple).second){
        cout << "  ";
         for (unsigned int i = 0; i < mySchema.size(); i++) {
          if (i == mySchema.size()-1){
            cout << mySchema.at(i) << "=" << innerTuple.at(i) << endl;  
          }
          else {
            cout << mySchema.at(i) << "=" << innerTuple.at(i) << ", ";
          }
          
         }
      }
    }
    newRelation = Relation(name,mySchema,newSet);
    return newRelation;
}

Relation Relation::Join(Relation &givenRelation)
{
  Schema givenSchema = givenRelation.GetSchema();
  vector<int> duplicateIDsVector = CheckForMatchingIDs(givenSchema); //Gives indexes of where ids don't match
  Relation newRelation = MakeNewRelation(duplicateIDsVector, givenSchema);
  set<Tuple> givenSetOfTuples = givenRelation.GetSetOfTuples();
  set<Tuple> newSetOfTuples;
  Tuple t;

  for (set<Tuple>::iterator it=mySetOfTuples.begin(); it!=mySetOfTuples.end(); ++it) {
    Tuple outerTuple = *it;

    for (set<Tuple>::iterator lit=givenSetOfTuples.begin(); lit!=givenSetOfTuples.end(); ++lit) {
      Tuple innerTuple = *lit;

      if (Joinable(mySchema,givenSchema,outerTuple,innerTuple)){
        t = ActuallyJoinTwoTuples(outerTuple,innerTuple,duplicateIDsVector);
        newSetOfTuples.insert(t);
      }

    }
  }

  newRelation.SetTuples(newSetOfTuples);

  return newRelation;
}

Tuple Relation::ActuallyJoinTwoTuples(Tuple & t1, Tuple & t2, vector<int> & duplicateIDsVector)
{
  Tuple tupleToReturn = t1;

  for (unsigned int i = 0; i < duplicateIDsVector.size(); ++i){
    int index = duplicateIDsVector.at(i);
    tupleToReturn.push_back(t2.at(index));
  }

  return tupleToReturn;
}

bool Relation::Joinable(Schema & s1, Schema & s2, Tuple & t1, Tuple & t2)
{
  for (unsigned int i = 0; i < s1.size(); ++i){
    for (unsigned int j = 0; j < s2.size(); ++j){
      if (s1.at(i) == s2.at(j)){
        if (t1.at(i) != t2.at(j)){
          return false;
        }
      }
    }
  }
  return true;
}


Relation Relation::MakeNewRelation(vector<int> & localVectorofInts, Schema & givenSchema)
{
  Schema newSchema = mySchema;
  set<Tuple> newSet;

  for (unsigned int i = 0; i < localVectorofInts.size(); ++i){
    newSchema.push_back(givenSchema.at(localVectorofInts.at(i)));
  }

  Relation newRelation = Relation("New Relation",newSchema,newSet);

  return newRelation;
}


vector<int> Relation::CheckForMatchingIDs(Schema & givenSchema)// returns indexes of not repeat ID's in given schema.
{
  vector<int> indexesOfSameIDsNot;
  bool repeatID = false;

  for (unsigned int i = 0; i < givenSchema.size(); i++){
    for (unsigned int j = 0; j < mySchema.size(); j++){
      if (givenSchema.at(i) == mySchema.at(j)){
        repeatID = true;
      }
    }
    if (repeatID){
      repeatID = false;
    }
    else {
      indexesOfSameIDsNot.push_back(i);
      repeatID = false;
    }
  }
  return indexesOfSameIDsNot;
}

void Relation::SetTuples(set<Tuple> &localSet)
{
  mySetOfTuples = localSet;
  return;
}

void Relation::AddToSet(Tuple & tempT)
{
  mySetOfTuples.insert(tempT);
  return;
}

Schema Relation::GetSchema()
{
  return mySchema;
}

set<Tuple> Relation::GetSetOfTuples()
{
  return mySetOfTuples;
}

int Relation::GetSize()
{
  return mySetOfTuples.size();
}

void Relation::Print()
{
  cout << endl;
  cout << "Relation Name: " << name << endl;
  cout << "Schema: ";
  for (unsigned int i = 0; i < mySchema.size(); ++i){
    cout << mySchema.at(i) << " ";
  }
  cout << endl;
  cout << "Set of Tuples: " << endl;
  for (set<Tuple>::iterator it=mySetOfTuples.begin(); it!=mySetOfTuples.end(); ++it) {
    Tuple innerTuple = *it;
    for (unsigned int i = 0; i < innerTuple.size(); i++){
      cout << setw(10);
      cout << left << innerTuple.at(i) << " ";
    }
    cout<< endl;
  }
  cout << endl;
}
