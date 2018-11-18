#include <iostream>
#include <vector>
#include "CIndividual.h"

using namespace std;


CIndividual* CIndividual::mutate(){

  if(DEBUG) cout << "~ Default mutate method\n" << endl;
  CIndividual* testIndividual;
  return testIndividual;
}

CIndividual* CIndividual::cross(CIndividual* otherParent){

  if(DEBUG) cout << "~ Default cross method\n" << endl;
  CIndividual* testIndividual;
  return testIndividual;

}

void CIndividual::setGenotype(vector<float> newGenotype){

    if(DEBUG) cout << "~ Setting new genotype\n" << endl;
    genotype = newGenotype;
}

float CKnapsackIndividual::fitness(){

  if(DEBUG) cout << "~ Default fitness method\n" << endl;
  return 0.0f;
}
