#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CIndividual.h"
#include "CIndividual.cpp"
#include "CProblem.h"
#include "CProblem.cpp"
#include "CGeneticAlgorithm.h"
#include "CGeneticAlgorithm.cpp"
#include <algorithm>



#define DEBUG true

using namespace std;

int main(){


  srand (time(NULL));

  int paramSize = 2;
  float** pParameters = new float*[paramSize];

  pParameters[0] = new float[paramSize];
  pParameters[0][0] = 5.3;
  pParameters[0][1] = 4.0;

  pParameters[1] = new float[paramSize];
  pParameters[1][0] = 1.0;
  pParameters[1][1] = 3.0;

  pParameters[2] = new float[paramSize];
  pParameters[2][0] = 1.5;
  pParameters[2][1] = 2.0;

  pParameters[3] = new float[paramSize];
  pParameters[3][0] = 2.5;
  pParameters[3][1] = 3.0;
/*

  pParameters[4] = new float[paramSize];
  pParameters[4][0] = 1.2;
  pParameters[4][1] = 2.9;

  pParameters[5] = new float[paramSize];
  pParameters[5][0] = 1.2;
  pParameters[5][1] = 1.4;

  pParameters[6] = new float[paramSize];
  pParameters[6][0] = 3.0;
  pParameters[6][1] = 1.0;

  pParameters[7] = new float[paramSize];
  pParameters[7][0] = 5.0;
  pParameters[7][1] = 6.0;

  pParameters[8] = new float[paramSize];
  pParameters[8][0] = 4.0;
  pParameters[8][1] = 2.0;

  pParameters[9] = new float[paramSize];
  pParameters[9][0] = 2.3;
  pParameters[9][1] = 2.2;
*/

  CKnapsackProblem* cKnapsackProblem = new CKnapsackProblem(4, pParameters, 20.0);
  cout << cKnapsackProblem -> toString();

/*
  vector<float> testGenotype;
  testGenotype.push_back(2);
  testGenotype.push_back(2);
  testGenotype.push_back(2);
  testGenotype.push_back(2);
  testGenotype.push_back(2);
  CIndividual* testInd1 = new CKnapsackIndividual(cKnapsackProblem, testGenotype);

  vector<float> testGenotype2;
  testGenotype2.push_back(4);
  testGenotype2.push_back(4);
  testGenotype2.push_back(4);
  testGenotype2.push_back(4);
  testGenotype2.push_back(4);
  CIndividual* testInd2 = new CKnapsackIndividual(cKnapsackProblem, testGenotype2);

  vector<CIndividual*> resultChildren = testInd1 -> cross(0.66, 0.55, testInd2);

  int size = resultChildren.size();
  vector<float> child1 = resultChildren[0] -> getGenotype();
  int childSize1 = child1.size();

  vector<float> child2 = resultChildren[1] -> getGenotype();
  int childSize2 = child2.size();

  cout << "child one: ";
  for(int i = 0; i < childSize1; i++){
      cout << child1[i];
  }
  cout << endl;

  cout << "child two: ";
  for(int i = 0; i < childSize2; i++){
      cout << child2[i];
  }
  cout << endl;

  vector<float> testGenotype4;
  testGenotype4.push_back(1);
  testGenotype4.push_back(0);
  testGenotype4.push_back(0);
  testGenotype4.push_back(0);
  testGenotype4.push_back(1);
  testGenotype4.push_back(0);

  testInd1 -> setGenotype(testGenotype4);
  testInd1 -> printGenotype();
  testInd1 -> mutate(0.70);
  testInd1 -> printGenotype();
*/
/*
  CGeneticAlgorithm cGeneticAlgorithm(cKnapsackProblem);
  cGeneticAlgorithm.setPopSize();
  cGeneticAlgorithm.generateParameters();
  cGeneticAlgorithm.generatePopulation();
*/
/*
  vector<int> myvector;

  // set some values (from 1 to 10)
   myvector.push_back(1);
   myvector.push_back(2);
   myvector.push_back(3);
   myvector.push_back(4);
   myvector.push_back(5);
   myvector.push_back(6);
   myvector.push_back(7);
   myvector.push_back(8);
   myvector.push_back(9);
   myvector.push_back(10);


  myvector.erase (myvector.begin(),myvector.begin()+3);

  cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    cout << ' ' << myvector[i];
  cout << '\n';
  */
  vector<float> testGenotype;
  testGenotype.push_back(1);
  testGenotype.push_back(1);
  testGenotype.push_back(1);
  testGenotype.push_back(1);

  vector<float> testGenotype2;
  testGenotype2.push_back(1);
  testGenotype2.push_back(0);
  testGenotype2.push_back(0);
  testGenotype2.push_back(0);

  vector<float> testGenotype3;
  testGenotype3.push_back(1);
  testGenotype3.push_back(1);
  testGenotype3.push_back(0);
  testGenotype3.push_back(0);


  vector<CIndividual*> testVector;
  testVector.push_back(new CKnapsackIndividual(cKnapsackProblem, testGenotype));
  testVector.push_back(new CKnapsackIndividual(cKnapsackProblem, testGenotype2));
  testVector.push_back(new CKnapsackIndividual(cKnapsackProblem, testGenotype3));


  for(int i = 0; i < testVector.size(); i++){
      cout << "fitness: " << testVector.at(i)-> fitness() << endl;
  }

  cout << "sorting... " << endl;
  sort(testVector.begin(), testVector.end(), ComparatorByFitness());

  for(int i = 0; i < testVector.size(); i++){
      cout << "fitness: " << testVector.at(i)-> fitness() << endl;
  }


  for(int i = 0; i < testVector.size(); i++){
    cout << i << ". ";
    testVector.at(i) -> printGenotype();
    cout << endl;
  }

  return 0;
}
