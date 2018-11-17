#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

#include <vector>

using namespace std;

#define DEBUG true

class CIndividual{

  public:
    virtual ~CIndividual();
    virtual float fitness() = 0;
    CIndividual* mutate();
    CIndividual* cross(CIndividual* otherParent);
    void setGenotype(vector<float> newGenotype);

  protected:
  //  CProblem problem;
    vector<float> genotype;

};

class CKnapsackIndividual: public CIndividual{

  public:
      CKnapsackIndividual();
      ~CKnapsackIndividual();
      //CKnapsackIndividual(CProblem(CKnapsackProblem?) problem, vector<float> genotype)
      //CIndividual(problem, genotype);
      float fitness();
};

#endif
