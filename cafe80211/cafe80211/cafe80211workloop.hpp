//
//  cafe80211workloop.hpp
//  cafe80211
//
//  Created by Harrison Ford on 5/2/20.
//  Copyright © 2020 IntelWifi for MacOS authors. All rights reserved.
//

#ifndef cafe80211workloop_hpp
#define cafe80211workloop_hpp

#include <libkern/c++/OSObject.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/IOTimerEventSource.h>


typedef void (*CafeTimerCallback)(void* arg);

class Cafe80211Workloop : public IOWorkLoop {
  OSDeclareDefaultStructors(Cafe80211Workloop)
public:
  bool init(class Cafe80211Device* device);
  void free() override;
  
  class Cafe80211Timer* createTimerMS(int msec, CafeTimerCallback* callback, void* arg = NULL);
  
};

class Cafe80211Timer : public OSObject {
  OSDeclareDefaultStructors(Cafe80211Timer)
  friend class Cafe80211Workloop;
public:
  void free() override;
  
  inline bool setTimeoutMS(int msec) {
    if (!running) {
      clock_interval_to_deadline(msec, kMillisecondScale,
                                 reinterpret_cast<UInt64 *>(&time));
    }
    return !running;
  }
  
  inline int getTimeout() {
    return time;
  }
  
  // Await functionality is only available if there is no callback to fire
  bool await();
  
  // true - done, false - not done
  inline bool getStatus() {
    IOLockLock(mutex);
    bool status = running;
    IOLockUnlock(mutex);
  
    return status;
  }
  bool start();
  bool stop();
  void reset();
private:
  AbsoluteTime time;
  bool init(Cafe80211Workloop* workloop, CafeTimerCallback* callback, void* arg);
  static void interruptOccured(OSObject* owner, IOTimerEventSource* timer);
  Cafe80211Workloop* workloop;
  CafeTimerCallback* callback;
  IOTimerEventSource* timer;
  IOLock* mutex;
  bool running;
  void* arg;
};



#endif /* cafe80211workloop_hpp */
