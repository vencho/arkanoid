#include<OptionsMenu.h>
#include<MenuStack.h>
#include<Menu.h>
#include<ActionMenuItem.h>
#include<NavigationMenuItem.h>
#include<AbstractCommand.h>
#include<DoNothingCommand.h>


OptionsMenu::OptionsMenu(MenuStack &menuStack) : Menu("Options menu", menuStack) {
  ActionMenuItem *exampleitem;;
  AbstractCommand *examplecommand = new DoNothingCommand();
  exampleitem = new ActionMenuItem("Example", true, *examplecommand);
  addMenuItem(exampleitem);

  NavigationMenuItem *backitem;
  backitem = new NavigationMenuItem("Back", false, NULL, *this);
  addMenuItem(backitem);
}
