#include<menus/OptionsMenu.h>
#include<menus/Menu.h>
#include<menus/ActionMenuItem.h>
#include<menus/SetValueMenuItem.h>
#include<commands/MenuNavigationCommand.h>
#include<commands/AbstractCommand.h>
#include<commands/DoNothingCommand.h>
#include<Configuration.h>

OptionsMenu::OptionsMenu(Application &application) : Menu("Options menu", application) {
  SetValueMenuItem *difficultyitem;
  difficultyitem = new SetValueMenuItem("Difficulty", true, 
					Configuration::minDifficulty,
					Configuration::maxDifficulty,
					Configuration::difficulty);

  addMenuItem(difficultyitem);

  SetValueMenuItem *levelitem;
  levelitem = new SetValueMenuItem("Level", false, 
				   Configuration::minLevel,
				   Configuration::maxLevel,
				   Configuration::level);
  addMenuItem(levelitem);

  ActionMenuItem *backitem;
  MenuNavigationCommand *backcommand = new MenuNavigationCommand(NULL, application);
  backitem = new ActionMenuItem("Back", false, *backcommand);
  addMenuItem(backitem);
}
