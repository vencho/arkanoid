#include<observers/GameEventMonitor.h>

void GameEventMonitor::notifyDied() { }

void GameEventMonitor::notifyEnters(const Bullet &bullet) { }
void GameEventMonitor::notifyLeaves(const Bullet &bullet) { }
void GameEventMonitor::notifyEnters(const Tile &tile) { }
void GameEventMonitor::notifyLeaves(const Tile &tile) { }
void GameEventMonitor::notifyEnters(const Powerup &powerup) { }
void GameEventMonitor::notifyEnters(const Enemy &enemy) { }
void GameEventMonitor::notifyEnters(const Ball &ball) { }
void GameEventMonitor::notifyLeaves(const Powerup &powerup) { }
void GameEventMonitor::notifyLeaves(const Enemy &enemy) { }
void GameEventMonitor::notifyLeaves(const Ball &ball) { }
void GameEventMonitor::notifyTileHit(const Tile &tile) { }
