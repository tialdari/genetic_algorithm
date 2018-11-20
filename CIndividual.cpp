#include <iostream>
#include <vector>
#include "CIndividual.h"

using namespace std;


void CIndividual::setGenotype(vector<float> newGenotype){

    if(DEBUG) cout << "~ Setting new genotype\n" << endl;
    genotype = newGenotype;
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

  if(DEBUG) cout << "~ Default generateGenotype method\n" << endl;
  vector<float> genotype;

  return genotype;
};

float CKnapsackIndividual::fitness(){

  if(DEBUG) cout << "~ Default fitness method\n" << endl;
  return 0.0f;
}
