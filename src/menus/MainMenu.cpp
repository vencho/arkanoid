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

MainMenu::MainMenu(Application &app) : Menu("Main menu", app), options(new OptionsMenu(app)) {
  AbstractCommand *newgamecommand = new SwitchToGameCommand(application);
  v.emplace_back(new ActionMenuItem("New game", true, *newgamecommand));

  AbstractCommand *optionscommand = new MenuNavigationCommand(options.get(), application);
  v.emplace_back(new ActionMenuItem("Options", false, *optionscommand));

  AbstractCommand *quitcommand = new QuitCommand(application);
  v.emplace_back(new ActionMenuItem("Quit", false, *quitcommand));
}

