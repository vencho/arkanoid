#ifndef QUIT_COMMAND_H_INCLUDED
#define QUIT_COMMAND_H_INCLUDED
#include<AbstractCommand.h>
class Application;
class QuitCommand : public AbstractCommand {
 private:
  Application &application;
 public:
  QuitCommand(Application &application);
  virtual void execute();
};
#endif
