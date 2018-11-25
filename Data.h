#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

class Data{

  public:
    Data(int number){this -> number = number;};
    ~Data(){};
    int getNumber(){return number;};

  private:
    int number;
};

class ComparatorByNum {

  public:
    ComparatorByNum(){};
    ~ComparatorByNum(){};
    bool operator()(Data *a, Data *b) {
      return a -> getNumber() < b -> getNumber();
  }
};



#endif
