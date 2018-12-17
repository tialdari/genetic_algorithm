#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H

#include <vector>
#include "CProblem.h"

using namespace std;

#define DEBUG false


class CIndividual{

  public:
    CIndividual();
    CIndividual(CProblem* cProblem);
    CIndividual(CProblem* cProblem, vector<float> genotype);
    ~CIndividual();
    vector<float> generateGenotype();
    void setGenotype(vector<float> newGenotype);
    vector<float> getGenotype();
    float getVolume();
    void countVolume();
    void printGenotype();
    void cross(float globalProb, float givenProb, CIndividual* otherParent, vector<CIndividual*> &population, bool even);
    vector<vector<float> > cutParent(CIndividual* parent, int cutIndex);
    vector<float> mergeGenotypes(vector<float> fstChild, vector<float> sndChild);
    void mutate(float globalProb);
    void negate(float &number);
    void fitness();
    float getFitness();
    int randInt(int range);
    float randFloat();
    CIndividual* operator>(CIndividual* &pOther);

  private:

    vector<float> genotype;
    CProblem* cProblem;
    float f_fitness;
    float volume;

};

class ComparatorByFitness {

  public:
    ComparatorByFitness(){};
    ~ComparatorByFitness(){};
    bool operator()(CIndividual *ind1, CIndividual *ind2) {
      return ind1 -> getFitness() > ind2 -> getFitness();
  }
};

class CGeneticAlgorithm{

  public:
    CGeneticAlgorithm();
    CGeneticAlgorithm(CProblem* cKnapsackProblem);
    ~CGeneticAlgorithm();
    void generateParameters();
    void generateInitPopulation(vector<CIndividual*> &population);
    void generateNextPopulation(vector<CIndividual*> oldPopulation, vector<CIndividual*> &newPopulation);
    void run(double seconds);
    void countPopulationFitness(vector<CIndividual*> &population);
    CIndividual* randIndividual(vector<CIndividual*> population);
    void crossIndividuals(vector<CIndividual*> oldPopulation, vector<CIndividual*> &newPopulation, bool even);
    bool ifEven(int num);
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
    CIndividual* getBestSolution();


  private:
    int popSize;
    CProblem* cProblem;
    float crossProb;
    float mutProb;
    CIndividual* bestSolution;

};



#endif
