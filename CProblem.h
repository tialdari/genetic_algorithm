#ifndef CPROBLEM_H
#define CPROBLEM_H

#include <vector>

using namespace std;

#define DEBUG true
#define itemsCharacteritics 2

class CProblem{

  public:
    virtual ~CProblem();
    virtual float solutionValue(vector<float> solution) = 0;
    virtual bool isValid(vector<float> solution) = 0;

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
      float solutionValue(vector<float> solution);
      bool isValid(vector<float> solution);
      string toString();
      string itemsParametersToString();


    private:
      int maxItemsNum;
      float** itemsParameters;
      int givenItemsNum;
      float maxVolume;

};


#endif
