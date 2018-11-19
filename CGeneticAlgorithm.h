#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H

#include <vector>
#include "CIndividual.h"

using namespace std;

#define DEBUG true

class CGeneticAlgorithm{

  public:
    CGeneticAlgorithm();
    ~CGeneticAlgorithm();
    void genereteParameters();
    void generateProb();
    void generatePopulation();
    CIndividual* run();

  private:
    int popSize;
    CIndividual* CKnapsackIndividual;
    vector<CIndividual*> population;
    float crossProb;
    float mutProb;

};

#endif
