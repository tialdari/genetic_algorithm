#ifndef CPROBLEM_H
#define CPROBLEM_H

#include <vector>

using namespace std;

#define DEBUG true
#define itemsCharacteritics 2

class CProblem{

  public:
    CProblem();
    virtual ~CProblem();
    virtual float solutionValue(vector<float> solution) = 0;
    virtual bool isValid(vector<float> solution) = 0;
    void setSolutionSize(int solutionSize){
      this -> solutionSize = solutionSize;
    };
    int getSolutionSize(){return solutionSize;};

  protected:
    CProblem(int solutionSize)
    :solutionSize(solutionSize){}
    int solutionSize;
};


class CKnapsackProblem: public CProblem{

    public:
      CKnapsackProblem();
      CKnapsackProblem(int solutionSize, float** itemsParameters, float maxVolume)
      :CProblem(solutionSize){
        if(DEBUG) cout << "+ New CKnapsackProblem object with parameters\n" << endl;
        this -> solutionSize = solutionSize;
        this -> itemsParameters = itemsParameters;
        this -> maxVolume = maxVolume;
      };
      ~CKnapsackProblem();
      //void setMaxItemsNum(int maxItemsNum);
      void setItemsParameters(float** newParameters);
      void setMaxVolume(float maxVolume);
      void setNewProblemParameters(int solutionSize, float** newParameters, int maxVolume);
      float solutionValue(vector<float> solution);
      bool isValid(vector<float> solution);
      string toString();
      string itemsParametersToString();

  private:
      float** itemsParameters;
      float maxVolume;

};


#endif
