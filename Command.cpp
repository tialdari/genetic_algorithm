#include <iostream>
#include "MenuObject.h"
#include "Menu.h"
#include "MenuCommand.h"
#include "Command.h"

using namespace std;

Command::Command()
{

}


bool Command::runCommand()
{
  if(DEBUG) cout << "command's run method is running" << endl;
  return true;
}
