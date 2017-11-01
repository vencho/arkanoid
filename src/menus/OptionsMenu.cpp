#include<menus/OptionsMenu.h>
#include<menus/Menu.h>
#include<menus/ActionMenuItem.h>
#include<menus/SetValueMenuItem.h>
#include<commands/MenuNavigationCommand.h>
#include<commands/AbstractCommand.h>
#include<commands/DoNothingCommand.h>
#include<Configuration.h>

OptionsMenu::OptionsMenu(Application &application) : Menu("Options menu", application) {
  v.emplace_back(new SetValueMenuItem("Difficulty", true, 
					Configuration::minDifficulty,
					Configuration::maxDifficulty,
				      Configuration::difficulty)
		 );


  v.emplace_back(new SetValueMenuItem("Level", false, 
				   Configuration::minLevel,
				   Configuration::maxLevel,
				   Configuration::level)
		 );

  MenuNavigationCommand *backcommand = new MenuNavigationCommand(NULL, application);
  v.emplace_back(new ActionMenuItem("Back", false, *backcommand));
}

