#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H

#include <vector>
#include "CProblem.h"

using namespace std;

#define DEBUG false

template <class T>
class CIndividual{

  public:
    CIndividual();
    CIndividual(CProblem<T>* cProblem);
    CIndividual(CProblem<T>* cProblem, vector<T> genotype);
    ~CIndividual();
    vector<T> generateGenotype();
    void setGenotype(vector<T> newGenotype);
    vector<T> getGenotype();
    float getVolume();
    void countVolume();
    void printGenotype();
    void cross(float globalProb, float givenProb, CIndividual<T>* otherParent, vector<CIndividual<T>*> &population, bool even);
    vector<vector<T> > cutParent(CIndividual<T>* parent, int cutIndex);
    vector<T> mergeGenotypes(vector<T> fstChild, vector<T> sndChild);
    void mutate(float globalProb);
    void negate(T number);
    void fitness();
    float getFitness();
    int randInt(int range);
    float randFloat();
    //CIndividual* operator>(CIndividual* &pOther);

  private:

    vector<T> genotype;
    CProblem<T>* cProblem;
    float f_fitness;
    float volume;

};

class ComparatorByFitness {

  public:
    ComparatorByFitness(){};
    ~ComparatorByFitness(){};
    template<class T> bool operator()(CIndividual<T> *ind1, CIndividual<T> *ind2) {
      return ind1 -> getFitness() > ind2 -> getFitness();
  }
};

template <class T>
class CGeneticAlgorithm{

  public:
    CGeneticAlgorithm<T>();
    CGeneticAlgorithm<T>(CProblem<T>* cKnapsackProblem);
    ~CGeneticAlgorithm();
    void generateParameters();
    void generateInitPopulation(vector<CIndividual<T>*> &population);
    void generateNextPopulation(vector<CIndividual<T>*> oldPopulation, vector<CIndividual<T>*> &newPopulation);
    void run(double seconds, int saveBestNum);
    vector<CIndividual<T>*> takeBest(vector<CIndividual<T>*> population, int numOfBestInd);
    void exchangeIndividuals(vector<CIndividual<T>*> &bestIndividuals, vector<CIndividual<T>*> &modifiedPopulation, int numOfBestInd);
    void countPopulationFitness(vector<CIndividual<T>*> &population);
    CIndividual<T>* randIndividual(vector<CIndividual<T>*> population);
    void crossIndividuals(vector<CIndividual<T>*> oldPopulation, vector<CIndividual<T>*> &newPopulation, bool even);
    bool ifEven(int num);
    void mutatePopulation(vector<CIndividual<T>*> &population);
    CIndividual<T>* findValidSolution(vector<CIndividual<T>*> population);
    int getInt();
    void setPopSize();
    int randInt(int range);
    float randFloat();
    string toString();
    void revaluePopVectors(vector<CIndividual<T>*> &oldPopulation, vector<CIndividual<T>*> &newPopulation);
    void erasePop(vector<CIndividual<T>*> &population);
    void printPopulation(vector<CIndividual<T>*> population);
    CIndividual<T>* getBestSolution();


  private:
    int popSize;
    CProblem<T>* cProblem;
    float crossProb;
    float mutProb;
    CIndividual<T>* bestSolution;

};



#endif
