#include <iostream>
#include <vector>
#include "MenuObject.h"
#include "Menu.h"
#include "MenuCommand.h"
#include "Command.h"
#include "IO.h"

using namespace std;

Menu::~Menu()
{
  cout << "deleting " << getName() << "'s objects" << endl;

  for(int i = 0; i < vMenuObjects.size(); i++)
  {
    cout << "deleting " << vMenuObjects[i] -> getName() << endl;
    delete vMenuObjects[i];
  }
}


MenuObject* Menu::getSubMenu()
{
  return subMenu;
}

void Menu::setvMenuObjects(vector<MenuObject*> newMenuObjects){
  this -> vMenuObjects = newMenuObjects;
  cout << "new menu objects vector" << endl;
}

void Menu::setSubmenu(Menu* subMenu)
{
  this -> subMenu = subMenu;
}

void Menu::addNewCommand(MenuObject* menuObj)
{

  //if the array doesn't already contain the object being added -> continue
  for(int i = 0; i < size; i++){
    if(vMenuObjects[i] == menuObj) {
      if(DEBUG){
         cout << "ERROR: the object you want to add ";
         cout << "is already in the array " << endl;
      }
      return;
    }
  }
  vMenuObjects.push_back(menuObj);
  size++;
  if (DEBUG) cout << "new command has been added to the " << name
                  << " at the index " << size - 1 << endl;

}

void Menu::deleteCommand(int index)
{
  if(index < 0){

    if (DEBUG) cout << "ERROR: cell number can't be less than 0" << endl;
    return;

  }else if (index >= size){

      if (DEBUG) {
        cout << "ERROR: index out of range " << endl;
      }
      return;

  }else{
    vMenuObjects.erase(vMenuObjects.begin() + index);
    if (DEBUG) cout << "the array cell no " << index
                    << " has been erased " << endl;
  }
}

void Menu::run()
{
  int commandIndex;

  while(true){

    cout << name << "(" << command << ")" << endl;

    menuItemsList();
    string commandName = getCommandName();
    if(builtInCommands(commandName) == true){}
    else if(commandName == "back"){
      return;
    }
    else{
      commandIndex = getCommandIndex(commandName);
      executeCommand(commandIndex);
    }
  }

}

void Menu::menuItemsList()
{
  int lastPos = 0;

  for(int i = 0; i < size; i++){

    cout << " " << (i + 1) << ". ";
    cout << vMenuObjects[i] -> printSubmenu(vMenuObjects[i])
         << "(" << vMenuObjects[i] -> getCommandsName() << ")" << endl;
    lastPos = i + 2;
  }
  cout << " " << lastPos << ". Search(search)" << endl;
  cout << " " << lastPos + 1 << ". Help(help)" << endl;
  cout << " " << lastPos + 2 << ". Go back(back)" << endl;
}

string Menu::getCommandName(){

  IO io;
  return io.getString();
}

int Menu::getCommandIndex(string commandName)
{
  bool ifContinue = true;
  int commandNum;

  while(ifContinue)
  {
    for(int i = 0; i < size; i++){

      if(commandName == vMenuObjects[i] -> getCommandsName())
      {
        commandNum = i;
        return i;
      }
    }
    ifContinue = false;
     cout << "No such command! " << endl;
  }
  return -1;
}

void Menu::executeCommand(int commandIndex)
{
  if(commandIndex == -1){
    if (DEBUG) cout << "ERROR: no such command" << endl;
    return;

  }else if(commandIndex < 0){

    if (DEBUG) cout << "ERROR: cell number can't be less than 0" << endl;
    return;

  }else if(commandIndex >= size){

    if (DEBUG) cout << "ERROR: index out of range " << endl;
    return;

  }else vMenuObjects[commandIndex] -> run();

}

/*
void Menu::search(string commandName){

  string currentCommandName;
  cout << "searching " << getName() << endl;

  for(int i = 0; i < size; i++){
    currentCommandName = vMenuObjects[i] -> getCommandsName();
    //cout << currentCommandName << " ?= " << commandName << endl;
    //str1.compare(str2)
    if(commandName.compare(currentCommandName)){
    //  cout << "!!! " << currentCommandName << " == " << commandName << "." << endl;
      cout << printSubmenu(vMenuObjects[i]) + "(" << currentCommandName
           << ")" << endl;
    }
    vMenuObjects[i] -> search(commandName);
  }
}
*/

void Menu::search(string commandName){

  for(int i = 0; i < size; i++){

    if(vMenuObjects[i] -> getCommandsName() == commandName){
      cout << printSubmenu(vMenuObjects[i]) + "(" << vMenuObjects[i] -> getCommandsName()
           << ")" << endl;
    }
    vMenuObjects[i] -> search(commandName);
  }
}


bool Menu::builtInCommands(string expression){


    MenuObject* command;
    string commandName;

    string searchString;
    string otherString;

    if(expression.length() >= 7){
       searchString = expression.substr(0,6);
       otherString = expression.substr(7);
    }

    for(int i = 0; i < size; i++){
      command = vMenuObjects[i];
      commandName = command -> getCommandsName();

      if(searchString == "search"){
        search(otherString);
        return true;
      }else if(expression == "help " + commandName){
        command -> help();
        return true;
      }
    }
    return false;
}


string Menu::menuToString(){

  string menuString = "(";
  string menuParameter = getName();
  menuString += nameToString(menuParameter) + ",";

  menuParameter = getCommandsName();
  menuString += nameToString(menuParameter) + ";";

  menuString += childrenToString();
  menuString += ")";

  return menuString;
}

string Menu::childrenToString(){

  string childrenString = "";
  int comasNum = size - 1;

  for(int i = 0; i < size; i++){
    childrenString += vMenuObjects[i] -> menuObjectToString();
    if(i < comasNum) childrenString += ",";
  }
  return childrenString;
}

int Menu::readWord(char* stringMenu, int size, int &startIndex, string& resultString, bool &pSucc){
  resultString = "";
  char currentSymbol = stringMenu[++startIndex];

  const char baseSymbols[] = {'(', ')', '[', ']', ';',','};
  int baseSymbolsSize = 6;
  char symbol = '\'';

  string currentStringSymbol;

  while(currentSymbol != symbol){
    for(int i = 0; i < baseSymbolsSize; i++){
      if(baseSymbols[i] == currentSymbol){
        error('\'', startIndex, stringMenu, size);
        pSucc = false;
        return startIndex;
      }
    }
    if(startIndex >= size){
      pSucc = false;
      return startIndex;
    }
    currentStringSymbol = string(1, currentSymbol);
    resultString += currentStringSymbol;
    currentSymbol = stringMenu[++startIndex];
  }

  pSucc = true;
  return startIndex;
}

Menu* Menu::readMenu(char* stringMenu, int size, int &startIndex, MenuObject* subMenu, bool &pSucc){

  Menu* menu = new Menu("test menu", "test_menu", subMenu);

  const char menuSymbols[] = {'(', '\'', 'n', '\'', ',', '\'', 'c', '\'', ';'};
  int mSymbolsSize = 9;

  char c_childrenNum = 0;
  const char endSymbols[] = {c_childrenNum,'(', '['};
  int endSymbolsSize = 3;
  int asciiConst = 48;
  int i_childrenNum = c_childrenNum;
  cout << i_childrenNum << endl;

  pSucc = false;
  bool namesRead = pSucc;
  int symbolIndex = 0;
  char symbol = menuSymbols[symbolIndex];
  char inputSymbol = stringMenu[startIndex];
  string name;

  while(!namesRead){

    if(symbol == inputSymbol){
      cout << "symbol : " << inputSymbol << endl;

      if(symbol == ';') {
        pSucc = true;
      }

      symbol = menuSymbols[++symbolIndex];
      inputSymbol = stringMenu[++startIndex];

    }else if(symbol == 'n' || symbol == 'c'){

      startIndex--;
      startIndex = readWord(stringMenu, size, startIndex, name, pSucc);
      if(symbol == 'n'){
      //  cout << "menu's name: " << name << endl;
        menu -> setName(name);
      }else if(symbol == 'c'){
      //  cout << "menu's command: " << name << endl;
        menu -> setCommand(name);
      }
      if(pSucc == false){
        return menu;
      }else pSucc = false;

      symbolIndex += 2;
      symbol = menuSymbols[symbolIndex];
      inputSymbol = stringMenu[++startIndex];

    }else{
      error(symbol, startIndex, stringMenu, size);
      pSucc = true;
      return menu;
    }
    namesRead = pSucc;
}
/*
  inputSymbol = stringMenu[--startIndex];
  if(symbol != ';'){
     error(symbol, startIndex, stringMenu, size);
     return menu;
  } else  inputSymbol = stringMenu[++startIndex];

  cout << "symbol after reading menu par: " << inputSymbol << endl;
  pSucc = false;

*/
inputSymbol = stringMenu[startIndex];


  for(int i = 0; i < endSymbolsSize; i++){
    cout << "inputSymbol; " << inputSymbol << endl;

    if(i == 0){
      inputSymbol = stringMenu[startIndex];
      i_childrenNum = inputSymbol -asciiConst;

      cout << "i_childrenNum: " << i_childrenNum << endl;
      startIndex += 2;
      inputSymbol = stringMenu[startIndex];
      if(i_childrenNum == 0){
        cout << "no children";
        return menu;
      }
    }
    if(inputSymbol == endSymbols[i]){
      vector<MenuObject*> accumVector(readChildren(stringMenu, size, startIndex, inputSymbol, menu, pSucc));
      menu -> addCommands(accumVector);
      cout << "children size after childrenRead: " << accumVector.size();
      if(i_childrenNum != accumVector.size()){
        cout << "\nERROR: wrong children number!" << endl;
        return menu;
      }
       if(pSucc == false){
         error(')', startIndex, stringMenu, size);
         return menu;
       }
       inputSymbol = stringMenu[startIndex];
    }
  }
  if(startIndex == size - 1) return menu;

  if(inputSymbol != ')'){
    error(symbol, startIndex, stringMenu, size);
  }else{
    inputSymbol = stringMenu[++startIndex];
  }
  return menu;
}


MenuCommand* Menu::readCommand(char* stringMenu, int size, int &startIndex, MenuObject* subMenu, bool &pSucc){

  Command* newtestCommand = new TestCommand();
  MenuCommand* testCommand = new MenuCommand("testCommand", "test_ comm_n", subMenu, newtestCommand);

  char inputSymbol = stringMenu[startIndex];

  const char commandSymbols[] = {'[', '\'', 'n', '\'', ',', '\'', 'c', '\'', ',', '\'', 'd', '\'', ']'};
  int commandIndex = 0;
  char commandSymbol = commandSymbols[commandIndex];

  pSucc = false;
  bool commandRead = pSucc;
  string result;

  while(!commandRead){
    if(inputSymbol == commandSymbol){

              if(commandSymbol == ',' || commandSymbol == '[' ){
                commandSymbol = commandSymbols[++commandIndex];
                inputSymbol = stringMenu[++startIndex];
              }else if(commandSymbol == '\''){
                  commandSymbol = commandSymbols[++commandIndex];
                  if(commandSymbol == 'n' || commandSymbol == 'c' || commandSymbol == 'd'){
                    startIndex = readWord(stringMenu, size, startIndex, result, pSucc);
                    switch(commandSymbol){
                      case 'n':
                        testCommand -> setName(result);
                      //  cout << "command's name: " << testCommand -> getName() << endl;
                      break;

                      case 'c':
                        testCommand -> setCommand(result);
                      //  cout << "command's command: " << testCommand -> getCommandsName() << endl;
                      break;

                      case 'd':
                        newtestCommand -> setDescription(result);
                        //testCommand -> help();
                      break;

                      default: break;
                      }
                    commandIndex += 2;
                    commandSymbol = commandSymbols[commandIndex];
                    inputSymbol = stringMenu[++startIndex];
                  }else inputSymbol = stringMenu[++startIndex];
              }else if(commandSymbol == ']'){
                ++startIndex;
                inputSymbol = stringMenu[startIndex];
                pSucc = true;
                return testCommand;
              }
  }else{
      error('s', startIndex, stringMenu, size);
      return testCommand;
    }
  }
//  cout << "end of command reading " << endl;
  return testCommand;
}

  vector<MenuObject*> Menu::readChildren(char* stringMenu, int size, int &startIndex, char symbol, MenuObject* subMenu, bool &pSucc){



  vector<MenuObject*> children;
  MenuCommand* newCommand;
  Menu* newMenu;

  bool success = false;

    while(!success){

      switch(symbol){
        case '[':
          newCommand = readCommand(stringMenu, size, startIndex, subMenu, pSucc);
          cout << "command " << newCommand -> getName() << " read" << endl;
          children.push_back(newCommand);
        break;

        case '(':
          newMenu = readMenu(stringMenu, size, startIndex, subMenu, pSucc);
          //cout << newMenu -> getName() ;//<< ", fst child name: " << endl;
          cout << newMenu -> getName() << " read" <<  endl;
          children.push_back(newMenu);
        break;

        case ',':
          startIndex++;
        break;

        case ')':
          success = true;
          pSucc = true;
          cout << "end of menu" << endl;
        break;

        default:

          success = true;
          return children;
      }
      symbol = stringMenu[startIndex];
  }
  pSucc = true;
  cout << "size of children: " << children.size();
  cout << " of menu: " << subMenu -> getName() << endl;
  symbol = stringMenu[startIndex];

  cout << "after reading children,  startIndex: " << startIndex << " output symbol: " << symbol << endl;
  return children;
}

void Menu::error(char missingSymbol, int index, char* text, int size){

    cout << "ERROR: missing symbol at '_' " << endl;
    for(int i = 0; i < size; i++){
      if(i == index) cout << "_";
      cout << text[i];
    } cout << "\n\n" ;

}

void Menu::addCommands(vector<MenuObject*> inputVector){
  int innerSize = inputVector.size();
  vMenuObjects.clear();

  for(int i = 0; i < innerSize; i++){
    vMenuObjects.push_back(inputVector[i]);
  //  cout << vMenuObjects[i] -> getName() << " added" << endl;
  }
  size = innerSize;
//  cout << getName() << "\'s size: " << size << endl;
//  cout << "new commands added to " << getName() << endl;
}

void Menu::printByLevels(){

  int queueSize = size;
  vector<MenuObject*> queue(vMenuObjects);

  for(int i = 0; i < queueSize; i++){
    cout << queue[i] -> getName() << " ";
  //queue.push_back(queue[i] -> )
  }
}
