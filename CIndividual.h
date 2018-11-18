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
    virtual vector<float> generateGenotype(int size);

  protected:
    CIndividual(vector<float> genotype):genotype(genotype){}
    vector<float> genotype;
};

class CKnapsackIndividual: public CIndividual{

  public:
      CKnapsackIndividual(vector<float> genotype):CIndividual(genotype){
        this -> genotype = genotype;}
      ~CKnapsackIndividual();
      float fitness();
      vector<float> generateGenotype(int size);

};

#endif
