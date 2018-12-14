#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H

#include <vector>
#include "CIndividual.h"
#include "CProblem.h"

using namespace std;

#define DEBUG true



class CIndividual{

  public:
    virtual CIndividual(){};
    virtual vector<float> generateGenotype(){
      vector<float> testVec;
      return testVec;
    };
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
    virtual float fitness() = 0;
    float getFitness();
    int randInt(int range);
    float randFloat();
    CIndividual* operator>(CIndividual* &pOther);

  protected:

    CIndividual(CProblem* cProblem)
    :cProblem(cProblem){}
    CIndividual(CProblem* cProblem, vector<float> genotype)
    :cProblem(cProblem),genotype(genotype){}
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


class CKnapsackIndividual: public CIndividual{

  public:
      CKnapsackIndividual(CProblem* cProblem)
      :CIndividual(cProblem)
      {this -> cProblem = cProblem;
       vector<float> initalGenotype;
       genotype = initalGenotype;};
       CKnapsackIndividual(CProblem* cProblem, vector<float> genotype)
       :CIndividual(cProblem, genotype){
         this -> cProblem = cProblem;
         this -> genotype = genotype;
         f_fitness = 0.0;
       };
      ~CKnapsackIndividual();
      vector<float> generateGenotype();
      float fitness();


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
