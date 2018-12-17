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

static float** getFileData(string fileName, int &externalSize);
static string readFromFile(string fileName);
static vector<string> splitString(string dataString);
static float** createParametersArray(vector<string> floatsString, int &externalSize);
static void getInputData(string &fileName, int &popSize, float &time);


int main(){
/*
  srand (time(NULL));

  int paramSize = 2;
  int solutionSize = 15;
  float** pParameters = new float*[solutionSize];

  pParameters[0] = new float[paramSize];
  pParameters[0][0] = 0.125126;
  pParameters[0][1] =  56.358531;

  pParameters[1] = new float[paramSize];
  pParameters[1][0] = 19.330424;
  pParameters[1][1] = 80.874050;

  pParameters[2] = new float[paramSize];
  pParameters[2][0] = 58.500931;
  pParameters[2][1] = 47.987304;

  pParameters[3] = new float[paramSize];
  pParameters[3][0] = 35.029145;
  pParameters[3][1] = 89.596240;

  pParameters[4] = new float[paramSize];
  pParameters[4][0] = 82.284005;
  pParameters[4][1] = 74.660482;

  pParameters[5] = new float[paramSize];
  pParameters[5][0] = 17.410810 ;
  pParameters[5][1] = 85.894345;

  pParameters[6] = new float[paramSize];
  pParameters[6][0] = 71.050142;
  pParameters[6][1] = 51.353496;

  pParameters[7] = new float[paramSize];
  pParameters[7][0] = 30.399487;
  pParameters[7][1] = 1.498459;

  pParameters[8] = new float[paramSize];
  pParameters[8][0] = 9.140294;
  pParameters[8][1] = 36.445204;

  pParameters[9] = new float[paramSize];
  pParameters[9][0] = 14.731285;
  pParameters[9][1] = 16.589862;

  pParameters[10] = new float[paramSize];
  pParameters[10][0] = 98.852504 ;
  pParameters[10][1] = 44.569231;

  pParameters[11] = new float[paramSize];
  pParameters[11][0] = 11.908322;
  pParameters[11][1] = 0.466933;

  pParameters[12] = new float[paramSize];
  pParameters[12][0] = 0.891140;
  pParameters[12][1] = 37.788018;

  pParameters[13] = new float[paramSize];
  pParameters[13][0] = 53.166295;
  pParameters[13][1] = 57.118442;

  pParameters[14] = new float[paramSize];
  pParameters[14][0] = 60.176397;
  pParameters[14][1] = 60.716575;

  CKnapsackProblem* cKnapsackProblem = new CKnapsackProblem(solutionSize, pParameters, 375.0);
  cout << cKnapsackProblem -> toString();

  CGeneticAlgorithm cGeneticAlgorithm(cKnapsackProblem);
  cGeneticAlgorithm.generateParameters();
  cGeneticAlgorithm.setPopSize();

  cGeneticAlgorithm.run(15.0);
  cout << "best solution: ";
  cGeneticAlgorithm.getBestSolution() -> printGenotype();
  cout << "Solution fitness:" << cGeneticAlgorithm.getBestSolution() -> getFitness() << endl;

  if(DEBUG) cout << "---------END----------" << endl;

  delete cKnapsackProblem;
  return 0;
*/

  int size = 0;
  float** fileData = getFileData("test1.txt", size);


  for(int i = 0; i < size; i ++){
    for(int j = 0; j < 2; j++){
      cout << (2 * i + j) << ". " << fileData[i][j] << " ";
    }
  }


}

static float** getFileData(string fileName, int &externalSize){

  string fileString = readFromFile(fileName);
  vector<string> splitStringVec = splitString(fileString);
  float** resultArray = createParametersArray(splitStringVec, externalSize);
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

static float** createParametersArray(vector<string> floatsString, int &externalSize){

  int size = floatsString.size();
  externalSize = (size / 2) - 1;
  //cout << "size: " << externalSize << endl;

  float** floatArr = new float*[size/2 - 1];
  const int firstIndex = 1;
  const int parametersNum = 2;

  for(int i = 0; i < size/2 - firstIndex; i ++){
    floatArr[i] = new float[parametersNum];
    for(int j = 0; j < parametersNum; j++){
      floatArr[i][j] = strtof(floatsString[2*(i + firstIndex) + j].c_str(),0);
    }
  }
  return floatArr;
}


static void getInputData(string &fileName, int &popSize, float &time){
}


//check potential memory leaks
//enable the user to set all the parameters
//make the algorithm compatible with any problem
