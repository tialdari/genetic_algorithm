#ifndef COMMAND_H
#define COMMAND_H

using namespace std;

#define DEBUG false

class Command{

  public:
    Command();
    virtual bool runCommand();
    void description(){cout << descriptionVar << endl;};
    void setDescription(string newDescription){
      this -> descriptionVar = newDescription;
    };
    string getDescription(){return descriptionVar;};

  protected:
    string descriptionVar;

};

class TestCommand : public Command{

  public:
    TestCommand(){
      if(DEBUG) cout << "new testCommand command" << endl;
    }
    ~TestCommand(){
      if(DEBUG) cout << "deleting testCommand" << endl;
    }
    bool runCommand(){
      cout << "test command running" << endl;
      return true;
    }

};

#endif
