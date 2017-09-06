#include<SwitchToGameCommand.h>
#include<Application.h>
SwitchToGameCommand::SwitchToGameCommand(Application &application) : application(application) { }
void SwitchToGameCommand::execute() {
  application.switchToGameMode();
}
