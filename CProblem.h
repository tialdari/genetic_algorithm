#ifndef CPROBLEM_H
#define CPROBLEM_H

#include <vector>
#include "CIndividual.h"

using namespace std;

#define DEBUG true
#define itemsCharacteritics 2

class CProblem{

  public:
    virtual ~CProblem();
    virtual CIndividual* solution() = 0;
    virtual float solutionValue(CIndividual* solution) = 0;
    virtual bool isValid(CIndividual* solution) = 0;

};


class CKnapsackProblem: public CProblem{

    public:
      CKnapsackProblem();
      CKnapsackProblem(int maxItemsNum, float** itemsParameters, int givenItemsNum, float maxVolume);
      ~CKnapsackProblem();
      void setMaxItemsNum(int num);
      void setItemsParameters(float** newParameters);
      void setMaxVolume(int maxVolume);
      void setNewProblemParameters(int num, float** newParameters, int maxVolume);
      CIndividual* solution();
      float solutionValue(CIndividual* solution);
      bool isValid(CIndividual* solution);
      string toString();
      string itemsParametersToString();


    private:
      int maxItemsNum;
      float** itemsParameters;
      int givenItemsNum;
      float maxVolume;

};


#endif
