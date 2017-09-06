#ifndef MENU_STACK_H_DEFINED
#define MENU_STACK_H_DEFINED
#include<vector>

class Menu;

class MenuStack {
 private:
  std::vector<Menu *> stack;
  
 public:
  MenuStack();
  Menu *top(); 
  void pop(); 
  bool empty(); 
  void push(Menu *menu);
};

#endif
