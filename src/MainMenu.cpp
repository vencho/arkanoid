#include<MainMenu.h>
#include<MenuStack.h>
#include<Menu.h>
#include<ActionMenuItem.h>
#include<AbstractCommand.h>
#include<DoNothingCommand.h>
#include<NavigationMenuItem.h>
#include<OptionsMenu.h>
#include<Application.h>
#include<SwitchToGameCommand.h>
#include<QuitCommand.h>

MainMenu::MainMenu(MenuStack &menuStack, Application &application) : Menu("Main menu", menuStack), application(application) {
  ActionMenuItem *newgameitem; 
  AbstractCommand *newgamecommand = new SwitchToGameCommand(application);
  newgameitem = new ActionMenuItem("New game", true, *newgamecommand);
  addMenuItem(newgameitem);

  NavigationMenuItem *optionsitem;
  Menu *options = new OptionsMenu(menuStack);
  optionsitem = new NavigationMenuItem("Options", false, options, *this);
  addMenuItem(optionsitem); 

  ActionMenuItem *quititem;
  AbstractCommand *quitcommand = new QuitCommand(application);
  quititem = new ActionMenuItem("Quit", false, *quitcommand);
  addMenuItem(quititem);
}

