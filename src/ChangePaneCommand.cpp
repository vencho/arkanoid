#include<ChangePaneCommand.h>
#include<Application.h>
#include<DrawablePane.h>

ChangePaneCommand::ChangePaneCommand(Application &owner, DrawablePane *pane) : owner(owner) { 
  this -> pane = pane; 
}


void ChangePaneCommand::execute() {
  owner.setActivePane(pane);
}
