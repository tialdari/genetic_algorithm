#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

using namespace std;

#include <vector>
#include "CProblem.h"
#define DEBUG true

class CIndividual{

  public:
    virtual ~CIndividual(){};
    virtual vector<float> generateGenotype(){
      vector<float> testVec;
      return testVec;
    };
    void setGenotype(vector<float> newGenotype);
    vector<float> getGenotype();
    void printGenotype();
    vector<CIndividual*> cross(float globalProb, float givenProb, CIndividual* otherParent);
    vector<vector<float> > cutParent(CIndividual* parent, int cutIndex);
    vector<float> mergeGenotypes(vector<float> fstChild, vector<float> sndChild);
    void mutate(float globalProb);
    void negate(float &number);
    virtual float fitness() = 0;
    int randInt(int range);
    float randFloat();


  protected:
    CIndividual(CProblem* cProblem)
    :cProblem(cProblem){}
    CIndividual(CProblem* cProblem, vector<float> genotype)
    :cProblem(cProblem),genotype(genotype){}
    vector<float> genotype;
    CProblem* cProblem;
    float f_fitness;
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
       };
      ~CKnapsackIndividual();
      vector<float> generateGenotype();
      float fitness();


};

#endif
