#include<animators/ExplosionAnimator.h>
#include<SpriteUtils.h>

void ExplosionAnimator::loadSprites(SDL_Surface *spritesheet) {
  explosionSprites.resize(3);
  explosionSprites[0] = SpriteUtils::loadSingleSprite(spritesheet, 357, 54, 24, 24);
  explosionSprites[1] = SpriteUtils::loadSingleSprite(spritesheet, 395, 52, 28, 28);
  explosionSprites[2] = SpriteUtils::loadSingleSprite(spritesheet, 433, 53, 32, 32);
}

void ExplosionAnimator::draw(SDL_Surface *target, int baseX, int baseY) {
  for(int i = 0; i < ongoingExplosions.size(); i++) {
    int phase = ongoingExplosions[i].ticksSoFar / ticksPerSprite;
    SDL_Rect r;
    r.x = baseX + ongoingExplosions[i].centreX - (explosionSprites[phase] -> w) / 2;
    r.y = baseY + ongoingExplosions[i].centreY - (explosionSprites[phase] -> h) / 2;
    SDL_BlitSurface(explosionSprites[phase], nullptr, target, &r);
  }
  incrementAll();
}

void ExplosionAnimator::incrementAll() {
  for(int i = 0; i < ongoingExplosions.size(); i++) {
    ongoingExplosions[i].ticksSoFar++;
    if(ongoingExplosions[i].ticksSoFar == explosionSprites.size() * ticksPerSprite) {
      ongoingExplosions.erase(ongoingExplosions.begin() + i);
      i--;
    }
  }
}

void ExplosionAnimator::addExplosion(int centreX, int centreY) {
  ongoingExplosions.emplace_back(centreX, centreY);
}

ExplosionAnimator::explosion::explosion(int x, int y) {
  centreX = x;
  centreY = y;
  ticksSoFar = 0;
}

void ExplosionAnimator::notifyEnemyDestroyed(const Enemy &enemy) {
  addExplosion(enemy.getX() + enemy.getWidth() / 2, enemy.getY() + enemy.getHeight()/2);
}

void ExplosionAnimator::reset() {
  ongoingExplosions.clear();
}
