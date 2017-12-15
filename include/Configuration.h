#ifndef CONFIGURATION_H_DEFINED
#define CONFIGURATION_H_DEFINED
#include<vector>
#include<string>
class Application;
class Configuration {
public:
  const static int screenWidth;
  const static int screenHeight;
  const static int framerate;
  const static int msPerFrame;

  static const int ballStickTime;
  static const int enemyFramesPerCurve;
  
  static int difficulty;
  static const int minDifficulty;
  static const int maxDifficulty;

  static const int minLevel;
  static const int maxLevel;
  static int level;

  static int powerupDuration;
  static int powerupSpawnRate;
  static int laserCooldown;
  static int slowFactor;
  static int toughTileBonus;
  static int enemySpawnRate;
  static double ballSpeed;
  static int maxPowerupsOnScreen;
  static int powerupSpeed;
  
  static void setDifficulty(int newDifficulty);
};

#endif
