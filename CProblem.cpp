#include <iostream>
#include <string>
#include <sstream>
#include "CProblem.h"

using namespace std;

CProblem::CProblem(){
  if(DEBUG) cout << "+ New cProblem object" << endl;
}

CProblem::~CProblem(){

  if(DEBUG) cout << "- Deleting a CProblem object" << endl;
}

CKnapsackProblem::CKnapsackProblem(){
  if(DEBUG) cout << "New CKnapsackProblem object" << endl;
}

CKnapsackProblem::~CKnapsackProblem(){
  if(DEBUG) cout << "- Deleting a CKnapsackProblem object" << endl;
}

void CKnapsackProblem::setItemsParameters(float** newParameters){
  if(DEBUG) cout << "~ Setting itemsParameters" << endl;
  this -> itemsParameters = newParameters;
}


void CKnapsackProblem::setMaxVolume(float maxVolume){
  if(DEBUG) cout << "~ Setting maxVolume to: " << maxVolume << endl;
  maxVolume = maxVolume;
}

void CKnapsackProblem::setNewProblemParameters(int solutionSize, float** newParameters, int maxVolume){
  if(DEBUG) cout << "~ Setting problem's parameters to: " << endl;
  if(solutionSize < 0) if(DEBUG) cout << "ERROR: [setNewProblemParameters] solutionSize < 0 " << endl;
  setSolutionSize(solutionSize);
  setItemsParameters(newParameters);
  setMaxVolume(maxVolume);
}

float CKnapsackProblem::solutionValue(vector<float> solution){

  //if(DEBUG) cout << "~ Solution value method " << endl;
  float value;

  for(int i = 0; i < solutionSize; i++){
  //  cout << to_string(itemsParameters[i][0]) << " ";
    value += itemsParameters[i][0] * solution[i];
  }
  return value;
}

bool CKnapsackProblem::isValid(vector<float> solution){
  //if(DEBUG) cout << "~ isValid method" << endl;

  float solutionVolume;

  for(int i = 0; i < solutionSize; i++){
    solutionVolume += itemsParameters[i][1] * solution[i];
  }

  //if(DEBUG) cout << " solution volume: " << solutionVolume << endl;
  //if(DEBUG) cout << " solution volume is ";

  if(solutionVolume > maxVolume){
    //if(DEBUG) cout << "not valid" << endl;
    return false;
  }else {
    //if(DEBUG) cout << "valid" << endl;
    return true;
  }
}

string CKnapsackProblem::toString(){

  string result;
  stringstream itemsNumber;
  itemsNumber << solutionSize;
  result = itemsNumber.str();

  string result2;
  stringstream volume;
  volume << maxVolume;
  result2 = volume.str();


  return "~ CKnapsackProblem object\n -> solutionSize: " + result +
          "\n -> max volume: " + result2 +
          "\n -> itemsParameters: " +  itemsParametersToString() +"\n\n";
}

string CKnapsackProblem::itemsParametersToString(){

  string parametersString = "{";
  for(int i = 0; i < solutionSize; i++){
    parametersString += "(";
    for(int j = 0; j < itemsCharacteritics; j++){
       parametersString += to_string(itemsParameters[i][j]);
       if(j != 1) parametersString += ",";
    }
    parametersString += ")";
    if(i != solutionSize - 1) parametersString += ",";
  }
  parametersString += "}";

  return parametersString;
}
