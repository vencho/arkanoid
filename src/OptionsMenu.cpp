#include<OptionsMenu.h>
#include<MenuStack.h>
#include<Menu.h>
#include<ActionMenuItem.h>
#include<MenuNavigationCommand.h>
#include<AbstractCommand.h>
#include<DoNothingCommand.h>


OptionsMenu::OptionsMenu(Application &application) : Menu("Options menu", application) {
  ActionMenuItem *exampleitem;;
  AbstractCommand *examplecommand = new DoNothingCommand();
  exampleitem = new ActionMenuItem("Example", true, *examplecommand);
  addMenuItem(exampleitem);

  ActionMenuItem *backitem;
  MenuNavigationCommand *backcommand = new MenuNavigationCommand(NULL, application);
  backitem = new ActionMenuItem("Back", false, *backcommand);
  addMenuItem(backitem);
}
