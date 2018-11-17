#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

using namespace std;

#include <vector>
#define DEBUG true

class CIndividual{

  public:
    virtual ~CIndividual(){};
    virtual float fitness() = 0;
    CIndividual* mutate();
    CIndividual* cross(CIndividual* otherParent);
    void setGenotype(vector<float> newGenotype);

  protected:
    vector<float> genotype;

};

class CKnapsackIndividual: public CIndividual{

  public:
      CKnapsackIndividual();
      ~CKnapsackIndividual();
      CKnapsackIndividual(vector<float> genotype);
      float fitness();
};

#endif
