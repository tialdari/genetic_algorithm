#ifndef MENUOBJECT_H
#define MENUOBJECT_H


using namespace std;

#include "Command.h"

#define DEBUG true

class MenuObject{

  public:
    virtual ~MenuObject(){};
    virtual void run() = 0;
    string getName(){return name;};
    void setName(string newName){
      this -> name = newName;
    };
    string getCommandsName(){return command;};
    void setCommand(string newCommand){
      this -> command = newCommand;
    };

    virtual void help() = 0;
    virtual string printSubmenu(MenuObject* menuObj){
      if(menuObj -> getSubMenu() == NULL) return menuObj -> getName();
      else return menuObj -> printSubmenu(menuObj -> getSubMenu())
                  + " -> " + menuObj -> getName();};
    virtual MenuObject* getSubMenu() = 0;
    virtual void search(string commmandName) = 0;
    virtual vector<MenuObject*> getMenuObjects(){return vector<MenuObject*>();};
    virtual Command* getCommand(){return NULL;};
    virtual string menuObjectToString(){return "virtual class implementation";};
    string nameToString(string name){return "\'" + name + "\'";};


  protected:
    MenuObject(string name, string command, MenuObject* subMenu)
    : name(name), command(command), subMenu(subMenu) {}
    string name;
    string command;
    MenuObject* subMenu;

  private:

};

#endif
