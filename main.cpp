#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CProblem.h"
#include "CProblem.cpp"
#include "CGeneticAlgorithm.h"
#include "CGeneticAlgorithm.cpp"
#include <algorithm>
#include <string>

#define DEBUG false

using namespace std;

static float** getFileData(string fileName, float &externalSize, float &maxVolume);
static string readFromFile(string fileName);
static vector<string> splitString(string dataString);
static float** createParametersArray(vector<string> floatsString, float &externalSize, float &maxVolume);
static void getInputData(string &fileName, int &popSize, float &time);

int main(){

  srand (time(NULL));
  float solutionSize = 0;
  float maxVolume = 0;
  int saveBestNum = 10;

  float** pParameters = getFileData("test3.txt", solutionSize, maxVolume);

  if(saveBestNum > solutionSize){
      cout << "saveBestNum is bigger than the solutionSize!" << endl;
      return(0);
  }else if(saveBestNum < 0){
    cout << "saveBestNum is less than the 0!" << endl;
    return(0);
  }else if(maxVolume < 0.0){
    cout << "maxVolume is less than 0!" << endl;
    return(0);
  }else if(solutionSize < 0.0){
    cout << "solutionSize is less than 0.0!" << endl;
    return(0);
  }

  CKnapsackProblem cKnapsackProblem(solutionSize, pParameters, maxVolume);
  cout << cKnapsackProblem.toString();

  CGeneticAlgorithm cGeneticAlgorithm(&cKnapsackProblem);
  cGeneticAlgorithm.generateParameters();
  cGeneticAlgorithm.setPopSize();

  cGeneticAlgorithm.run(5.0, 50);
  cout << "best solution: ";
  cGeneticAlgorithm.getBestSolution() -> printGenotype();
  cout << "Solution fitness:" << cGeneticAlgorithm.getBestSolution() -> getFitness() << endl;

  if(DEBUG) cout << "---------END----------" << endl;

  //delete cKnapsackProblem;
  return 0;

}

static float** getFileData(string fileName, float &externalSize, float &maxVolume){

  string fileString = readFromFile(fileName);
  vector<string> splitStringVec = splitString(fileString);
  float** resultArray = createParametersArray(splitStringVec, externalSize, maxVolume);
  return resultArray;
}

static string readFromFile(string fileName){

    fstream file;
    file.open(fileName, ios::in);

    if(file.good() == false){
      cout << "file doesn't exist!";
      exit(0);
    }

    string line;
    string resultString = "";

    while(getline(file, line)){
      resultString += " " + line;
    }
    file.close();

    return resultString;
  }

static vector<string> splitString(string dataString){

  istringstream dataStream(dataString);
  vector<string> stringFloatData((istream_iterator<string>(dataStream)), istream_iterator<string>());
  return stringFloatData;
}

static float** createParametersArray(vector<string> floatsString, float &externalSize, float &maxVolume){

  int size = floatsString.size();
  const int firstIndex = 1;
  const int parametersNum = 2;
  float** floatArr = new float*[size/2 - firstIndex];
  int currentIndex = 0;

  externalSize = strtof(floatsString[currentIndex++].c_str(),0);
  maxVolume = strtof(floatsString[currentIndex++].c_str(),0);

  for(int i = 0; i < size/2 - firstIndex; i ++){
    floatArr[i] = new float[parametersNum];
    for(int j = 0; j < parametersNum; j++){
      floatArr[i][j] = strtof(floatsString[currentIndex].c_str(),0);
      currentIndex++;
    }
  }
  return floatArr;
}

static void getInputData(string &fileName, int &popSize, float &time){
}
