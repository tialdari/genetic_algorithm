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

/*
  vector<float> testSolution;
  testSolution.push_back(1.0);
  testSolution.push_back(0.0);
  testSolution.push_back(1.0);
  float result = cKnapsackProblem -> solutionValue(testSolution);
  cout << cKnapsackProblem -> isValid(result) << endl;
*/

  CIndividual* cKnapsackIndividual = new CKnapsackIndividual(cKnapsackProblem);
  vector<float> testSolution = cKnapsackIndividual -> generateGenotype();

  for(int i = 0; i < cKnapsackProblem -> getSolutionSize(); i++){
    cout << testSolution[i] << " ";
  }
  return 0;
}

//test setters in CProblem
//implement CKnapsackIndividual
