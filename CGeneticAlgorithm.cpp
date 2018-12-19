#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CGeneticAlgorithm.h"

using namespace std;


CIndividual::CIndividual(CProblem* cProblem){
  this -> cProblem = cProblem;
}

CIndividual::CIndividual(CProblem* cProblem, vector<float> genotype){
  this -> cProblem = cProblem;
  this -> genotype = genotype;
}

CIndividual::~CIndividual(){

  //if(DEBUG) cout << "-Deleting CIndividual" << endl;
}


vector<float> CIndividual::generateGenotype(){

  //if(DEBUG) cout << "~ Generate genotype method" << endl;

  int size = cProblem -> getSolutionSize();
  float randNum;

  for(int i = 0; i < size; i++){
    randNum = randInt(1);
    genotype.push_back(randNum);
  }
  this -> genotype = genotype;

  return genotype;
};

void CIndividual::setGenotype(vector<float> newGenotype){

  if(DEBUG) cout << "~ Setting new genotype" << endl;
  genotype = newGenotype;
}

vector<float> CIndividual::getGenotype(){
  return genotype;
}

void CIndividual::printGenotype(){
  for(int i = 0; i < genotype.size(); i++){
    cout << genotype[i];
  }
  cout << " ";
}

void CIndividual::cross(float globalProb, float givenProb, CIndividual* otherParent, vector<CIndividual*> &population, bool even){

  if(DEBUG) cout << "~ Cross method" << endl;

  int ownSize = genotype.size();
  int otherSize = otherParent -> getGenotype().size();
  vector<float> betterGenotype;

  if(ownSize != otherSize)
    if(DEBUG) {cout << "ERROR: [cross] different genotypes size";
               cout << "ownSize: " << ownSize << " otherSize: " << otherSize << endl;
  }

  if(givenProb > globalProb){
    if(DEBUG) cout << " ERROR: [cross] Too big probability" << endl;
    if(even){
      population.push_back(new CIndividual(cProblem, genotype));
      population.push_back(new CIndividual(cProblem, otherParent -> getGenotype()));
    }else{
      if(f_fitness > otherParent -> getFitness()) betterGenotype = genotype;
      else betterGenotype = otherParent -> getGenotype();
      population.push_back(new CIndividual(cProblem, betterGenotype));
    }

  }else{

      int cutIndex = randInt(genotype.size() - 1);
    //  if(DEBUG) cout << " cutIndex: " << cutIndex << endl;

      vector<vector<float> > firstGenotypeParts = cutParent(this, cutIndex);
      vector<vector<float> > secondGenotypeParts = cutParent(otherParent, cutIndex);

      vector<float> fstGenotype = mergeGenotypes(firstGenotypeParts[0],secondGenotypeParts[1]);
      vector<float> sndGenotype = mergeGenotypes(secondGenotypeParts[0],firstGenotypeParts[1]);

      CIndividual* fstChild = new CIndividual(cProblem, fstGenotype);
      CIndividual* sndChild = new CIndividual(cProblem, sndGenotype);

    if(even){
      population.push_back(fstChild);
      population.push_back(sndChild);

    }else{
      if(fstChild -> getFitness() > sndChild -> getFitness()) betterGenotype = fstChild -> getGenotype();
      else betterGenotype = sndChild -> getGenotype();
      population.push_back(new CIndividual(cProblem, betterGenotype));
    }
  }
}

vector<vector<float> > CIndividual::cutParent(CIndividual* parent, int cutIndex){

  if(DEBUG) cout << "~ Cut parent method" << endl;

  vector<vector<float> > genotypeParts;
  vector<float> parentGenotype = parent -> getGenotype();
  int parentGenSize = parentGenotype.size();

  if(cutIndex >= parentGenSize){
    if(DEBUG) cout << "ERROR: [cutParent] cutIndec out of range" << endl;
  }

  vector<float> genotypePart1;
  vector<float> genotypePart2;

  for(int i = 0; i < parentGenSize; i++){

    if(i <= cutIndex) genotypePart1.push_back(parentGenotype[i]);
    else genotypePart2.push_back(parentGenotype[i]);
  }

  genotypeParts.push_back(genotypePart1);
  genotypeParts.push_back(genotypePart2);

  return genotypeParts;
}

vector<float> CIndividual::mergeGenotypes(vector<float> fstGenotype, vector<float> sndGenotype){

  if(DEBUG) cout << "~ Merge children method" << endl;

  int sndGenotypeSize = sndGenotype.size();

  for(int i = 0; i < sndGenotypeSize; i++){
    fstGenotype.push_back(sndGenotype[i]);
  }

  return fstGenotype;
}

void CIndividual::mutate(float globalProb){

  //if(DEBUG) cout << "~ Mutate method" << endl;

  float randProb = randFloat();
  int genotypeSize = genotype.size();

  for(int i = 0; i < genotypeSize; i++){
    //if(DEBUG) cout << "gene no " << i;
    if(randProb <= globalProb){
      negate(genotype[i]);
      //cout << " + " << endl;
    }else{} //cout << " - " << endl;
    randProb = randFloat();
  }
}

void CIndividual::negate(float &number){

  if(number == 1.0) number = 0.0;
  else if(number == 0.0) number = 1.0;
  else{
    //if(DEBUG) cout << " ERROR: [negation] number not allowed " << endl;
  }
}

int CIndividual::randInt(int range){

  float randNum;
  for(int i = 0; i < 3; i++){
      randNum = rand() % (range + 1);
  }
  return randNum;
}

float CIndividual::randFloat(){

  float randNum;{}
  for(int i = 0; i < 4; i++){
    randNum = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  }
  return randNum;
}

CIndividual* CIndividual::operator>(CIndividual* &pOther){
  if(pOther -> f_fitness > this -> f_fitness) return pOther;
  else return this;
}

float CIndividual::getFitness(){
  return f_fitness;
}

void CIndividual::fitness(){

  //if(DEBUG) cout << "\n~ fitness method" << endl;

  if(cProblem -> isValid(genotype)){
    f_fitness = cProblem -> solutionValue(genotype);
  }
}


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
  delete bestSolution;
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
      CIndividual* newCIndividual = new CIndividual(cProblem);
      newCIndividual -> generateGenotype();
      population.push_back(newCIndividual);
      //newCKnapsachIndividual -> printGenotype();
      newCIndividual -> fitness();
      fitness = newCIndividual -> getFitness();
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

  void CGeneticAlgorithm::run(double seconds, int saveBestNum){

  CIndividual* bestIndividual;

  vector<CIndividual*> initialPopulation;
  generateInitPopulation(initialPopulation);

  if(DEBUG) cout << " SUCCES: generateInitPopulation(initialPopulation)";
  vector<CIndividual*> nextPopulation;

  clock_t begin;
  clock_t end;
  double elapsed_secs;

  begin = clock();

  while(elapsed_secs <= seconds){

    if(DEBUG){cout << "\ninitialPopulation: ";
      printPopulation(initialPopulation);
      cout << endl;
    }
    countPopulationFitness(initialPopulation);
    if(DEBUG) cout << " SUCCES: countPopulationFitness(initialPopulation)";
    sort(initialPopulation.begin(), initialPopulation.end(), ComparatorByFitness());
    if(DEBUG) cout << " SUCCES: sort";

    //take x best individuals from the initPop
    vector<CIndividual*> bestIndividuals = takeBest(initialPopulation, saveBestNum);
    if(DEBUG) cout << " SUCCES: takeBest";

    generateNextPopulation(initialPopulation, nextPopulation);
    if(DEBUG) cout << " SUCCES: generateNextPopulation";

    //junta los x mejores soluciones y la proxima generacion
    exchangeIndividuals(bestIndividuals, nextPopulation, saveBestNum);
    if(DEBUG) cout << " SUCCES: exchangeIndividuals";

    mutatePopulation(nextPopulation);
    if(DEBUG) cout << " SUCCES: mutatePopulation";

    revaluePopVectors(initialPopulation, nextPopulation);
    if(DEBUG) cout << " SUCCES: revaluePopVectors";

    countPopulationFitness(initialPopulation);
    if(DEBUG) cout << " SUCCES: countPopulationFitness";

    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  }

    sort(initialPopulation.begin(), initialPopulation.end(), ComparatorByFitness());

    if(DEBUG) cout << "initialPopulation after sorting: ";
    if(DEBUG) {printPopulation(initialPopulation);
      cout << endl;}

    bestIndividual = findValidSolution(initialPopulation);
    erasePop(initialPopulation);
    //erasePop(nextPopulation);
    bestSolution = bestIndividual;
}

vector<CIndividual*> CGeneticAlgorithm::takeBest(vector<CIndividual*> population, int numOfBestInd){

    vector<CIndividual*> bestIndividuals;

    for(int i = 0; i < numOfBestInd; i++){
      bestIndividuals.push_back(new CIndividual(cProblem, population[i] -> getGenotype()));
    }
    return bestIndividuals;
}

void CGeneticAlgorithm::exchangeIndividuals(vector<CIndividual*> &bestIndividuals, vector<CIndividual*> &modifiedPopulation, int numOfBestInd){

      for(int i = 0; i < numOfBestInd; i++){
          delete modifiedPopulation[i];
          modifiedPopulation[i] = bestIndividuals[i];
      }
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
      CIndividual* bestSolution = new CIndividual(cProblem, population[i] -> getGenotype());
      bestSolution -> fitness();
      return bestSolution;
    }
  }
  if(DEBUG) cout << "no valid solution!!!" << endl;
  return new CIndividual(cProblem);
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

  for(int i = 0; i < newPopulation.size(); i ++){
    oldPopulation.push_back(newPopulation[i]);
  }
  newPopulation.clear();
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
      if(DEBUG) {population[i] -> printGenotype();
      cout << "(" << population[i] -> getFitness() << ")";
        cout << " ";
      }
    }
    if(DEBUG) cout << "\n";
}

CIndividual* CGeneticAlgorithm::getBestSolution(){
  return bestSolution;
}
