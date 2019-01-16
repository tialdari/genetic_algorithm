#ifndef CGENETICALGORITHMCOMMANDS_H
#define CGENETICALGORITHMCOMMANDS_H

#define DEBUG true

using namespace std;

template <class T>
class IntroduceData: public Command{

  public:
    IntroduceData();
    IntroduceData(CGeneticAlgorithm<T> *cGeneticAlgorithm);
    ~IntroduceData();
    bool runCommand();

  private:
    CGeneticAlgorithm<T>* cGeneticAlgorithm;

};

template <class T>
class RunAlgorithm: public Command{

  public:
    RunAlgorithm();
    RunAlgorithm(CGeneticAlgorithm<T> *cGeneticAlgorithm);
    ~RunAlgorithm();
    bool runCommand();

  private:
    CGeneticAlgorithm<T>* cGeneticAlgorithm;

};

#endif
