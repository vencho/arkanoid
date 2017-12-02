#include<model/Bullet.h>

Bullet::Bullet(const Paddle &player, bool leftside) :
  MovableRectangle(  player.getX() + (leftside ? player.getWidth() / 3 : 2*player.getWidth() / 3),
		     player.getY() - 5,
		     5, 5, 0, -8) {
		    
}
