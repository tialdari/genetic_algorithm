#include <iostream>
#include <vector>
#include "CIndividual.h"

using namespace std;

#define DEBUG true

CIndividual CIndividual::mutate(){

  if(DEBUG) cout << "Default mutate method" << endl;
  CIndividual testIndividual;
  return testIndividual;
}

CIndividual CIndividual::cross(CIndividual otherParent){

  if(DEBUG) cout << "Default cross method" << endl;
  CIndividual testIndividual;
  return testIndividual;

}

void CIndividual::setGenotype(vector<float> newGenotype){

    if(DEBUG) cout << "Setting new genotype" << endl;
    genotype = newGenotype;
}


CKnapsackIndividual::CKnapsackIndividual(){

  if(DEBUG) cout << "New CKnapsackIndividual object" << endl;
}

float CKnapsackIndividual::fitness(){

  if(DEBUG) cout << "Default fitness method" << endl;
  return 0.0f;
}
