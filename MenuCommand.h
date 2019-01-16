#ifndef MENUCOMMAND_H
#define MENUCOMMAND_H

#include "Command.h"


using namespace std;

#define DEBUG true


class MenuCommand: public MenuObject{

  public:
    MenuCommand(string name, string command, MenuObject* subMenu, Command* pCommand)
    : MenuObject(name, command, subMenu)
    {
      this -> subMenu = subMenu;
      this -> pCommand = pCommand;
    };
    ~MenuCommand();

  //  Menu* getSubMenu(){return subMenu;};
    void run();
    void help(){pCommand -> description();};
    void search(string commandName){};
    MenuObject* getSubMenu(){return subMenu;};
    Command* getCommand(){return pCommand;};
    string commandToString();
    string menuObjectToString(){return commandToString();};


  private:
    Command* pCommand;
    MenuObject* subMenu;

};

#endif
