#include<model/Tile.h>
#include<Configuration.h>

Tile::Tile(int i, int j, int colour) : GameObject(), DockedRectangle( (j-1)*tilePhysicalWidth, (i-1)*tilePhysicalHeight, 
							tilePhysicalWidth, 
							tilePhysicalHeight) {
  // static int nextIdToAssign = 7;

  if(colour < 8) healthleft = 1;
  else {
    if(colour == 8) healthleft = 2;
    else if(colour == 9) healthleft = 3;
    healthleft += Configuration::toughTileBonus;
  }
  this -> indestructible = false;
  this -> colour = colour;
  // this -> id = nextIdToAssign++;
}

/*
int Tile::getId() const {
  return id;
}
*/

int Tile::getColour() const {
  return colour;
}

int Tile::getHealth() const {
  return healthleft;
}

void Tile::takeDamage() {
  if(!indestructible) {
    healthleft--;
  }
}
