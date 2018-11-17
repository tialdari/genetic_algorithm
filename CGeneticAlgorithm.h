#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H

#include <vector>
#include "CIndividual.h"
#include "CProblem.h"

using namespace std;

#define DEBUG true

class CGeneticAlgorithm{

  public:
    CGeneticAlgorithm();
    ~CGeneticAlgorithm();
    void genereteParameters();
    void generateProb();
    void generatePopulation();
    Individual* run();

  private:
    CProblem* problem;
    int popSize;
    vector<CIndividual*> population;
    float crossProb;
    float mutProb;

};

#endif
