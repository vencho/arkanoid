#include<SpriteUtils.h>
#include<model/Enemy.h>
#include<model/Ball.h>
#include<model/Bullet.h>
#include<observers/GameEventMonitor.h>
#include<vector>
#include<unordered_map>
#include<utility>
#include<SDL.h>
#include<cstdio>


class CountPacket {
public:
  int cycle, sprite, framesSoFar;
  CountPacket() { }
  CountPacket(int cycle, int sprite, int framesSoFar) {
    this -> cycle = cycle;
    this -> sprite = sprite;
    this -> framesSoFar = framesSoFar;
  }
};


template <class T> class AnimatorBase : public GameEventMonitor {
protected:
  const std::vector<T> &gameObjects;
  std::unordered_map<int, CountPacket> frameCounter;
  std::vector<std::vector<SDL_Surface *>> sprites;
  std::vector<int> framesPerSprite;
  std::vector<int> nextCycle;
  SDL_Surface *shadowSprite;

  void incrementAll() {
    for(std::unordered_map<int, CountPacket> :: iterator it = frameCounter.begin(); it != frameCounter.end(); it++) {
      advanceAnimation(it);
    }
  }

  void switchToAnimation(int id, int animationIdx) {
    frameCounter[id] = CountPacket(animationIdx, 0, 0);
  }

  void advanceAnimation(std::unordered_map<int, CountPacket> :: iterator it) {
    CountPacket &p = it -> second;
    advanceAnimation(p);
  }

  void advanceAnimation(int id) {
    CountPacket &p = frameCounter[id];
    advanceAnimation(p);
  }

  void advanceAnimation(CountPacket &p) {
    p.framesSoFar++;
    if(p.framesSoFar == framesPerSprite[p.cycle]) {
      p.framesSoFar = 0;
      p.sprite++;
      if(p.sprite == sprites[p.cycle].size()) {
	p.sprite = 0;
	p.cycle = nextCycle[p.cycle];
      }
    }
  }

 public:

  AnimatorBase<T>(const std::vector<T> &gameObjects) : gameObjects(gameObjects) {     
    shadowSprite = nullptr;
  }

  virtual void draw(SDL_Surface *target, int baseX, int baseY) {
    for(int i = 0; i < gameObjects.size(); i++) {
      CountPacket p = frameCounter[gameObjects[i].getId()];
      SDL_Surface *pic = sprites[p.cycle][p.sprite];
      SDL_Rect r;
      r.x = baseX + gameObjects[i].getX();
      r.y = baseY + gameObjects[i].getY();
      SDL_BlitSurface(pic, nullptr, target, &r);
    }
    incrementAll();
  }


  void reset() {
    frameCounter.clear();
  }

  virtual void loadSprites(SDL_Surface *spritesheet) = 0;
  virtual void notifyEnters(const T &gameObject) = 0;

  virtual void notifyLeaves(const T &gameObject) {
    frameCounter.erase(gameObject.getId());
  }

  virtual void drawShadows(SDL_Surface *target, int baseX, int baseY) {
    for(int i = 0; i < gameObjects.size(); i++) {
      SDL_Rect r;
      r.x = baseX + gameObjects[i].getX();
      r.y = baseY + gameObjects[i].getY();
      SDL_BlitSurface(shadowSprite, nullptr, target, &r);
    }
  }
};

template <class T> class Animator : public AnimatorBase<T> { };

template <> class Animator<Ball> : public AnimatorBase<Ball> {
public:
  Animator<Ball>(const std::vector<Ball> &gameObjects) : AnimatorBase<Ball>(gameObjects) { }
  virtual void loadSprites(SDL_Surface *spritesheet) { 
    std::vector<SDL_Surface *> v;
    SpriteUtils::loadSpritesFromGrid(spritesheet, 129, 67, 10, 10, 0, 0, 1, 5, 10, 10, v);
    sprites.push_back(std::vector<SDL_Surface *>());
    sprites.back().push_back(v[0]);
    framesPerSprite.push_back(1);
    nextCycle.push_back(0);
    shadowSprite = v[4];
  }
  virtual void notifyEnters(const Ball &gameObject) { 
    frameCounter[gameObject.getId()] = CountPacket(0, 0, 0);
  }
};

template <> class Animator<Powerup> : public AnimatorBase<Powerup> {
public:
  Animator<Powerup>(const std::vector<Powerup> &gameObjects) : AnimatorBase<Powerup>(gameObjects) { }
  virtual void loadSprites(SDL_Surface *spritesheet) {
    std::vector<SDL_Surface *> v;
    SpriteUtils::loadSpritesFromGrid(spritesheet, 129, 165, 44, 22, 0, 2, 7, 8, 44, 22, v);
    sprites.resize(7);
    for(int i = 0; i < 7; i++) sprites[i].resize(8);
    framesPerSprite.resize(7);
    nextCycle.resize(7);
    for(int i = 0; i < 7; i++) nextCycle[i] = i;
    for(int i = 0; i < 7; i++) framesPerSprite[i] = 5;
    for(int i = 0; i < v.size(); i++) sprites[i/8][i%8] = v[i];
  }
  virtual void notifyEnters(const Powerup &gameObject) {
    int row;
    switch(gameObject.getType()) {
    case 'L': row = 0; break;
    case 'E': row = 1; break;
    case 'C': row = 2; break;
    case 'S': row = 3; break;
    case 'D': row = 4; break;
    case 'B': row = 5; break;
    case 'P': row = 6; break;
    };
    frameCounter[gameObject.getId()] = CountPacket(row, 0, 0);
  }
};

template <> class Animator<Enemy> : public AnimatorBase<Enemy> {
public:
  Animator<Enemy>(const std::vector<Enemy> &gameObjects) : AnimatorBase<Enemy>(gameObjects) { }
  virtual void loadSprites(SDL_Surface *spritesheet) {
    sprites.resize(1);
    framesPerSprite.resize(1);
    nextCycle.resize(1);
    SpriteUtils::loadSpritesFromGrid(spritesheet, 8, 335, 34, 44, 10, 0, 5, 5, 
				     Enemy::enemyPhysicalWidth, Enemy::enemyPhysicalHeight, sprites[0]);
    framesPerSprite[0] = 3; 
    nextCycle[0] = 0;
  }
  virtual void notifyEnters(const Enemy &gameObject) {
    frameCounter[gameObject.getId()] = CountPacket(0, 0, 0);
  }
};

template <> class Animator<Tile> : public AnimatorBase<Tile> {
public:
  Animator<Tile>(const std::vector<Tile> &gameObjects) : AnimatorBase<Tile>(gameObjects) { }
  virtual void loadSprites(SDL_Surface *spritesheet) {
    std::vector<SDL_Surface *> v;
    SpriteUtils::loadSpritesFromGrid(spritesheet, 129, 1, 44, 22, 0, 0, 3, 3, 44, 22, v);
    sprites.resize(12);
    nextCycle.resize(12);
    framesPerSprite.resize(12);
    for(int i = 0; i < 8; i++) {
      sprites[i].push_back(v[i]);
      nextCycle[i] = i;
      framesPerSprite[i] = 1;
    }
    shadowSprite = v[8];
    v.clear();
    SpriteUtils::loadSpritesFromGrid(spritesheet, 129, 77, 44, 22, 0, 0, 4, 5, 44, 22, v);
    for(int i = 8; i < 10; i++) {
      sprites[i].push_back(v[(i-8)*10]);
      nextCycle[i] = i;
      framesPerSprite[i] = 1;
    }
    for(int i = 10; i < 12; i++) {
      sprites[i].resize(10);
      nextCycle[i] = i - 2;
      framesPerSprite[i] = 3;
      for(int j = 0; j < 10; j++) {
	sprites[i][j] = v[j + (i-10)*10];
      }
    }
  }

  virtual void notifyEnters(const Tile &gameObject) {
    frameCounter[gameObject.getId()] = CountPacket(gameObject.getColour(), 0, 0);
  }

  virtual void notifyTileHit(const Tile &gameObject) {
    if(gameObject.getColour() < 8) return;
    switchToAnimation(gameObject.getId(), gameObject.getColour() + 2);
  }
};

template <> class Animator<Paddle> : public AnimatorBase<Paddle> {
public:
  Animator<Paddle>(const std::vector<Paddle> &gameObjects) : AnimatorBase<Paddle>(gameObjects) { }

  virtual void draw(SDL_Surface *target, int baseX, int baseY) {
    SDL_Rect r;
    r.x = gameObjects[0].getX() + baseX;
    r.y = gameObjects[0].getY() + baseY;
    SDL_BlitSurface(sprites[0][7-gameObjects[0].getLength()], nullptr, target, &r);
  }

  void loadSprites(SDL_Surface *spritesheet) {
    const int paddleSpriteLength[8] = { 80, 92, 100, 108, 116, 120, 124, 128 };
    sprites.resize(1);
    sprites[0].resize(8);
    for(int i = 0; i < 8; i++) {
      sprites[0][i] = SpriteUtils::loadSingleSprite(spritesheet, 0, 22*i, paddleSpriteLength[7-i], 22, 
						    Paddle::paddlePhysicalLength[7-i], 
						    Paddle::paddlePhysicalHeight);
    }
  }

  virtual void notifyEnters(const Paddle &paddle) { }
};

template <> class Animator<Bullet> : public AnimatorBase<Bullet> {
public:
  Animator<Bullet>(const std::vector<Bullet> &gameObjects) : AnimatorBase<Bullet>(gameObjects) { }
  void loadSprites(SDL_Surface *spritesheet) {
    sprites.resize(1);
    sprites[0].resize(1);
    sprites[0][0] = SpriteUtils::loadSingleSprite(spritesheet, 123, 45, 5, 5); 
    nextCycle.push_back(0);
    framesPerSprite.push_back(1);
  }
  virtual void notifyEnters(const Bullet &bullet) { 
    frameCounter[bullet.getId()] = CountPacket(0, 0, 0);
  }
};
