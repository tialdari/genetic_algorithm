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
    virtual CIndividual* solution(int solutionSize) = 0;
    virtual float solutionValue(CIndividual* solution) = 0;
    virtual bool isValid(CIndividual* solution) = 0;

};


class CKnapsackProblem: public CProblem{

    public:
      CKnapsackProblem();
      CKnapsackProblem(int maxItemsNum, float** itemsParameters, int givenItemsNum, float maxVolume);
      ~CKnapsackProblem();
      void setMaxItemsNum(int maxItemsNum);
      void setItemsParameters(float** newParameters);
      void setGivenItemsNum(int givenItemsNum);
      void setMaxVolume(float maxVolume);
      void setNewProblemParameters(int maxItemsNum, float** newParameters, int givenItemsNum, int maxVolume);
      CIndividual* solution(int solutionSize);
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
