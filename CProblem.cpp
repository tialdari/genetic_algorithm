#include <iostream>
#include <string>
#include <sstream>
#include "CProblem.h"

using namespace std;

CProblem::~CProblem(){

  if(DEBUG) cout << "- Deleting a CProblem object" << endl;
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

void CKnapsackProblem::setMaxItemsNum(int maxItemsNum){
  if(DEBUG) cout << "~ Setting itemsNum to: " << maxItemsNum << "\n" << endl;
  this -> maxItemsNum = maxItemsNum;
}

void CKnapsackProblem::setItemsParameters(float** newParameters){
  if(DEBUG) cout << "~ Setting itemsParameters" << "\n" << endl;
  this -> itemsParameters = newParameters;
}

void CKnapsackProblem::setGivenItemsNum(int givenItemsNum){
  if(DEBUG) cout << "~ Setting givenItemsNum to: "
                 << givenItemsNum << "\n" << endl;
  this -> givenItemsNum = givenItemsNum;
}

void CKnapsackProblem::setMaxVolume(float maxVolume){
  if(DEBUG) cout << "~ Setting maxVolume to: " << maxVolume << "\n" << endl;
  maxVolume = maxVolume;
}

void CKnapsackProblem::setNewProblemParameters(int maxItemsNum, float** newParameters, int givenItemsNum, int maxVolume){
  if(DEBUG) cout << "~ Setting problem's parameters to: " << "\n" << endl;
  setMaxItemsNum(maxItemsNum);
  setItemsParameters(newParameters);
  setGivenItemsNum(givenItemsNum);
  setMaxVolume(maxVolume);
}

float CKnapsackProblem::solutionValue(vector<float> solution){

  if(DEBUG) cout << "~ Solution value method " << endl;
  float value;

  for(int i = 0; i < maxItemsNum; i++){
    value += itemsParameters[i][0] * solution[i];
  }
  return value;
}

bool CKnapsackProblem::isValid(float f_solutionValue){
  if(DEBUG) cout << "Default isValid value" << endl;

  if(f_solutionValue > maxVolume) return false;
  else return true;
  
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
    if(i != givenItemsNum - 1) parametersString += ",";
  }
  parametersString += "}";

  return parametersString;
}
