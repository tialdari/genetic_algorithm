
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CIndividual.h"
#include "CIndividual.cpp"
#include "CProblem.h"
#include "CProblem.cpp"
#include "CGeneticAlgorithm.h"
#include "CGeneticAlgorithm.cpp"

#define DEBUG true

using namespace std;

int main(){

  int paramSize = 2;
  float** pParameters = new float*[paramSize];

  pParameters[0] = new float[paramSize];
  pParameters[0][0] = 5.3;
  pParameters[0][1] = 4.0;

  pParameters[1] = new float[paramSize];
  pParameters[1][0] = 1.0;
  pParameters[1][1] = 3.0;

  pParameters[2] = new float[paramSize];
  pParameters[2][0] = 2.0;
  pParameters[2][1] = 2.0;

  CKnapsackProblem* cKnapsackProblem = new CKnapsackProblem(3, pParameters, 3, 4.0);
  cout << cKnapsackProblem -> toString();


  vector<float> testGenotype;
  testGenotype.push_back(2);
  testGenotype.push_back(2);
  testGenotype.push_back(2);
  testGenotype.push_back(2);
  testGenotype.push_back(2);
  CIndividual* testInd1 = new CKnapsackIndividual(cKnapsackProblem, testGenotype);

  vector<float> testGenotype2;
  testGenotype2.push_back(4);
  testGenotype2.push_back(4);
  testGenotype2.push_back(4);
  testGenotype2.push_back(4);
  testGenotype2.push_back(4);
  CIndividual* testInd2 = new CKnapsackIndividual(cKnapsackProblem, testGenotype2);

  vector<CIndividual*> resultChildren = testInd1 -> cross(0.66, 0.55, testInd2);

  int size = resultChildren.size();
  vector<float> child1 = resultChildren[0] -> getGenotype();
  int childSize1 = child1.size();

  vector<float> child2 = resultChildren[1] -> getGenotype();
  int childSize2 = child2.size();

  cout << "child one: ";
  for(int i = 0; i < childSize1; i++){
      cout << child1[i];
  }
  cout << endl;

  cout << "child two: ";
  for(int i = 0; i < childSize2; i++){
      cout << child2[i];
  }
  cout << endl;


  return 0;
}
