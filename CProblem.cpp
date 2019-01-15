#include <iostream>
#include <string>
#include <sstream>
#include "CProblem.h"

using namespace std;

template<class T> CProblem<T>::CProblem(){
  if(DEBUG) cout << "+ New cProblem object" << endl;
}

template<class T> CProblem<T>::~CProblem(){

  if(DEBUG) cout << "- Deleting a CProblem object" << endl;
}

template<class T> CKnapsackProblem<T>::CKnapsackProblem(){
  if(DEBUG) cout << "New CKnapsackProblem object" << endl;
}

template<class T> CKnapsackProblem<T>::~CKnapsackProblem(){
  if(DEBUG) cout << "- Deleting a CKnapsackProblem object" << endl;
}

template<class T> void CKnapsackProblem<T>::setItemsParameters(float** newParameters){
  if(DEBUG) cout << "~ Setting itemsParameters" << endl;
  this -> itemsParameters = newParameters;
}

template<class T> void CKnapsackProblem<T>::setMaxVolume(float maxVolume){
  if(DEBUG) cout << "~ Setting maxVolume to: " << maxVolume << endl;
  this -> maxVolume = maxVolume;
}

template<class T> void CKnapsackProblem<T>::setNewProblemParameters(int solutionSize, float** newParameters, int maxVolume){
  if(DEBUG) cout << "~ Setting problem's parameters to: " << endl;
  if(solutionSize < 0) if(DEBUG) cout << "ERROR: [setNewProblemParameters] solutionSize < 0 " << endl;
  this -> setSolutionSize(this -> solutionSize);
  setItemsParameters(newParameters);
  setMaxVolume(maxVolume);
}

template<> float CKnapsackProblem<bool>::solutionValue(vector<bool> solution){

  //if(DEBUG) cout << "~ Solution value method " << endl;
  float value;

  for(int i = 0; i < this -> solutionSize; i++){
  //  cout << to_string(itemsParameters[i][0]) << " ";
    value += itemsParameters[i][0] * solution[i];
  }
  return value;
}

template<> bool CKnapsackProblem<bool>::isValid(vector<bool> solution){
  //if(DEBUG) cout << "~ isValid method" << endl;
  float solutionVolume;

  for(int i = 0; i < this -> solutionSize; i++){
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

template<class T> string CKnapsackProblem<T>::toString(){

  string result;
  stringstream itemsNumber;
  itemsNumber << this -> solutionSize;
  result = itemsNumber.str();

  string result2;
  stringstream volume;
  volume << maxVolume;
  result2 = volume.str();


  return "~ CKnapsackProblem object\n -> solutionSize: " + result +
          "\n -> max volume: " + result2 +
          "\n -> itemsParameters: " +  itemsParametersToString() +"\n\n";
}

template<class T> string CKnapsackProblem<T>::itemsParametersToString(){

  string parametersString = "{";
  for(int i = 0; i < this -> solutionSize; i++){
    parametersString += "(";
    for(int j = 0; j < itemsCharacteritics; j++){
       parametersString += to_string(itemsParameters[i][j]);
       if(j != 1) parametersString += ",";
    }
    parametersString += ")";
    if(i != this -> solutionSize - 1) parametersString += ",";
  }
  parametersString += "}";

  return parametersString;
}
