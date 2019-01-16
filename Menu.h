#ifndef MENU_H
#define MENU_H

using namespace std;

#define DEBUG true

#include "MenuObject.h"
#include "MenuCommand.h"

class Menu: public MenuObject{

  public:
    Menu(string name, string command, MenuObject* subMenu): MenuObject(name, command, subMenu)
    {
      size = vMenuObjects.size();
      this -> subMenu = subMenu;
      if(DEBUG) cout << "new menu, name: "  << name << ", "
                     << "command: " << command << ", "
                     << "size: " << size << endl;

    };
    ~Menu();

    int getSize(){return size;};

    MenuObject* getSubMenu();
    void setSubmenu(Menu* subMenu);
    vector<MenuObject*> getMenuObjects(){return vMenuObjects;};

    void setvMenuObjects(vector<MenuObject*> newMenuObjects);
    void setpMenuObjListVal(int index, MenuObject* menuObj);
    void addNewCommand(MenuObject* menuObj);
    void deleteCommand(int index);

    void run();
    void menuItemsList();
    string getCommandName();
    int getCommandIndex(string commandName);
    void executeCommand(int commandIndex);
    void help(){cout << "no help\n" << endl;};
    void search(string commandName);
    bool builtInCommands(string expression);

    string menuToString();
    string childrenToString();
    string menuObjectToString(){return menuToString();};


    int readWord(char* stringMenu, int size, int &startIndex, string& resultString, bool &pSucc);
    Menu* readMenu(char* stringMenu, int size, int &startIndex, MenuObject* subMenu, bool &pSucc);
    vector<MenuObject*> readChildren(char* stringMenu, int size, int &startIndex, char symbol, MenuObject* subMenu, bool &pSucc);
    MenuCommand* readCommand(char* stringMenu, int size, int &startIndex, MenuObject* subMenu, bool &pSucc);
    void error(char missingSymbol, int index, char* text, int size);
    void addCommands(vector<MenuObject*> inputVector);

    void printByLevels();


  private:
    int size;
    int objectsNum;
    MenuObject* subMenu;
    vector<MenuObject*> vMenuObjects;

};

#endif
