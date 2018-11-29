#include <vector>
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
#include <algorithm>
#include <string>

#define DEBUG true

using namespace std;

int main(){

  srand (time(NULL));

  int paramSize = 2;
  int solutionSize = 4;
  float** pParameters = new float*[solutionSize];

  pParameters[0] = new float[paramSize];
  pParameters[0][0] = 5.3;
  pParameters[0][1] = 3.0;

  pParameters[1] = new float[paramSize];
  pParameters[1][0] = 1.9;
  pParameters[1][1] = 3.0;

  pParameters[2] = new float[paramSize];
  pParameters[2][0] = 1.5;
  pParameters[2][1] = 2.0;

  pParameters[3] = new float[paramSize];
  pParameters[3][0] = 2.5;
  pParameters[3][1] = 3.0;

  CKnapsackProblem* cKnapsackProblem = new CKnapsackProblem(4, pParameters, 20.0);
  cout << cKnapsackProblem -> toString();
  bool succ = true;


  CIndividual* testIndividual = new CKnapsackIndividual(cKnapsackProblem);
  testIndividual -> generateGenotype();
  testIndividual -> printGenotype();

  CIndividual* testIndividual2 = new CKnapsackIndividual(cKnapsackProblem);
  testIndividual2 -> generateGenotype();
  testIndividual2 -> printGenotype();

  vector<vector<float> > parentParts = testIndividual -> cutParent(testIndividual, 2);
  //vector<CIndividual*> children = testIndividual2 -> cross(0.6, 0.5, testIndividual, succ);
  //children[0] -> printGenotype();
//  children[1] -> printGenotype();

/*
  CGeneticAlgorithm cGeneticAlgorithm(cKnapsackProblem);
  cGeneticAlgorithm.setPopSize();
  cGeneticAlgorithm.generateParameters();
  cGeneticAlgorithm.run(5);
*/


  return 0;
}
