#include <iostream>
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
  pParameters[0][0] = 5.0;
  pParameters[0][1] = 4.0;

  pParameters[1] = new float[paramSize];
  pParameters[1][0] = 1.0;
  pParameters[1][1] = 3.0;

  pParameters[2] = new float[paramSize];
  pParameters[2][0] = 2.0;
  pParameters[2][1] = 2.0;

  CKnapsackProblem cKnapsackProblem(2, pParameters, 3, 4.0);
  cout << cKnapsackProblem.toString();

  return 0;
}

//test setters in CProblem
//implement CKnapsackIndividual
