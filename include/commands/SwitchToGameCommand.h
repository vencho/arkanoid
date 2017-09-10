#ifndef SWITCH_TO_GAME_COMMAND_H_INCLUDED
#define SWITCH_TO_GAME_COMMAND_H_INCLUDED
#include<commands/AbstractCommand.h>
class Application;

class SwitchToGameCommand : public AbstractCommand {
 private:
  Application &application;
 public:
  SwitchToGameCommand(Application &application);
  virtual void execute();
};
#endif
