#include<iostream>
#include "IO.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>

using namespace std;

float** IO::getFileData(string fileName, float &externalSize, float &maxVolume){

  string fileString = readFromFile(fileName);
  vector<string> splitStringVec = splitString(fileString);
  float** resultArray = createParametersArray(splitStringVec, externalSize, maxVolume);
  return resultArray;
}

string IO::readFromFile(string fileName){

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

vector<string> IO::splitString(string dataString){

  istringstream dataStream(dataString);
  vector<string> stringFloatData((istream_iterator<string>(dataStream)), istream_iterator<string>());
  return stringFloatData;
}

float** IO::createParametersArray(vector<string> floatsString, float &externalSize, float &maxVolume){
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

void IO::getInputData(string &fileName, int &popSize, float &time){}
