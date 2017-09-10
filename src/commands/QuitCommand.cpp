#include<commands/QuitCommand.h>
#include<Application.h>

QuitCommand:: QuitCommand(Application &application) : application(application) { }
void QuitCommand::execute() {
  application.requestEnd();
}
