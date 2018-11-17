#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

using namespace std;

#define DEBUG false

class CIndividual{

  public:
    //virtual ~CIndividual();
    //virtual float fitness() = 0;
    //CIndividual mutate() = 0;
    //CIndividual cross(CIndividual otherParent) = 0;
    //void setGenotype(vector<float> newGenotype) = 0;

  protected:
    //CProblem problem;
    //vector<float> genotype;

};

class CKnapsackIndividual: public CIndividual{

  public:
      //CKnapsackIndividual();
      //~CKnapsackIndividual();
      //CKnapsackIndividual(CProblem(CKnapsackProblem?) problem, vector<float> genotype)
      //:CIndividual(problem, genotype);
      //float fitness();
}
