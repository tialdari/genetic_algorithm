#include <iostream>
#include <vector>
#include "CGeneticAlgorithm.h"

using namespace std;


CGeneticAlgorithm::CGeneticAlgorithm(){

  if(DEBUG) cout << "+ New CGeneticAlgorithm object\n" << endl;
}

CGeneticAlgorithm::~CGeneticAlgorithm(){

  if(DEBUG) cout << "- Deleting a CGeneticAlgorithm object\n" << endl;
}

void CGeneticAlgorithm::genereteParameters(){

  if(DEBUG) cout << "~ Default generate parameters method\n" << endl;
}

void CGeneticAlgorithm::generateProb(){

  if(DEBUG) cout << "~ Default generate probability method\n" << endl;
}

void CGeneticAlgorithm::generatePopulation(){

  if(DEBUG) cout << "~ Default generate population method\n" << endl;
}

CIndividual* CGeneticAlgorithm::run(){

  if(DEBUG) cout << "~ Default run method\n" << endl;
  CIndividual* testIndividual;
  return testIndividual;
}
