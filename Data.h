#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

using namespace std;

#include <vector>


class Data{

  public:
    Data(int number){this -> number = number;};
    ~Data(){};
    int getNumber(){return number;};
    bool operator <(const Data& dataExample) const{
    return this -> number < dataExample.number;
}

  private:
    int number;
};

#endif
