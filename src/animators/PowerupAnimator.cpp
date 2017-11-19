#include<animators/PowerupAnimator.h>
#include<SDL.h>
#include<model/Powerup.h>
#include<vector>
#include<unordered_map>

PowerupAnimator::PowerupAnimator(std::vector<Powerup> &powerups) : powerups(powerups), 
								   powerupSprites(7, std::vector<SDL_Surface *>(8, nullptr)) {
  whichRow['L'] = 0;
  whichRow['E'] = 1;
  whichRow['C'] = 2;
  whichRow['S'] = 3;
  whichRow['D'] = 4;
  whichRow['B'] = 5;
  whichRow['P'] = 6;
}

void PowerupAnimator::loadSprites(std::vector<SDL_Surface *> &sprites) {
  for(int i = 0; i < sprites.size(); i++) {
    powerupSprites[i/8][i%8] = sprites[i];
  }
}

void PowerupAnimator::notifyPowerupDestroyed(int id) {
  whichFrame.erase(id);
}

void PowerupAnimator::drawPowerups(SDL_Surface *target, int baseX, int baseY) {
  incrementAll();
  for(int i = 0; i < powerups.size(); i++) {
    Powerup &powerup = powerups[i];
    SDL_Rect r;
    r.x = powerup.getX() + baseX;
    r.y = powerup.getY() + baseY;
    int row = whichRow[powerup.getType()];
    int column = whichFrame[powerup.getId()] / framesPerSprite;
    SDL_BlitSurface(powerupSprites[row][column], nullptr, target, &r);
  }
}

void PowerupAnimator::incrementAll() {
  std::unordered_map<int, int> :: iterator it;
  for(it = whichFrame.begin(); it != whichFrame.end(); it++) {
    it -> second++;
    if(it -> second == powerupSprites[0].size() * framesPerSprite) it -> second = 0;
  }
}

