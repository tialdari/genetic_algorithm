#include <iostream>
#include <vector>
#include <algorithm>
#include "Data.h"

using namespace std;

int main(){

  vector<Data> dataVector;
  dataVector.push_back(Data(4));
  dataVector.push_back(Data(2));
  dataVector.push_back(Data(7));
  dataVector.push_back(Data(-1));
  dataVector.push_back(Data(0));

  sort(dataVector.begin(), dataVector.end());

  int size = dataVector.size();
  cout << "size: " << size << endl;

  for(int i = 0; i < size; i++){

    cout << to_string(dataVector.at(i).getNumber()) << " ";
  }


  return 0;
}
