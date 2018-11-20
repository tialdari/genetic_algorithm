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


CIndividual* CIndividual::cross(CIndividual* otherParent){

  if(DEBUG) cout << "~ Default cross method\n" << endl;
  CIndividual* testIndividual;
  return testIndividual;

}

CIndividual* CIndividual::mutate(){

  if(DEBUG) cout << "~ Default mutate method\n" << endl;
  CIndividual* testIndividual;
  return testIndividual;
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
    for(int j = 0; j < 3; j++){
      randNum = rand() % 2;
    }
    genotype.push_back(randNum);
  }

  return genotype;
};

float CKnapsackIndividual::fitness(){

  if(DEBUG) cout << "~ Default fitness method\n" << endl;
  return 0.0f;
}
