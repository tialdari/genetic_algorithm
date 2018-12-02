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
    void generateInitPopulation(vector<CIndividual*> &population);
    void generateNextPopulation(vector<CIndividual*> oldPopulation, vector<CIndividual*> &newPopulation);
    CIndividual* run(double seconds);
    void countPopulationFitness(vector<CIndividual*> &population);
    CIndividual* randIndividual(vector<CIndividual*> population);
    void crossIndividuals(vector<CIndividual*> oldPopulation, vector<CIndividual*> &newPopulation);
    void mutatePopulation(vector<CIndividual*> &population);
    CIndividual* findValidSolution(vector<CIndividual*> population);
    int getInt();
    void setPopSize();
    int randInt(int range);
    float randFloat();
    string toString();
    void revaluePopVectors(vector<CIndividual*> &oldPopulation, vector<CIndividual*> &newPopulation);
    void erasePop(vector<CIndividual*> &population);
    void printPopulation(vector<CIndividual*> population);


  private:
    int popSize;
    CProblem* cProblem;
    float crossProb;
    float mutProb;

};

#endif
