#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CProblem.h"
#include "CProblem.cpp"
#include "CGeneticAlgorithm.h"
#include "CGeneticAlgorithm.cpp"
#include <algorithm>
#include <string>
#include "IO.h"
#include "IO.cpp"

#define DEBUG false

using namespace std;

int main(){

  //CProblem<bool>* pProblem = new CKnapsackProblem<bool>();

  IO io;
  srand (time(NULL));
  float solutionSize = 0;
  float maxVolume = 0;
  int saveBestNum = 10;

  float** pParameters = io.getFileData("test3.txt", solutionSize, maxVolume);

  if(saveBestNum > solutionSize){
      cout << "saveBestNum is bigger than the solutionSize!" << endl;
      return(0);
  }else if(saveBestNum < 0){
    cout << "saveBestNum is less than the 0!" << endl;
    return(0);
  }else if(maxVolume < 0.0){
    cout << "maxVolume is less than 0!" << endl;
    return(0);
  }else if(solutionSize < 0.0){
    cout << "solutionSize is less than 0.0!" << endl;
    return(0);
  }

  CKnapsackProblem<bool>* cKnapsackProblem = new CKnapsackProblem<bool>(solutionSize, pParameters, maxVolume);
  cout << cKnapsackProblem -> toString();

  CIndividual<bool>* cIndividual = new CIndividual<bool>(cKnapsackProblem);
  cIndividual -> generateGenotype();
  cIndividual -> printGenotype();


/*
  CGeneticAlgorithm<bool> cGeneticAlgorithm(cKnapsackProblem);
  cGeneticAlgorithm.generateParameters();
  cGeneticAlgorithm.setPopSize();

  cGeneticAlgorithm.run(5.0, 50);
  cout << "best solution: ";
  cGeneticAlgorithm.getBestSolution() -> printGenotype();
  cout << "Solution fitness:" << cGeneticAlgorithm.getBestSolution() -> getFitness() << endl;

  if(DEBUG) cout << "---------END----------" << endl;
*/

  //delete cKnapsackProblem;
  return 0;

}
