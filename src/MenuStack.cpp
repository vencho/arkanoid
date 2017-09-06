#include<MenuStack.h>
#include<Menu.h>
#include<vector>
MenuStack::MenuStack() { }
Menu* MenuStack::top() { return stack.back(); }
void MenuStack::pop() { stack.pop_back(); }
bool MenuStack::empty() { return stack.empty(); }
void MenuStack::push(Menu *menu) { stack.push_back(menu); }
