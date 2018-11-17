#include <iostream>
#include "CProblem.h"

using namespace std;

CProblem::~CProblem(){

  if(DEBUG) cout << "Deleting a CProblem object" << endl;
}

CKnapsackProblem::CKnapsackProblem(){
  if(DEBUG) cout << "New CKnapsackProblem object" << endl;
}

CKnapsackProblem::CKnapsackProblem(int itemsNum, float** itemsParameters, float maxVolume){
  if(DEBUG) cout << "New CKnapsackProblem object with parameters" << endl;
  this -> itemsNum = itemsNum;
  this -> itemsParameters = itemsParameters;
  this -> maxVolume = maxVolume;
}

CKnapsackProblem::~CKnapsackProblem(){
  if(DEBUG) cout << "Deleting a CKnapsackProblem object" << endl;
}

void CKnapsackProblem::setItemsNum(int num){
  if(DEBUG) cout << "Setting itersNum to: " << num << endl;
  this -> itemsNum = num;
}

void CKnapsackProblem::setItemsParameters(float** newParameters){
  if(DEBUG) cout << "Setting itemsParameters" << endl;
  this -> itemsParameters = newParameters;
}

void setMaxVolume(int new maxVolume){
  if(DEBUG) cout << "Setting maxVolume to: " << maxVolume << endl;
  this -> maxVolume = maxVolume;
}

void setNewProblemParameters(int num, float** newParameters, int maxVolume){
  if(DEBUG) cout << "Setting problem's parameters to: " << maxVolume << endl;
  setItemsNum(num);
  setItemsParameters(newParameters);
  setMaxVolume(maxVolume);
}

CIndividual* solution(){
  if(DEBUG) cout << "Default solution method" << endl;
  CIndividual testIndividual;
  return testIndividual;
}

float solutionValue(CIndividual* solution){

  if(DEBUG) cout << "Default solution value" << endl;
  return 0.0f;
}

bool isValid(CIndividual* solution){
  if(DEBUG) cout << "Default isValid value" << endl;
  return true;
}
