#include<SetValueMenuItem.h>
#include<MenuItemDrawer.h>
#include<string>

int SetValueMenuItem::getVal() {
  return val;
}

SetValueMenuItem::SetValueMenuItem(std::string text, 
				   bool selected, 
				   const int &min, 
				   const int &max, 
				   int &val) :
  min(min), max(max), val(val), MenuItem(text, selected) { }

void SetValueMenuItem::activate() { }

void SetValueMenuItem::left() {
  val--;
  if(val < min) val = max;
}

void SetValueMenuItem::right() {
  val++;
  if(val > max) val = min;
}

void SetValueMenuItem::drawYourself(MenuItemDrawer &mid) {
  mid.drawSetValueMenuItem(this);
}
