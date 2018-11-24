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
    void generatePopulation();
    CIndividual* run();
    int getInt();
    void setPopSize();
    int randInt(int range);
    float randFloat();
    string toString();


  private:
    int popSize;
    //CIndividual* CKnapsackIndividual;
    CProblem* cKnapsackProblem;
    vector<CIndividual*> population;
    float crossProb;
    float mutProb;

};

#endif
