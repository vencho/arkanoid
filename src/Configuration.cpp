#include<Configuration.h>
#include<vector>
#include<string>

const int Configuration::minDifficulty = 1;
const int Configuration::maxDifficulty = 3;
int Configuration::difficulty = 1;

const int Configuration::minLevel = 1;
const int Configuration::maxLevel = 35;
int Configuration::level = minLevel;

const int Configuration::screenWidth = 640;
const int Configuration::screenHeight = 700;
const int Configuration::framerate = 60;
const int Configuration::msPerFrame = 1000/Configuration::framerate;

int Configuration::powerupDuration = 0;
int Configuration::powerupSpawnRate = 0;
int Configuration::laserCooldown = 0;
int Configuration::slowFactor = 0;
int Configuration::toughTileBonus = 0;
int Configuration::enemySpawnRate = 0;
double Configuration::ballSpeed = 0;
int Configuration::maxPowerupsOnScreen = 0;
int Configuration::powerupSpeed = 0;

void Configuration::setDifficulty(int newDifficulty) {
  if(newDifficulty < minDifficulty || newDifficulty > maxDifficulty) return;
  switch(newDifficulty) {
  case 1:
    powerupDuration = 15*framerate;
    powerupSpawnRate = 3;
    laserCooldown = 10;
    slowFactor = 2;
    toughTileBonus = 0;
    enemySpawnRate = 800;
    ballSpeed = 4.242640687;
    maxPowerupsOnScreen = 3;
    powerupSpeed = 2;
    break;
  case 2:
    powerupDuration = 10*framerate;
    powerupSpawnRate = 6;
    laserCooldown = 20;
    slowFactor = 2;
    toughTileBonus = 1;
    enemySpawnRate = 500;
    ballSpeed = 6.5;
    maxPowerupsOnScreen = 2;
    powerupSpeed = 3;
    break;
  case 3:
    powerupDuration = 7*framerate;
    powerupSpawnRate = 8;
    laserCooldown = 30;
    slowFactor = 3;
    toughTileBonus = 2;
    enemySpawnRate = 300;
    ballSpeed = 8;
    maxPowerupsOnScreen = 1;
    powerupSpeed = 4;
    break;
  }
}
