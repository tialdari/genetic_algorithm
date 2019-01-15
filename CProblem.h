  #ifndef CPROBLEM_H
  #define CPROBLEM_H

  #include <vector>

  using namespace std;

  #define DEBUG false
  #define itemsCharacteritics 2

  template <class T>
  class CProblem{

  public:
    CProblem<T>();
    virtual ~CProblem();
    virtual float solutionValue(vector<T> solution) = 0;
    virtual bool isValid(vector<T> solution) = 0;
    void setSolutionSize(int solutionSize){
      this -> solutionSize = solutionSize;
    };
    int getSolutionSize(){return solutionSize;};
    CProblem<T>(int solutionSize):solutionSize(solutionSize){}

  protected:
    int solutionSize;
};

template <class T>
class CKnapsackProblem: public CProblem<T>{

    public:
      CKnapsackProblem<T>();
      inline CKnapsackProblem<T>(int solutionSize, float** itemsParameters, float maxVolume)
      :CProblem<T>(solutionSize){
        if(DEBUG) cout << "+ New CKnapsackProblem object with parameters" << endl;
        this -> solutionSize = solutionSize;
        this -> itemsParameters = itemsParameters;
        this -> maxVolume = maxVolume;
      };
      ~CKnapsackProblem();
      void setItemsParameters(float** newParameters);
      void setMaxVolume(float maxVolume);
      void setNewProblemParameters(int solutionSize, float** newParameters, int maxVolume);
      float solutionValue(vector<T> solution);
      bool isValid(vector<T> solution);
      string toString();
      string itemsParametersToString();

  private:
      float** itemsParameters;
      float maxVolume;
};



#endif
