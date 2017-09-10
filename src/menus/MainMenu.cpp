#include<menus/MainMenu.h>
#include<menus/Menu.h>
#include<menus/ActionMenuItem.h>
#include<menus/OptionsMenu.h>
#include<commands/AbstractCommand.h>
#include<commands/DoNothingCommand.h>
#include<commands/SwitchToGameCommand.h>
#include<commands/QuitCommand.h>
#include<commands/MenuNavigationCommand.h>
#include<Application.h>

MainMenu::MainMenu(Application &app) : Menu("Main menu", app) {
  ActionMenuItem *newgameitem; 
  AbstractCommand *newgamecommand = new SwitchToGameCommand(application);
  newgameitem = new ActionMenuItem("New game", true, *newgamecommand);
  addMenuItem(newgameitem);

  ActionMenuItem *optionsitem;
  Menu *options = new OptionsMenu(application);
  AbstractCommand *optionscommand = new MenuNavigationCommand(options, application);
  optionsitem = new ActionMenuItem("Options", false, *optionscommand);
  addMenuItem(optionsitem); 

  ActionMenuItem *quititem;
  AbstractCommand *quitcommand = new QuitCommand(application);
  quititem = new ActionMenuItem("Quit", false, *quitcommand);
  addMenuItem(quititem);
}

