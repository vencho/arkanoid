#ifndef DEATH_MONITOR_H_DEFINED
#define DEATH_MONITOR_H_DEFINED

class DeathMonitor {
 public:
  virtual void notifyDied() = 0;
};

#endif
