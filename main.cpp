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

/*
  CIndividual* testIndividual = new CKnapsackIndividual(cKnapsackProblem);
  testIndividual -> generateGenotype();
  testIndividual -> printGenotype();
  cout << endl;


  CIndividual* testIndividual2 = new CKnapsackIndividual(cKnapsackProblem);
  testIndividual2 -> generateGenotype();
  testIndividual2 -> printGenotype();
  cout << endl;
  */

  //float fitness = cKnapsackProblem -> solutionValue(testIndividual -> getGenotype());

//  cout << "\n" << to_string(fitness);


  CGeneticAlgorithm cGeneticAlgorithm(cKnapsackProblem);
  cGeneticAlgorithm.setPopSize();


  vector<CIndividual*> testPopulation;
  vector<CIndividual*> newPopulation;

  cGeneticAlgorithm.generatePopulation(testPopulation, 4);
  cGeneticAlgorithm.generatePopulation(newPopulation, 4);

  cout << "test population: " << endl;
  for(int i = 0; i < testPopulation.size(); i++){
      testPopulation[i] -> printGenotype();
  }
  cout << endl;

  cout << "new population: " << endl;
  for(int i = 0; i < newPopulation.size(); i++){
      newPopulation[i] -> printGenotype();
  }
  cout << endl;


  cGeneticAlgorithm.erasePop(testPopulation);

  cout << "test population: " << endl;
  for(int i = 0; i < testPopulation.size(); i++){
      testPopulation[i] -> printGenotype();
  }
  cout << endl;

  CIndividual* newCKnapsachIndividual;

  cout << "pushing to test population: " << endl;
  for(int i = 0; i < newPopulation.size(); i ++){
    newCKnapsachIndividual = new CKnapsackIndividual(cKnapsackProblem, newPopulation[i] -> getGenotype());
    testPopulation.push_back(newCKnapsachIndividual);
    newPopulation[i] -> printGenotype();
  }
  cout << endl;


  cout << "test population: " << endl;
  for(int i = 0; i < testPopulation.size(); i++){
      testPopulation[i] -> printGenotype();
  }
  cout << endl;

  cGeneticAlgorithm.erasePop(newPopulation);

  cout << "generating new population: " << endl;
  cGeneticAlgorithm.generatePopulation(newPopulation, 4);


  cout << "test population: " << endl;
  for(int i = 0; i < testPopulation.size(); i++){
      testPopulation[i] -> printGenotype();
  }
  cout << endl;


  cout << "new population: " << endl;
  for(int i = 0; i < newPopulation.size(); i++){
      newPopulation[i] -> printGenotype();
  }
  cout << endl;


/*
  vector<CIndividual*> testPopulation = cGeneticAlgorithm.generatePopulation();
  vector<CIndividual*> testPopulation2 = cGeneticAlgorithm.generatePopulation();

  cout << "testPopulation:  ";
  cGeneticAlgorithm.printPopulation(testPopulation);
  cout << endl;

  cout << "testPopulation2: ";
  cGeneticAlgorithm.printPopulation(testPopulation2);
  cout << endl;

  cGeneticAlgorithm.erasePop(testPopulation);


  for(int i = 0; i < testPopulation2.size(); i++){
    testPopulation.push_back(testPopulation2[i]);
  }

  cGeneticAlgorithm.erasePop(testPopulation2);


  vector<CIndividual*> newTestPopulation2 = cGeneticAlgorithm.generatePopulation();

  cout << "TESTTT:  ";

  for(int i = 0; i < newTestPopulation2.size(); i++){
    testPopulation2.push_back(newTestPopulation2[i]);
  }

  cout << "testPopulation:  ";
  cGeneticAlgorithm.printPopulation(testPopulation);
  cout << endl;

  return(0);


  cout << "testPopulation2: ";
  cGeneticAlgorithm.printPopulation(testPopulation2);
  cout << endl;




  cout << "---------END----------" << endl;

//deleting objects
//cGeneticAlgorithm is deleted automatically
  cGeneticAlgorithm.erasePop(testPopulation);
  cGeneticAlgorithm.erasePop(testPopulation2);

  delete cKnapsackProblem;
*/
  return 0;
}
