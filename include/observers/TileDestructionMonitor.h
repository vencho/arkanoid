#ifndef TILE_DESTRUCTION_MONITOR_H_DEFINED
#define TILE_DESTRUCTION_MONITOR_H_DEFINED

class TileDestructionMonitor {
 public:
  virtual void notifyTileDestroyed() = 0;
};

#endif
