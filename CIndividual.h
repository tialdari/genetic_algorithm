
class CIndividual{

  public:
    CIndividual();
    CIndividual(CProblem* cProblem);
    CIndividual(CProblem* cProblem, vector<float> genotype);
    vector<float> generateGenotype(){};
    void setGenotype(vector<float> newGenotype);
    vector<float> getGenotype();
    float getVolume();
    void countVolume();
    void printGenotype();
    void cross(float globalProb, float givenProb, CIndividual* otherParent, vector<CIndividual*> &population, bool even);
    vector<vector<float>> cutParent(CIndividual* parent, int cutIndex);
    vector<float> mergeGenotypes(vector<float> fstChild, vector<float> sndChild);
    void mutate(float globalProb);
    void negate(float &number);
    virtual float fitness() = 0;
    float getFitness();
    int randInt(int range);
    float randFloat();
    CIndividual* operator>(CIndividual* &pOther);

  private:

    vector<float> genotype;
    CProblem* cProblem;
    float f_fitness;
    float volume;


};

class ComparatorByFitness {

  public:
    ComparatorByFitness(){};
    ~ComparatorByFitness(){};
    bool operator()(CIndividual *ind1, CIndividual *ind2) {
      return ind1 -> getFitness() > ind2 -> getFitness();
  }
};
