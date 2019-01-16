#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CProblem.h"
//#include "CProblem.cpp"
#include "CGeneticAlgorithm.h"
//#include "CGeneticAlgorithm.cpp"
#include <algorithm>
#include <string>
#include "IO.h"
#include "IO.cpp"
#include "Menu.h"
#include "Menu.cpp"
#include "MenuObject.h"
#include "MenuObject.cpp"
#include "MenuCommand.h"
#include "MenuCommand.cpp"
#include "CGeneticAlgorithmCommands.h"
#include "CGeneticAlgorithmCommands.cpp"

#define DEBUG false

using namespace std;

int main(){


  srand (time(NULL));
  CGeneticAlgorithm<int>* cGeneticAlgorithm = new CGeneticAlgorithm<int>();

  Menu* menu = new Menu("main menu", "main_menu", NULL);
  MenuObject* introduceData = new MenuCommand("introduceData", "introduce_d", menu, new IntroduceData<int>(cGeneticAlgorithm));
  MenuObject* runAlgorithm = new MenuCommand("runAlgorithm", "run_alg", menu, new RunAlgorithm<int>(cGeneticAlgorithm));

  menu -> addNewCommand(introduceData);
  menu -> addNewCommand(runAlgorithm);

  menu -> run();
  delete menu;


/*
  IO io;
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

  CKnapsackProblem<int>* cKnapsackProblem = new CKnapsackProblem<int>(solutionSize, pParameters, maxVolume);

  CGeneticAlgorithm<int> cGeneticAlgorithm(cKnapsackProblem);
  cGeneticAlgorithm.generateParameters();

  cGeneticAlgorithm.setPopSize();

  cGeneticAlgorithm.run(5.0, 50);
  cout << "best solution: ";
  cGeneticAlgorithm.getBestSolution() -> printGenotype();
  cout << "Solution fitness:" << cGeneticAlgorithm.getBestSolution() -> getFitness() << endl;

  if(DEBUG) cout << "---------END----------" << endl;

  delete cKnapsackProblem;
  */
  return 0;

}
