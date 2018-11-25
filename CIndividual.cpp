#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CIndividual.h"

using namespace std;


void CIndividual::setGenotype(vector<float> newGenotype){

  if(DEBUG) cout << "~ Setting new genotype\n" << endl;
  genotype = newGenotype;

}

vector<float> CIndividual::getGenotype(){
  return genotype;
}

void CIndividual::printGenotype(){

  if(DEBUG) cout << "~ individual's genotype:\n" << endl;
  for(int i = 0; i < genotype.size(); i++){
    cout << genotype[i];
  }
  cout << "\n\n";
}

vector<CIndividual*> CIndividual::cross(float globalProb, float givenProb, CIndividual* otherParent){

  if(DEBUG) cout << "~ Cross method\n" << endl;

  int ownSize = genotype.size();
  int otherSize = otherParent -> getGenotype().size();

  if(ownSize != otherSize)
    if(DEBUG) {cout << "ERROR: [cross] different genotypes size";
               cout << "ownSize: " << ownSize << " otherSize: " << otherSize << endl;
  }

  vector<CIndividual*> resultChildren;
  if(givenProb > globalProb){
    if(DEBUG) cout << " ERROR: [cross] Too big probability\n" << endl;
    return resultChildren;
  }

  int cutIndex = randInt(genotype.size() - 1);
  if(DEBUG) cout << " cutIndex: " << cutIndex << endl;

  vector<vector<float> > firstGenotypeParts = cutParent(this, cutIndex);
  vector<vector<float> > secondGenotypeParts = cutParent(otherParent, cutIndex);

  vector<float> fstGenotype = mergeGenotypes(firstGenotypeParts[0],secondGenotypeParts[1]);
  vector<float> sndGenotype = mergeGenotypes(firstGenotypeParts[1],secondGenotypeParts[0]);

  CIndividual* fstChild = new CKnapsackIndividual(cProblem, fstGenotype);
  CIndividual* sndChild = new CKnapsackIndividual(cProblem, sndGenotype);

  resultChildren.push_back(fstChild);
  resultChildren.push_back(sndChild);

  return resultChildren;
}

vector<vector<float> > CIndividual::cutParent(CIndividual* parent, int cutIndex){

  if(DEBUG) cout << "~ Cut parent method\n" << endl;

  vector<vector<float> > genotypeParts;
  vector<float> parentGenotype = parent -> getGenotype();
  int parentGenSize = parentGenotype.size();

  if(cutIndex >= parentGenSize){
    if(DEBUG) cout << "ERROR: [cutParent] cutIndec out of range\n" << endl;
    return genotypeParts;
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

  if(DEBUG) cout << "~ Merge children method\n" << endl;

  int sndGenotypeSize = sndGenotype.size();

  for(int i = 0; i < sndGenotypeSize; i++){
    fstGenotype.push_back(sndGenotype[i]);
  }
  return fstGenotype;
}

void CIndividual::mutate(float globalProb){

  if(DEBUG) cout << "~ Mutate method\n" << endl;

  float randProb = randFloat();
  int genotypeSize = genotype.size();

  for(int i = 0; i < genotypeSize; i++){
    if(randProb <= globalProb){
      negate(genotype[i]);
      randProb = randFloat();
    }
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

float CIndividual::getFitness(){
  return f_fitness;
}

CKnapsackIndividual::~CKnapsackIndividual(){

  if(DEBUG) cout << "- Deleting CKnapsackIndividual object\n" << endl;

};

vector<float> CKnapsackIndividual::generateGenotype(){

  if(DEBUG) cout << "~ Generate genotype method\n" << endl;

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

  if(DEBUG) cout << "~ fitness method\n" << endl;

  if(cProblem -> isValid(genotype)){
    f_fitness = cProblem -> solutionValue(genotype);
    return f_fitness;
  }
  else return 0.0;
}
