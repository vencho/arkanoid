#ifndef DONOTHING_COMMAND_H_DEFINED
#define DONOTHING_COMMAND_H_DEFINED
#include<AbstractCommand.h>
class DoNothingCommand : public AbstractCommand {
 public:
  DoNothingCommand();
  virtual void execute();
};
#endif
