#include<MainMenu.h>
#include<MenuStack.h>
#include<Menu.h>
#include<ActionMenuItem.h>
#include<AbstractCommand.h>
#include<DoNothingCommand.h>
#include<OptionsMenu.h>
#include<Application.h>
#include<SwitchToGameCommand.h>
#include<QuitCommand.h>
#include<MenuNavigationCommand.h>

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

