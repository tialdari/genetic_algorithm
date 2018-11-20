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
    CIndividual* cross(CIndividual* otherParent);
    CIndividual* mutate();
    virtual float fitness() = 0;


  protected:
    CIndividual(CProblem* cProblem)
    :cProblem(cProblem){}
    vector<float> genotype;
    CProblem* cProblem;
};

class CKnapsackIndividual: public CIndividual{

  public:
      CKnapsackIndividual(CProblem* cProblem)
      :CIndividual(cProblem)
      {this -> cProblem = cProblem;};
      ~CKnapsackIndividual();
      vector<float> generateGenotype();
      float fitness();


};

#endif
