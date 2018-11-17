#ifndef CPROBLEM_H
#define CPROBLEM_H

#include <vector>
#include "CIndividual.h"

using namespace std;

#define DEBUG true

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
      CKnapsackProblem(int itemsNum, float** itemsParameters, float maxVolume);
      ~CKnapsackProblem();
      void setItemsNum(int num);
      void setItemsParameters(float** newParameters);
      void setMaxVolume(int maxVolume);
      void setNewProblemParameters(int num, float** newParameters, int maxVolume);
      CIndividual* solution();
      float solutionValue(CIndividual* solution);
      bool isValid(CIndividual* solution);


    private:
      int itemsNum;
      float** itemsParameters;
      float maxVolume;

};


#endif
