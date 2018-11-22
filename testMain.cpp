
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
  cout << endl;
  cKnapsackIndividual -> fitness();

  float f_rand = cKnapsackIndividual -> randFloat();
  cout << "rand float: " << f_rand << endl;

  vector<vector<float> >  firstChildrenParts = cKnapsackIndividual -> cutParent(cKnapsackIndividual, 0);
  cout << endl;

  vector<float> firstChildPart = firstChildrenParts[0];
  int fstChildSize = firstChildPart.size();
  vector<float> secondChildPart = firstChildrenParts[1];
  int sndChildSize = secondChildPart.size();

  cout << "first child: ";
  for(int i = 0; i < fstChildSize; i++){
    cout << firstChildPart[i];
  }

  cout << endl;

  cout << "second child: ";
  for(int i = 0; i < sndChildSize; i++){
    cout << secondChildPart[i];
  }

  cout << endl;
  vector<float> testChild1;
  vector<float> testChild2;

  testChild1.push_back(1);
  testChild1.push_back(2);
  testChild1.push_back(3);

  testChild2.push_back(4);
  testChild2.push_back(5);
  testChild2.push_back(6);

  vector<float> testMergedVector = cKnapsackIndividual -> mergeGenotypes(testChild1, testChild2);
  int testChildSize = testChild1.size() + testChild2.size();

  cout << "test Merger vector: ";
  for(int i = 0; i < testChildSize; i++){
    cout << testMergedVector[i];
  }

  


  return 0;
}
