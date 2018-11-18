#include <iostream>
#include <string>
#include <sstream>
#include "CProblem.h"

using namespace std;

CProblem::~CProblem(){

  if(DEBUG) cout << "Deleting a CProblem object" << endl;
}


CKnapsackProblem::CKnapsackProblem(){
  if(DEBUG) cout << "New CKnapsackProblem object" << endl;
}

CKnapsackProblem::CKnapsackProblem(int maxItemsNum, float** itemsParameters, int givenItemsNum, float maxVolume){
  if(DEBUG) cout << "+ New CKnapsackProblem object with parameters\n" << endl;
  this -> maxItemsNum = maxItemsNum;
  this -> itemsParameters = itemsParameters;
  this -> givenItemsNum = givenItemsNum;
  this -> maxVolume = maxVolume;
}

CKnapsackProblem::~CKnapsackProblem(){
  if(DEBUG) cout << "- Deleting a CKnapsackProblem object\n" << endl;
}

void CKnapsackProblem::setMaxItemsNum(int num){
  if(DEBUG) cout << "~ Setting itersNum to: " << num << "\n" << endl;
  this -> maxItemsNum = num;
}

void CKnapsackProblem::setItemsParameters(float** newParameters){
  if(DEBUG) cout << "Setting itemsParameters" << endl;
  this -> itemsParameters = newParameters;
}

void CKnapsackProblem::setMaxVolume(int maxVolume){
  if(DEBUG) cout << "Setting maxVolume to: " << maxVolume << endl;
  maxVolume = maxVolume;
}

void CKnapsackProblem::setNewProblemParameters(int num, float** newParameters, int maxVolume){
  if(DEBUG) cout << "~ Setting problem's parameters to: " << maxVolume << "\n" << endl;
  setMaxItemsNum(num);
  setItemsParameters(newParameters);
  setMaxVolume(maxVolume);
}

CIndividual* CKnapsackProblem::solution(){
  if(DEBUG) cout << "Default solution method" << endl;
  CIndividual* testIndividual;
  return testIndividual;
}

float CKnapsackProblem::solutionValue(CIndividual* solution){

  if(DEBUG) cout << "Default solution value" << endl;
  return 0.0f;
}

bool CKnapsackProblem::isValid(CIndividual* solution){
  if(DEBUG) cout << "Default isValid value" << endl;
  return true;
}

string CKnapsackProblem::toString(){

  string result;
  stringstream itemsNumber;
  itemsNumber << maxItemsNum;
  result = itemsNumber.str();

  string result2;
  stringstream volume;
  volume << maxVolume;
  result2 = volume.str();


  return "~ CKnapsackProblem object\n -> maxItemsNum: " + result +
          "\n -> givenItemsParameters: " + itemsParametersToString() +
          "\n -> max volume: " + result2 + "\n\n";
}

string CKnapsackProblem::itemsParametersToString(){

  string parametersString = "{";
  for(int i = 0; i < givenItemsNum; i++){
    parametersString += "(";
    for(int j = 0; j < itemsCharacteritics; j++){
       parametersString += to_string(itemsParameters[i][j]);
       if(j != 1) parametersString += ",";
    }
    parametersString += ")";
    if(i != maxItemsNum - 1) parametersString += ",";
  }
  parametersString += "}";

  return parametersString;
}
