#ifndef CONFIGURATION_H_DEFINED
#define CONFIGURATION_H_DEFINED
#include<vector>
#include<string>
class Configuration {
public:
  static int difficulty;
  static const int minDifficulty, maxDifficulty;
  static const int powerupDuration;
  static const int laserCooldown;
  
  static int level;
  static const int minLevel, maxLevel;
};

#endif
