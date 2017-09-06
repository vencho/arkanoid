#include<MainMenu.h>
#include<MenuStack.h>
#include<Menu.h>
#include<ActionMenuItem.h>
#include<AbstractCommand.h>
#include<DoNothingCommand.h>
#include<NavigationMenuItem.h>
#include<OptionsMenu.h>


MainMenu::MainMenu(MenuStack &menuStack) : Menu("Main menu", menuStack) {
  ActionMenuItem *newgameitem; 
  AbstractCommand *newgamecommand = new DoNothingCommand();
  newgameitem = new ActionMenuItem("New game", true, *newgamecommand);
  addMenuItem(newgameitem);

  NavigationMenuItem *optionsitem;
  Menu *options = new OptionsMenu(menuStack);
  optionsitem = new NavigationMenuItem("Options", false, options, *this);
  addMenuItem(optionsitem); 

  ActionMenuItem *quititem;
  AbstractCommand *quitcommand = new DoNothingCommand();
  quititem = new ActionMenuItem("Quit", false, *quitcommand);
  addMenuItem(quititem);
}






