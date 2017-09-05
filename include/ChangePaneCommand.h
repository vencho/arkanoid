#ifndef CHANGE_PANE_COMMAND_H_DEFINED
#define CHANGE_PANE_COMMAND_H_DEFINED

#include<AbstractCommand.h>
class Application;
class DrawablePane;

class ChangePaneCommand : public AbstractCommand {
 private:
  Application &owner;
  DrawablePane *pane;
 public:
  ChangePaneCommand(Application &owner, DrawablePane *pane);
  virtual void execute();
};

#endif
