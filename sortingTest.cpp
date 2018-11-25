  #include <iostream>
  #include <vector>
  #include <algorithm>
#include "Data.h"

using namespace std;



int main(){

  vector<Data*> dataVector;
  dataVector.push_back(new Data(4));
  dataVector.push_back(new Data(2));
  dataVector.push_back(new Data(7));
  dataVector.push_back(new Data(-1));
  dataVector.push_back(new Data(0));

  sort(dataVector.begin(), dataVector.end(), ComparatorByNum());

  int size = dataVector.size();
  cout << "size: " << size << endl;

  for(int i = 0; i < size; i++){

    cout << to_string(dataVector.at(i) -> getNumber()) << " ";
  }


  return 0;
}
