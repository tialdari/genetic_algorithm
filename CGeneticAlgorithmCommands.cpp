#include <iostream>
#include "CGeneticAlgorithm.h"
#include "CGeneticAlgorithm.cpp"
#include "CGeneticAlgorithmCommands.h"
#include "IO.h"
#include "Command.h"
#include "Command.cpp"
#include "CProblem.h"
#include "CProblem.cpp"

using namespace std;


  template<class T> IntroduceData<T>::IntroduceData(){
    if(DEBUG) cout << "new IntroduceData command" << endl;
  }

  template<class T> IntroduceData<T>::~IntroduceData(){
    if(DEBUG) cout << "deleting IntroduceData command" << endl;
  }

  template<class T> IntroduceData<T>::IntroduceData(CGeneticAlgorithm<T> *cGeneticAlgorithm){
    if(DEBUG) cout << "new IntroduceData command with a cGeneticAlgorithm" << endl;
    this -> cGeneticAlgorithm = cGeneticAlgorithm;
  }

  template<class T> bool IntroduceData<T>::runCommand(){

    if(DEBUG) cout << "running IntroduceData command" << endl;

    IO io;
    float solutionSize = 0;
    float maxVolume = 0;
    int saveBestNum = 10;

    float** pParameters = io.getFileData("test3.txt", solutionSize, maxVolume);

    if(saveBestNum > solutionSize){
        cout << "saveBestNum is bigger than the solutionSize!" << endl;
        return false;
    }else if(saveBestNum < 0){
      cout << "saveBestNum is less than the 0!" << endl;
      return false;
    }else if(maxVolume < 0.0){
      cout << "maxVolume is less than 0!" << endl;
      return false;
    }else if(solutionSize < 0.0){
      cout << "solutionSize is less than 0.0!" << endl;
      return false;
    }

    CKnapsackProblem<T>* cKnapsackProblem = new CKnapsackProblem<T>(solutionSize, pParameters, maxVolume);
    cGeneticAlgorithm -> setProblem(cKnapsackProblem);
    
    cout << "new data has been set" << endl;
    return true;
  }

  template<class T2> RunAlgorithm<T2>::RunAlgorithm(){
    if(DEBUG) cout << "new RunAlgorithm command" << endl;
  }

  template<class T2> RunAlgorithm<T2>::RunAlgorithm(CGeneticAlgorithm<T2> *cGeneticAlgorithm){
    if(DEBUG) cout << "deleting RunAlgorithm command" << endl;
  }

  template<class T2> RunAlgorithm<T2>::~RunAlgorithm(){
    if(DEBUG) cout << "new RunAlgorithm command with a cGeneticAlgorithm" << endl;
    this -> cGeneticAlgorithm = cGeneticAlgorithm;
  }

  template<class T2> bool RunAlgorithm<T2>::runCommand(){

    cGeneticAlgorithm -> getProblem() -> toString();

    /*
    cGeneticAlgorithm -> run(5.0, 50);
    cout << "best solution: ";
    cGeneticAlgorithm -> getBestSolution() -> printGenotype();
    cout << "Solution fitness:" << cGeneticAlgorithm -> getBestSolution() -> getFitness() << endl;
    */
    return true;
  }
