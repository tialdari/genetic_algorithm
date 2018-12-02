#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ctime>


#include "CGeneticAlgorithm.h"

using namespace std;


CGeneticAlgorithm::CGeneticAlgorithm(){

  if(DEBUG) cout << "+ New CGeneticAlgorithm object" << endl;
  popSize = 0;
  crossProb = 0.0;
  mutProb = 0.0;
}

CGeneticAlgorithm::CGeneticAlgorithm(CProblem* cProblem){

  if(DEBUG) cout << "+ New CGeneticAlgorithm object with cProblem" << endl;
  this -> cProblem = cProblem;
}

CGeneticAlgorithm::~CGeneticAlgorithm(){

  if(DEBUG) cout << "- Deleting a CGeneticAlgorithm object" << endl;
}

void CGeneticAlgorithm::generateParameters(){

  if(DEBUG) cout << "~ Generate parameters method" << endl;

   crossProb = randFloat();
   mutProb = randFloat();
}

void CGeneticAlgorithm::generateInitPopulation(vector<CIndividual*> &population){

  if(DEBUG) cout << "~ Generate population method" << endl;

  float fitness;

  for(int i = 0; i < popSize; i++){
      CIndividual* newCKnapsachIndividual = new CKnapsackIndividual(cProblem);
      newCKnapsachIndividual -> generateGenotype();
      population.push_back(newCKnapsachIndividual);
      //newCKnapsachIndividual -> printGenotype();
      fitness = newCKnapsachIndividual -> fitness();
      //if(DEBUG) cout << " fitness: " << to_string(fitness) << endl;
  }
}

void CGeneticAlgorithm::generateNextPopulation(vector<CIndividual*> oldPopulation, vector<CIndividual*> &newPopulation){

  bool evenSize = ifEven(popSize);

  for(int i = 0; i < popSize/2; i++){
    crossIndividuals(oldPopulation, newPopulation, true);
  }
  if(!evenSize) crossIndividuals(oldPopulation, newPopulation, false);
}

CIndividual* CGeneticAlgorithm::run(double seconds){

  CIndividual* bestIndividual;

  vector<CIndividual*> initialPopulation;
  generateInitPopulation(initialPopulation);

  vector<CIndividual*> nextPopulation;

  clock_t begin;
  clock_t end;
  double elapsed_secs;

  begin = clock();

  while(elapsed_secs <= seconds){

    if(DEBUG) cout << "\ninitialPopulation: ";
    printPopulation(initialPopulation);
    cout << endl;
    countPopulationFitness(initialPopulation);
    generateNextPopulation(initialPopulation, nextPopulation);
    mutatePopulation(nextPopulation);
    revaluePopVectors(initialPopulation, nextPopulation);
    countPopulationFitness(initialPopulation);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  }

    sort(initialPopulation.begin(), initialPopulation.end(), ComparatorByFitness());

    if(DEBUG) cout << "initialPopulation after sorting: ";
    printPopulation(initialPopulation);
    cout << endl;

    bestIndividual = findValidSolution(initialPopulation);
    cout << "best individual fitness: " << bestIndividual -> getFitness() << endl;
    erasePop(initialPopulation);
    //erasePop(nextPopulation);
    return bestIndividual;

}

void CGeneticAlgorithm::countPopulationFitness(vector<CIndividual*> &population){

  for(int i = 0; i < popSize; i++){
    population[i] -> fitness();
    //cout << population[i] -> getFitness() << " ";
  }
}

CIndividual* CGeneticAlgorithm::randIndividual(vector<CIndividual*> population){

  int randIndx1 = randInt(popSize - 1);
  int randIndx2 = randInt(popSize - 1);

  CIndividual* individual1 = population[randIndx1];
  CIndividual* individual2 = population[randIndx2];

  if(individual1 -> getFitness() >= individual2 -> getFitness()) return individual1;
  else return individual2;
}

void CGeneticAlgorithm::crossIndividuals(vector<CIndividual*> oldPopulation, vector<CIndividual*> &newPopulation, bool even){

  if(DEBUG) cout << "~ crossIndividuals method\n" << endl;

  CIndividual* parent1 = randIndividual(oldPopulation);
  CIndividual* parent2 = randIndividual(oldPopulation);

  float randCrossProb = randFloat();
  parent1 -> cross(crossProb, randCrossProb, parent2, newPopulation, even);
}

bool CGeneticAlgorithm::ifEven(int num){
  if(num % 2 == 0) return true;
  else return false;
}

void CGeneticAlgorithm::mutatePopulation(vector<CIndividual*> &population){

  for(int i = 0; i < popSize; i++){
    population[i] -> mutate(mutProb);
  }
}

CIndividual* CGeneticAlgorithm::findValidSolution(vector<CIndividual*> population){

  if(DEBUG) cout << "~ find valid solution method\n" << endl;

  for(int i = 0; i < popSize; i++){
    if(cProblem -> isValid(population[i] -> getGenotype())){
      CIndividual* bestSolution = new CKnapsackIndividual(cProblem, population[i] -> getGenotype());
      bestSolution -> fitness();
      return bestSolution;
    }
  }
  if(DEBUG) cout << "no valid solution!!!" << endl;
  return new CKnapsackIndividual(cProblem);
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

  erasePop(oldPopulation);
  CIndividual* newCKnapsachIndividual;

  for(int i = 0; i < newPopulation.size(); i ++){
    newCKnapsachIndividual = new CKnapsackIndividual(cProblem, newPopulation[i] -> getGenotype());
    oldPopulation.push_back(newCKnapsachIndividual);
  }
  erasePop(newPopulation);
}

void CGeneticAlgorithm::erasePop(vector<CIndividual*> &population){

  if(DEBUG) cout << "~ Erase population method\n" << endl;

  for(int i = 0; i < popSize; i++){
     delete population[i];
  }

  population.clear();
}

void CGeneticAlgorithm::printPopulation(vector<CIndividual*> population){

    for(int i = 0; i < population.size(); i++){
      population[i] -> printGenotype();
      cout << "(" << population[i] -> getFitness() << ")";
        cout << " ";
    }
    cout << "\n";
}
