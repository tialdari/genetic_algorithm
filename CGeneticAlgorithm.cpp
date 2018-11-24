#include <iostream>
#include <vector>
#include<fstream>
#include<iostream>
#include "CGeneticAlgorithm.h"

using namespace std;


CGeneticAlgorithm::CGeneticAlgorithm(){

  if(DEBUG) cout << "+ New CGeneticAlgorithm object\n" << endl;
  popSize = 0;
  crossProb = 0.0;
  mutProb = 0.0;
}

CGeneticAlgorithm::CGeneticAlgorithm(CProblem* cKnapsackProblem){

  if(DEBUG) cout << "+ New CGeneticAlgorithm object with cKnapsackProblem\n" << endl;
  this -> cKnapsackProblem = cKnapsackProblem;
}


CGeneticAlgorithm::~CGeneticAlgorithm(){

  if(DEBUG) cout << "- Deleting a CGeneticAlgorithm object\n" << endl;
}

void CGeneticAlgorithm::generateParameters(){

  if(DEBUG) cout << "~ Generate parameters method\n" << endl;

   crossProb = randFloat();
   mutProb = randFloat();
}

void CGeneticAlgorithm::generatePopulation(){

  if(DEBUG) cout << "~ Generate population method\n" << endl;
  int fitness;

  for(int i = 0; i < popSize; i++){
    CIndividual* newCKnapsachIndividual = new CKnapsackIndividual(cKnapsackProblem);
    newCKnapsachIndividual -> generateGenotype();
    population.push_back(newCKnapsachIndividual);
    newCKnapsachIndividual -> printGenotype();
    fitness = newCKnapsachIndividual -> fitness();
    if(DEBUG) cout << " fitness: " << fitness << endl;

  }
}

CIndividual* CGeneticAlgorithm::run(int times){

  if(DEBUG) cout << "~ Default run method\n" << endl;
  CIndividual* testIndividual;

  /*
  CIndividual* pp_population;
  for(int i = 0; i < popSize; i++){
    pp_population = population[i];
  }

  

  */
  return testIndividual;
}

CIndividual* CGeneticAlgorithm::randIndividual(){

  int randIndx1 = randInt(popSize - 1);
  int randIndx2 = randInt(popSize - 1);

  CIndividual* individual1 = population[randIndx1];
  CIndividual* individual2 = population[randIndx2];

  if(individual1 -> getFitness() >= individual2 -> getFitness()) return individual1;
  else return individual2;
}

vector<CIndividual*> CGeneticAlgorithm::crossIndividuals(){

  CIndividual* parent1 = randIndividual();
  CIndividual* parent2 = randIndividual();

  float randCrossProb = randFloat();
  return parent1 -> cross(crossProb, randCrossProb, parent2);
}

int CGeneticAlgorithm::getInt(){

  int someInt;

  while(!(cin >> someInt)){
      cout << "please, give a whole number: ";
      cin >> someInt;

      cin.clear();
      cin.ignore(10000, '\n');
  }

  return someInt;
}

void CGeneticAlgorithm::setPopSize(){

  cout << "Give popSize: ";
  popSize = getInt();
}

int CGeneticAlgorithm::randInt(int range){

  float randNum;
  for(int i = 0; i < 3; i++){
      randNum = rand() % (range + 1);
  }
  return randNum;
}

float CGeneticAlgorithm::randFloat(){

  float randNum;{}
  for(int i = 0; i < 4; i++){
    randNum = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  }
  return randNum;
}

string CGeneticAlgorithm::toString(){

  return "popSize: " + to_string(popSize) + "\n" +
         "crossProb: " + to_string(crossProb) + "\n" +
         "mutProb: " + to_string(mutProb) + "\n";
}
