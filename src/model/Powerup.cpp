#include<model/Powerup.h>
#include<model/Tile.h>
#include<Configuration.h>

char Powerup::getType() const {
  return type;
}

Powerup::Powerup(const Tile &tile, char type) : MovableRectangle(tile.getX(), tile.getY(), 
								 powerupPhysicalWidth, 
								 powerupPhysicalHeight, 0, Configuration::powerupSpeed) {
  this -> type = type;
}
