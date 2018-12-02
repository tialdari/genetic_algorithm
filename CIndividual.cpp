#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CIndividual.h"

using namespace std;

void CIndividual::setGenotype(vector<float> newGenotype){

  if(DEBUG) cout << "~ Setting new genotype" << endl;
  genotype = newGenotype;
}

vector<float> CIndividual::getGenotype(){
  return genotype;
}

float CIndividual::getVolume(){
  return volume;
}

void CIndividual::countVolume(){

  for(int i = 0; i < genotype.size(); i++){

  }
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
      population.push_back(new CKnapsackIndividual(cProblem, genotype));
      population.push_back(new CKnapsackIndividual(cProblem, otherParent -> getGenotype()));
    }else{
      if(f_fitness > otherParent -> getFitness()) betterGenotype = genotype;
      else betterGenotype = otherParent -> getGenotype();
      population.push_back(new CKnapsackIndividual(cProblem, betterGenotype));
    }

  }else{

      int cutIndex = randInt(genotype.size() - 1);
    //  if(DEBUG) cout << " cutIndex: " << cutIndex << endl;

      vector<vector<float> > firstGenotypeParts = cutParent(this, cutIndex);
      vector<vector<float> > secondGenotypeParts = cutParent(otherParent, cutIndex);

      vector<float> fstGenotype = mergeGenotypes(firstGenotypeParts[0],secondGenotypeParts[1]);
      vector<float> sndGenotype = mergeGenotypes(secondGenotypeParts[0],firstGenotypeParts[1]);

      CIndividual* fstChild = new CKnapsackIndividual(cProblem, fstGenotype);
      CIndividual* sndChild = new CKnapsackIndividual(cProblem, sndGenotype);

    if(even){
      population.push_back(fstChild);
      population.push_back(sndChild);

    }else{
      if(fstChild -> getFitness() > sndChild -> getFitness()) betterGenotype = fstChild -> getGenotype();
      else betterGenotype = sndChild -> getGenotype();
      population.push_back(new CKnapsackIndividual(cProblem, betterGenotype));
    }
  }
}


/*
  cout << "children's genotype: " << endl;
  resultChildren[0] -> printGenotype();
  resultChildren[1] -> printGenotype();
  cout << endl;
*/


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

/*
  cout << "child genotype: ";
  for(int i = 0; i < fstGenotype.size(); i++){
    cout << to_string(fstGenotype[i]) << " ";
  }
  cout << endl;
  */

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
    if(DEBUG) cout << " ERROR: [negation] number not allowed " << endl;
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

CKnapsackIndividual::~CKnapsackIndividual(){

  //if(DEBUG) cout << "- Deleting CKnapsackIndividual object" << endl;
};

vector<float> CKnapsackIndividual::generateGenotype(){

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

float CKnapsackIndividual::fitness(){

  //if(DEBUG) cout << "\n~ fitness method" << endl;

  if(cProblem -> isValid(genotype)){
    f_fitness = cProblem -> solutionValue(genotype);
    return f_fitness;
  }
  else return 0.0;
}
