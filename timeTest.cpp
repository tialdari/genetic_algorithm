#include <ctime>
#include <iostream>

using namespace std;

int main(){

  clock_t begin = clock();

  cout << "I'm measuring time..." << endl;
  cout << "and measuring..." << endl;


  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  cout << to_string(elapsed_secs) << endl;

  return 0;
}
