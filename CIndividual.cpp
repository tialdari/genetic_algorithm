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

vector<CIndividual*> CIndividual::cross(float globalProb, float givenProb, CIndividual* otherParent){

  if(DEBUG) cout << "~ Cross method\n" << endl;

  int ownSize = getGenotype().size();
  int otherSize = otherParent -> getGenotype().size();
  if(ownSize != otherSize)
    if(DEBUG) {cout << "ERROR: [cross] different genotypes size";
               cout << "ownSize: " << ownSize << " otherSize: " << otherSize << endl;
    }
  vector<CIndividual*> testChildren;
  return testChildren;
}

vector<vector<float> > CIndividual::cutParent(CIndividual* parent, int cutIndex){

  vector<vector<float> > firstChildrenParts;
  vector<float> parentGenotype = parent -> getGenotype();
  int parentGenSize = parentGenotype.size();

  if(cutIndex >= parentGenSize){
    if(DEBUG) cout << "ERROR: [cutParent] cutIndec out of range\n" << endl;
    return firstChildrenParts;
  }

  vector<float> children1;
  vector<float> children2;

  for(int i = 0; i < parentGenSize; i++){

    if(i <= cutIndex) children1.push_back(parentGenotype[i]);
    else children2.push_back(parentGenotype[i]);
  }

  firstChildrenParts.push_back(children1);
  firstChildrenParts.push_back(children2);

  return firstChildrenParts;
}


CIndividual* CIndividual::mutate(float globalProb, float givenProb){

  if(DEBUG) cout << "~ Default mutate method\n" << endl;
  CIndividual* testIndividual;
  return testIndividual;
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

CKnapsackIndividual::~CKnapsackIndividual(){

  if(DEBUG) cout << "- Deleting CKnapsackIndividual object\n" << endl;

};

vector<float> CKnapsackIndividual::generateGenotype(){

  if(DEBUG) cout << "~ generateGenotype method\n" << endl;
  vector<float> genotype;
  int size = cProblem -> getSolutionSize();
  float randNum;
  srand (time(NULL));

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
    if(DEBUG) cout << "~ fitness: " << f_fitness << endl;
    return f_fitness;
  }
  else return 0.0;
}
