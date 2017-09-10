#ifndef ABSTRACT_COMMAND_H_INCLUDED
#define ABSTRACT_COMMAND_H_INCLUDED

class AbstractCommand {
 public:
  virtual void execute() = 0;
};

#endif
