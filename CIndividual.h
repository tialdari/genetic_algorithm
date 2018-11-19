#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

using namespace std;

#include <vector>
#include "CProblem.h"
#define DEBUG true

class CIndividual{

  public:
    virtual ~CIndividual(){};
    virtual float fitness() = 0;
    CIndividual* mutate();
    CIndividual* cross(CIndividual* otherParent);
    void setGenotype(vector<float> newGenotype);
    virtual vector<float> generateGenotype();

  protected:
    CIndividual(CProblem* cProblem, vector<float> genotype)
    :cProblem(cProblem),genotype(genotype){}
    vector<float> genotype;
    CProblem* cProblem;
};

class CKnapsackIndividual: public CIndividual{

  public:
      CKnapsackIndividual(CProblem* cProblem, vector<float> genotype)
      :CIndividual(cProblem, genotype)
      {this -> genotype = genotype;}
      ~CKnapsackIndividual();
      float fitness();
      vector<float> generateGenotype(int size);


};

#endif
