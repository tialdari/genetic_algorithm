#include <iostream>
#include <vector>
#include "CGeneticAlgorithm.h"

using namespace std;

#define DEBUG true

CGeneticAlgorithm::CGeneticAlgorithm(){

  if(DEBUG) cout << "New CGeneticAlgorithm object" << endl;
}

CGeneticAlgorithm::~CGeneticAlgorithm(){

  if(DEBUG) cout << "Deleting a CGeneticAlgorithm object" << endl;
}

void CGeneticAlgorithm::genereteParameters(){

  if(DEBUG) cout << "Default generate parameters method" << endl;
}

void CGeneticAlgorithm::generateProb(){

  if(DEBUG) cout << "Default generate probability method" << endl;
}

void CGeneticAlgorithm::generatePopulation(){

  if(DEBUG) cout << "Default generate population method" << endl;
}

Individual* CGeneticAlgorithm::run(){

  if(DEBUG) cout << "Default run method" << endl;
  CIndividual testIndividual;
  return testIndividual;
}
