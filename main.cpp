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
  pParameters[0][1] = 1.5;

  pParameters[1] = new float[paramSize];
  pParameters[1][0] = 1.9;
  pParameters[1][1] = 2.0;

  pParameters[2] = new float[paramSize];
  pParameters[2][0] = 1.5;
  pParameters[2][1] = 2.0;

  pParameters[3] = new float[paramSize];
  pParameters[3][0] = 2.5;
  pParameters[3][1] = 3.0;

  CKnapsackProblem* cKnapsackProblem = new CKnapsackProblem(4, pParameters, 4.0);
  cout << cKnapsackProblem -> toString();

  CGeneticAlgorithm cGeneticAlgorithm(cKnapsackProblem);
  cGeneticAlgorithm.generateParameters();
  cGeneticAlgorithm.setPopSize();

  CIndividual* bestSolution = cGeneticAlgorithm.run(2);
  

  cout << "---------END----------" << endl;

  delete cKnapsackProblem;
  return 0;
}
