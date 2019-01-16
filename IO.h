#ifndef IO_H
#define IO_H

#include <vector>

using namespace std;

class IO{

    public:
       float** getFileData(string fileName, float &externalSize, float &maxVolume);
       string readFromFile(string fileName);
       vector<string> splitString(string dataString);
       float** createParametersArray(vector<string> floatsString, float &externalSize, float &maxVolume);
       void getInputData(string &fileName, int &popSize, float &time);
       string getString();

};

#endif
