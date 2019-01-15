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


template<class T> CIndividual<T>::CIndividual(CKnapsackProblem<T>* cProblem, float globalMutProb, float globalCrossProb){
  this -> cProblem = cProblem;
  this -> globalMutProb = globalMutProb;
  this -> globalCrossProb = globalCrossProb;
}

template<class T> CIndividual<T>::CIndividual(CKnapsackProblem<T>* cProblem, vector<T> genotype, float globalMutProb, float globalCrossProb){
  this -> cProblem = cProblem;
  this -> genotype = genotype;
  this -> globalMutProb = globalMutProb;
  this -> globalCrossProb = globalCrossProb;
}

template<class T> CIndividual<T>::~CIndividual(){
  //if(DEBUG) cout << "-Deleting CIndividual" << endl;
}

template<> vector<bool> CIndividual<bool>::generateGenotype(){

  //if(DEBUG) cout << "~ Generate genotype method" << endl;

  int size = cProblem -> getSolutionSize();
  float randNum;
  bool isTaken;

  for(int i = 0; i < size; i++){
    randNum = randInt(1);
    isTaken = randNum;
    genotype.push_back(isTaken);
  }
  this -> genotype = genotype;

  return genotype;
};

template<> vector<int> CIndividual<int>::generateGenotype(){

  //if(DEBUG) cout << "~ Generate genotype method" << endl;

  int size = cProblem -> getSolutionSize();
  float randNum;
  bool isTaken;
  const int maxNumOfOneTypeItems = 10;

  for(int i = 0; i < size; i++){
    randNum = randInt(maxNumOfOneTypeItems);
    genotype.push_back(randNum);
  }
  this -> genotype = genotype;

  return genotype;
};

template<> vector<double> CIndividual<double>::generateGenotype(){

  //if(DEBUG) cout << "~ Generate genotype method" << endl;

  int size = cProblem -> getSolutionSize();
  float randNum;
  bool isTaken;
  const int maxNumOfOneTypeItems = 10.0;

  for(int i = 0; i < size; i++){
    randNum = randFloat() + randInt(maxNumOfOneTypeItems);
    genotype.push_back(randNum);
  }
  this -> genotype = genotype;

  return genotype;
};

template<class T> void CIndividual<T>::setGenotype(vector<T> newGenotype){

  if(DEBUG) cout << "~ Setting new genotype" << endl;
  genotype = newGenotype;
}

template<class T> vector<T> CIndividual<T>::getGenotype(){
  return genotype;
}

template<class T> void CIndividual<T>::printGenotype(){
  for(int i = 0; i < genotype.size(); i++){
    cout << genotype[i] << " ";
  }
  cout << " ";
}

template<class T> vector< vector<T> > CIndividual<T>::cutParent(CIndividual<T>* parent, int cutIndex){

  if(DEBUG) cout << "~ Cut parent method" << endl;

  vector<vector<T> > genotypeParts;
  vector<T> parentGenotype = parent -> getGenotype();
  int parentGenSize = parentGenotype.size();

  if(cutIndex >= parentGenSize){
    if(DEBUG) cout << "ERROR: [cutParent] cutIndec out of range" << endl;
  }

  vector<T> genotypePart1;
  vector<T> genotypePart2;

  for(int i = 0; i < parentGenSize; i++){

    if(i <= cutIndex) genotypePart1.push_back(parentGenotype[i]);
    else genotypePart2.push_back(parentGenotype[i]);
  }

  genotypeParts.push_back(genotypePart1);
  genotypeParts.push_back(genotypePart2);

  return genotypeParts;
}

template<class T> vector<T> CIndividual<T>::mergeGenotypes(vector<T> fstGenotype, vector<T> sndGenotype){

  if(DEBUG) cout << "~ Merge children method" << endl;

  int sndGenotypeSize = sndGenotype.size();

  for(int i = 0; i < sndGenotypeSize; i++){
    fstGenotype.push_back(sndGenotype[i]);
  }

  return fstGenotype;
}



template<class T> void CIndividual<T>::cross(float globalProb, float givenProb, CIndividual<T>* otherParent, vector<CIndividual<T>*> &population, bool even){

  if(DEBUG) cout << "~ Cross method" << endl;

  int ownSize = genotype.size();
  int otherSize = otherParent -> getGenotype().size();
  vector<T> betterGenotype;

  if(ownSize != otherSize)
    if(DEBUG) {cout << "ERROR: [cross] different genotypes size";
               cout << "ownSize: " << ownSize << " otherSize: " << otherSize << endl;
  }

  if(givenProb > globalProb){
    if(DEBUG) cout << " ERROR: [cross] Too big probability" << endl;
    if(even){
      population.push_back(new CIndividual<T>(cProblem, genotype, globalProb, otherParent -> globalCrossProb));
      population.push_back(new CIndividual<T>(cProblem, otherParent -> getGenotype(), globalProb, otherParent -> globalCrossProb));
    }else{
      if(f_fitness > otherParent -> getFitness()) betterGenotype = genotype;
      else betterGenotype = otherParent -> getGenotype();
      population.push_back(new CIndividual<T>(cProblem, betterGenotype, globalProb, otherParent -> globalCrossProb));
    }

  }else{

      int cutIndex = randInt(genotype.size() - 1);
    //  if(DEBUG) cout << " cutIndex: " << cutIndex << endl;

      vector<vector<T> > firstGenotypeParts = cutParent(this, cutIndex);
      vector<vector<T> > secondGenotypeParts = cutParent(otherParent, cutIndex);

      vector<T> fstGenotype = mergeGenotypes(firstGenotypeParts[0],secondGenotypeParts[1]);
      vector<T> sndGenotype = mergeGenotypes(secondGenotypeParts[0],firstGenotypeParts[1]);

      CIndividual<T>* fstChild = new CIndividual(cProblem, fstGenotype, globalProb, otherParent -> globalCrossProb);
      CIndividual<T>* sndChild = new CIndividual(cProblem, sndGenotype, globalProb, otherParent -> globalCrossProb);

    if(even){
      population.push_back(fstChild);
      population.push_back(sndChild);

    }else{
      if(fstChild -> getFitness() > sndChild -> getFitness()) betterGenotype = fstChild -> getGenotype();
      else betterGenotype = sndChild -> getGenotype();
      population.push_back(new CIndividual<T>(cProblem, betterGenotype, globalProb, otherParent -> globalCrossProb));
    }
  }
}

template<> void CIndividual<bool>::negate(bool &number){

  if(number == true) number = false;
  else if(number == false) number = true;
  else{
    if(DEBUG) cout << " ERROR: [negation] number not allowed " << endl;
  }
}

template<> void CIndividual<double>::negate(double &number){

  if(number == 0.0) number = 1.0;
  else if(number >= 1.0) number = 0.0;
  else{
    if(DEBUG) cout << " ERROR: [negation] number not allowed " << endl;
  }
}

template<> void CIndividual<int>::negate(int &number){

  if(number == 0) number = 1;
  else if(number >= 1) number = 0;
  else{
    if(DEBUG) cout << " ERROR: [negation] number not allowed " << endl;
  }
}

template<class T> vector<T> CIndividual<T>::operator +(CIndividual<T>* otherParent){

  float randCrossProb = randFloat();

  int ownSize = genotype.size();
  int otherSize = otherParent -> getGenotype().size();

  if(ownSize != otherSize)
    if(DEBUG) {cout << "ERROR: [cross] different genotypes size";
               cout << "ownSize: " << ownSize << " otherSize: " << otherSize << endl;

//    CIndividual<T>* thisCopy = new CIndividual(cProblem, genotype, globalMutProb, globalCrossProb);
    return genotype;
  }

  if(randCrossProb > globalCrossProb){

    //CIndividual<T>* thisCopy = new CIndividual(cProblem, genotype, globalMutProb, globalCrossProb);
    return genotype;

  }else{

      int cutIndex = randInt(genotype.size() - 1);

      vector<vector<T> > firstGenotypeParts = cutParent(this, cutIndex);
      vector<vector<T> > secondGenotypeParts = cutParent(otherParent, cutIndex);

      vector<T> fstGenotype = mergeGenotypes(firstGenotypeParts[0], secondGenotypeParts[1]);
    //  vector<T> sndGenotype = mergeGenotypes(secondGenotypeParts[0], firstGenotypeParts[1]);

    //CIndividual<T>* fstChild = new CIndividual(cProblem, fstGenotype, globalMutProb, globalCrossProb);
    //  CIndividual<T>* sndChild = new CIndividual(cProblem, sndGenotype, globalMutProb, globalCrossProb);

      return fstGenotype;
  }

}

template<class T> void CIndividual<T>::operator++(){

    mutate();
}

template<class T> void CIndividual<T>::mutate(){

  //if(DEBUG) cout << "~ Mutate method" << endl;


  float randProb = randFloat();
  int genotypeSize = genotype.size();

  for(int i = 0; i < genotypeSize; i++){
    //if(DEBUG) cout << "gene no " << i;
    if(randProb <= globalMutProb){
      negate(genotype[i]);
      //cout << " + " << endl;
    } //cout << " - " << endl;
    randProb = randFloat();
  }
}



template<class T> int CIndividual<T>::randInt(int range){

  float randNum;
  for(int i = 0; i < 3; i++){
      randNum = rand() % (range + 1);
  }
  return randNum;
}

template<class T> float CIndividual<T>::randFloat(){

  float randNum;{}
  for(int i = 0; i < 4; i++){
    randNum = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  }
  return randNum;
}

/*
template<class T> CIndividual<T>* CIndividual<T>::operator>(CIndividual<T>* &pOther){
  if(pOther -> f_fitness > this -> f_fitness) return pOther;
  else return this;
}
*/

template<class T> float CIndividual<T>::getFitness(){
  return f_fitness;
}

template<class T> void CIndividual<T>::fitness(){

  //if(DEBUG) cout << "\n~ fitness method" << endl;

  if(cProblem -> isValid(genotype)){
    f_fitness = cProblem -> solutionValue(genotype);
  }
}


template<class T> CGeneticAlgorithm<T>::CGeneticAlgorithm(){

  if(DEBUG) cout << "+ New CGeneticAlgorithm object" << endl;
  popSize = 0;
  crossProb = 0.0;
  mutProb = 0.0;
}

template<class T> CGeneticAlgorithm<T>::CGeneticAlgorithm(CKnapsackProblem<T>* cProblem){

  if(DEBUG) cout << "+ New CGeneticAlgorithm object with cProblem" << endl;
  this -> cProblem = cProblem;
}

template<class T> CGeneticAlgorithm<T>::~CGeneticAlgorithm(){

  if(DEBUG) cout << "- Deleting a CGeneticAlgorithm object" << endl;
  delete bestSolution;

}

template<class T> void CGeneticAlgorithm<T>::generateParameters(){

  if(DEBUG) cout << "~ Generate parameters method" << endl;

   crossProb = randFloat();
   mutProb = randFloat();
}

template<class T> void CGeneticAlgorithm<T>::generateInitPopulation(vector<CIndividual<T>*> &population){

  if(DEBUG) cout << "~ Generate population method" << endl;

  float fitness;

  for(int i = 0; i < popSize; i++){
      CIndividual<T>* newCIndividual = new CIndividual<T>(cProblem, mutProb, crossProb);
      newCIndividual -> generateGenotype();
      population.push_back(newCIndividual);
      //newCKnapsachIndividual -> printGenotype();
      newCIndividual -> fitness();
      fitness = newCIndividual -> getFitness();
      //if(DEBUG) cout << " fitness: " << to_string(fitness) << endl;
  }

}

template<class T> void CGeneticAlgorithm<T>::generateNextPopulation(vector<CIndividual<T>*> oldPopulation, vector<CIndividual<T>*> &newPopulation){

  crossIndividuals(oldPopulation, newPopulation);
}

template<class T> void CGeneticAlgorithm<T>::addToPopulation(CIndividual<T>* newCIndividual, vector<CIndividual<T>*> &destPopulation){

    destPopulation.push_back(newCIndividual);
}

template<class T> void CGeneticAlgorithm<T>::run(double seconds, int saveBestNum){

  cout << " computing...please, wait" << endl;

  CIndividual<T>* bestIndividual;

  vector<CIndividual<T>*> initialPopulation;
  generateInitPopulation(initialPopulation);

  if(DEBUG) cout << " SUCCES: generateInitPopulation(initialPopulation)";
  vector<CIndividual<T>*> nextPopulation;

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
    //vector<CIndividual<T>*> bestIndividuals = takeBest(initialPopulation, saveBestNum);
    if(DEBUG) cout << " SUCCES: takeBest";

    generateNextPopulation(initialPopulation, nextPopulation);
    if(DEBUG) cout << " SUCCES: generateNextPopulation";

    //junta los x mejores soluciones y la proxima generacion
    //exchangeIndividuals(bestIndividuals, nextPopulation, saveBestNum);
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

template<class T> vector<CIndividual<T>*> CGeneticAlgorithm<T>::takeBest(vector<CIndividual<T>*> population, int numOfBestInd){

    vector<CIndividual<T>*> bestIndividuals;

    for(int i = 0; i < numOfBestInd; i++){
      bestIndividuals.push_back(new CIndividual<T>(cProblem, population[i] -> getGenotype(), mutProb, crossProb));
    }
    return bestIndividuals;
}

template<class T> void CGeneticAlgorithm<T>::exchangeIndividuals(vector<CIndividual<T>*> &bestIndividuals, vector<CIndividual<T>*> &modifiedPopulation, int numOfBestInd){

      for(int i = 0; i < numOfBestInd; i++){
          delete modifiedPopulation[i];
          modifiedPopulation[i] = bestIndividuals[i];
      }
}

template<class T> void CGeneticAlgorithm<T>::countPopulationFitness(vector<CIndividual<T>*> &population){

  for(int i = 0; i < popSize; i++){
    population[i] -> fitness();
    //cout << population[i] -> getFitness() << " ";
  }
}

template<class T> CIndividual<T>* CGeneticAlgorithm<T>::randIndividual(vector<CIndividual<T>*> population){

  int randIndx1 = randInt(popSize - 1);
  int randIndx2 = randInt(popSize - 1);

  CIndividual<T>* individual1 = population[randIndx1];
  CIndividual<T>* individual2 = population[randIndx2];

  if(individual1 -> getFitness() >= individual2 -> getFitness()) return individual1;
  else return individual2;
}

template<class T> void CGeneticAlgorithm<T>::crossIndividuals(vector<CIndividual<T>*> oldPopulation, vector<CIndividual<T>*> &newPopulation){

  if(DEBUG) cout << "~ crossIndividuals method\n" << endl;

  CIndividual<T>* parent1 = randIndividual(oldPopulation);
  CIndividual<T>* parent2 = randIndividual(oldPopulation);
  vector<T> childGenotype = parent1 -> operator+(parent2);

  for(int i = 0; i < popSize; i++){
    addToPopulation(new CIndividual<T>(cProblem, childGenotype, mutProb, crossProb), newPopulation);
    parent1 = randIndividual(oldPopulation);
    parent2 = randIndividual(oldPopulation);
    childGenotype = parent1 -> operator+(parent2);
  }
}

template<class T> bool CGeneticAlgorithm<T>::ifEven(int num){
  if(num % 2 == 0) return true;
  else return false;
}

template<class T> void CGeneticAlgorithm<T>::mutatePopulation(vector<CIndividual<T>*> &population){

  for(int i = 0; i < popSize; i++){
    population[i] -> operator++();
  }
}

template<class T> CIndividual<T>* CGeneticAlgorithm<T>::findValidSolution(vector<CIndividual<T>*> population){

  if(DEBUG) cout << "~ find valid solution method\n" << endl;

  for(int i = 0; i < popSize; i++){
    if(cProblem -> isValid(population[i] -> getGenotype())){
      CIndividual<T>* bestSolution = new CIndividual<T>(cProblem, population[i] -> getGenotype(), mutProb, crossProb);
      bestSolution -> fitness();
      return bestSolution;
    }
  }
  if(DEBUG) cout << "no valid solution!!!" << endl;
  return new CIndividual<T>(cProblem, mutProb, crossProb);
}

template<class T> int CGeneticAlgorithm<T>::getInt(){

  int someInt;

  while(!(cin >> someInt)){
      cout << "please, give a whole number: ";
      cin >> someInt;

      cin.clear();
      cin.ignore(10000, '\n');
  }

  return someInt;
}

template<class T> void CGeneticAlgorithm<T>::setPopSize(){

  cout << "Give popSize: ";
  popSize = getInt();
}

template<class T> int CGeneticAlgorithm<T>::randInt(int range){

  float randNum;
  for(int i = 0; i < 3; i++){
      randNum = rand() % (range + 1);
  }
  return randNum;
}

template<class T> float CGeneticAlgorithm<T>::randFloat(){

  float randNum;{}
  for(int i = 0; i < 4; i++){
    randNum = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  }
  return randNum;
}

template<class T> string CGeneticAlgorithm<T>::toString(){

  return "popSize: " + to_string(popSize) + "\n" +
         "crossProb: " + to_string(crossProb) + "\n" +
         "mutProb: " + to_string(mutProb) + "\n";
}

template<class T> void CGeneticAlgorithm<T>::revaluePopVectors(vector<CIndividual<T>*> &oldPopulation, vector<CIndividual<T>*> &newPopulation){

  if(DEBUG) cout << "~ revaluePopVectors method\n" << endl;
  erasePop(oldPopulation);

  for(int i = 0; i < newPopulation.size(); i ++){
    oldPopulation.push_back(newPopulation[i]);
  }
  newPopulation.clear();
}

template<class T> void CGeneticAlgorithm<T>::erasePop(vector<CIndividual<T>*> &population){

  if(DEBUG) cout << "~ Erase population method\n" << endl;

  for(int i = 0; i < popSize; i++){
     delete population[i];
  }

  population.clear();
}

template<class T> void CGeneticAlgorithm<T>::printPopulation(vector<CIndividual<T>*> population){

    for(int i = 0; i < population.size(); i++){
      if(DEBUG) {population[i] -> printGenotype();
      cout << "(" << population[i] -> getFitness() << ")";
        cout << " ";
      }
    }
    if(DEBUG) cout << "\n";
}

template<class T> CIndividual<T>* CGeneticAlgorithm<T>::getBestSolution(){
  return bestSolution;
}
