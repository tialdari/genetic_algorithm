#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

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

vector<CIndividual*> CGeneticAlgorithm::generatePopulation(){

  if(DEBUG) cout << "~ Generate population method\n" << endl;
  vector<CIndividual*> population;
  int fitness;

  for(int i = 0; i < popSize; i++){
    CIndividual* newCKnapsachIndividual = new CKnapsackIndividual(cKnapsackProblem);
    newCKnapsachIndividual -> generateGenotype();
    population.push_back(newCKnapsachIndividual);
    newCKnapsachIndividual -> printGenotype();
    fitness = newCKnapsachIndividual -> fitness();
    if(DEBUG) cout << " fitness: " << fitness << endl;

  }
  return population;
}

CIndividual* CGeneticAlgorithm::run(int times){

  bool succ = true;
  if(DEBUG) cout << "~ Run method\n" << endl;

  vector<CIndividual*> startPopulation = generatePopulation();
  int counter = 0;
  vector<CIndividual*> newPopulation;

  while(counter <= times){

    if(DEBUG) cout << "----------- ROUND " << counter << " ----------- " << endl;

    for(int i = 0; i < popSize; i++){
      startPopulation[i] -> fitness();
    }

    for(int i = 0; i < popSize/2; i++){
      vector<CIndividual*> children = crossIndividuals(startPopulation, succ);
        for(int j = 0; j < 2; j++){
          //  if(DEBUG) cout << "child added to the newPopulation\n" << endl;
            newPopulation.push_back(children[j]);
      }
    }

    cout << "newPopSize: " << newPopulation.size() << endl;

    for(int i = 0; i < newPopulation.size(); i++){
      newPopulation[i] -> mutate(mutProb);
      cout << "mutating new pop: " << endl;
    //  cout << "CHILD " << i << " GENOTYPE: ";
      newPopulation[i] -> printGenotype();
      cout << endl;
    }

    if(counter == times){
      sort(newPopulation.begin(), newPopulation.end(), ComparatorByFitness());
      return newPopulation.at(0);
    }

    cout << "before revaluing " << endl;

    for(int i = 0; i < newPopulation.size(); i++){
      cout << "CHILD " << i << " GENOTYPE: ";
      newPopulation[i] -> printGenotype();
    }
    revaluePopVectors(startPopulation, newPopulation);
    counter++;
  }

  sort(startPopulation.begin(), startPopulation.end(), ComparatorByFitness());
  return startPopulation.at(0);
}

CIndividual* CGeneticAlgorithm::randIndividual(vector<CIndividual*> population){

  int randIndx1 = randInt(popSize - 1);
  int randIndx2 = randInt(popSize - 1);

  CIndividual* individual1 = population[randIndx1];
  CIndividual* individual2 = population[randIndx2];

  if(individual1 -> getFitness() >= individual2 -> getFitness()) return individual1;
  else return individual2;
}

vector<CIndividual*> CGeneticAlgorithm::crossIndividuals(vector<CIndividual*> population, bool &pSucc){

  if(DEBUG) cout << "~ crossIndividuals method\n" << endl;

  CIndividual* parent1 = randIndividual(population);
  CIndividual* parent2 = randIndividual(population);

  float randCrossProb = randFloat();
  bool succ = true;
  vector<CIndividual*> children = parent1 -> cross(crossProb, randCrossProb, parent2, succ);
  pSucc = succ;
  return children;
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

void CGeneticAlgorithm::revaluePopVectors(vector<CIndividual*> &oldPopulation, vector<CIndividual*> &newPopulation){

  if(DEBUG) cout << "~ revaluePopVectors method\n" << endl;

  cout << "oldPopulation: " << endl;
    for(int i = 0; i < oldPopulation.size(); i++){
    oldPopulation[i] -> printGenotype();
  }

  erasePop(oldPopulation);

  cout << "newPopulation: " << endl;
    for(int i = 0; i < newPopulation.size(); i++){
    newPopulation[i] -> printGenotype();
  }

  cout << "oldPopulation after copying: " << endl;
  int popSize = newPopulation.size();
  for(int i = 0; i < popSize; i++){
    oldPopulation.push_back(newPopulation[i]);
    oldPopulation[i] -> printGenotype();
  }
/*
  cout << "oldPopulation after copying: " << endl;
    for(int i = 0; i < oldPopulation.size(); i++){
    oldPopulation[i] -> printGenotype();
  }
  */



  erasePop(newPopulation);
}

void CGeneticAlgorithm::erasePop(vector<CIndividual*> &population){

  if(DEBUG) cout << "~ Erase population method\n" << endl;
  if(DEBUG) cout << "~ test\n" << endl;

  int size = population.size();
  if(DEBUG) cout << "popSize: \n" << size << endl;

  for(int i = 0; i < size; i++){
     delete population[i];
     population.clear();
  }
}
