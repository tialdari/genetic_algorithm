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
    CGeneticAlgorithm(CProblem* cKnapsackProblem);
    ~CGeneticAlgorithm();
    void generateParameters();
    vector<CIndividual*> generatePopulation();
    CIndividual* run(int times);
    CIndividual* randIndividual();
    vector<CIndividual*> crossIndividuals();
    int getInt();
    void setPopSize();
    int randInt(int range);
    float randFloat();
    string toString();


  private:
    int popSize;
    CProblem* cKnapsackProblem;
    vector<CIndividual*> population;
    float crossProb;
    float mutProb;

};

#endif
