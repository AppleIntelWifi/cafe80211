//
//  cafe80211workloop.cpp
//  cafe80211
//
//  Created by Harrison Ford on 5/2/20.
//  Copyright © 2020 IntelWifi for MacOS authors. All rights reserved.
//

#include "cafe80211workloop.hpp"
#include "cafe80211device.hpp"
#include "cafedebug.h"

#define super IOWorkLoop
OSDefineMetaClassAndStructors(Cafe80211Workloop, IOWorkLoop);
OSDefineMetaClassAndStructors(Cafe80211Timer, OSObject);

// MARK: Work loop
bool Cafe80211Workloop::init(class Cafe80211Device* device) {
  if (!super::init()) {
    CAFE_ERR(0, "Failed to call super::init for workloop\n");
    return false;
  }
  
  return true;
}

void Cafe80211Workloop::free() {
  super::free();
}

Cafe80211Timer* Cafe80211Workloop::createTimerMS(int msec, CafeTimerCallback *callback, void* arg) {
  Cafe80211Timer* timer = new Cafe80211Timer();
  if (!timer->init(this, callback, arg)) {
    timer->free();
    return NULL;
  }
  return timer;
}

bool Cafe80211Timer::init(Cafe80211Workloop* _workloop, CafeTimerCallback* _callback, void* _arg) {
  if (!OSObject::init()) return false;
  timer = IOTimerEventSource::timerEventSource(this, interruptOccured);
  if (!timer) return false;
  mutex = IOLockAlloc();
  if (!mutex) return false;
  workloop = _workloop;
  arg = _arg;
  callback = _callback;
  workloop->addEventSource(timer);
  return true;
}

bool Cafe80211Timer::start() {
  if (time == 0) return false;
  if (!timer) return false;
  if (!mutex) return false;
  if (running) return false;
  
  IOLockLock(mutex);
  running = true;
  timer->setTimeout(time);
  timer->enable();
  IOLockUnlock(mutex);
  return true;
}

bool Cafe80211Timer::stop() {
  if (time == 0) return false; // should never happen
  if (!timer) return false;
  if (!mutex) return false;
  if (!running) return false;
  if (!IOLockTryLock(mutex)) return false;
  
  running = false;
  timer->disable();
  IOLockUnlock(mutex);
  return true;
}

void Cafe80211Timer::reset() {
  if (running) {
    if (!this->stop()) {
      return;
    }
  }
  
  IOLockLock(mutex);
  time = 0;
  running = false;
  IOLockUnlock(mutex);
}

bool Cafe80211Timer::await() {
  if (time == 0) return false;
  if (!timer) return false;
  if (!mutex) return false;
  if (!running) return false;
  if (callback) return false; // await() cannot work with a callback
  
  IOLockLock(mutex);
  int ret = IOLockSleepDeadline(this->mutex, (void*)this, time + 50000, THREAD_INTERRUPTIBLE);
  IOLockUnlock(mutex);
  if (ret != THREAD_AWAKENED) {
    return false;
  }
  return true;
}

void Cafe80211Timer::interruptOccured(OSObject* owner, IOTimerEventSource* timer) {
  if (!owner) return;
  Cafe80211Timer* obj = OSDynamicCast(Cafe80211Timer, owner);
  if (!obj) return;
  
  IOLockLock(obj->mutex);
  if (obj->callback) {
    (*obj->callback)(obj->arg);
    IOLockUnlock(obj->mutex);
  } else {
    IOLockUnlock(obj->mutex);
    IOLockWakeup(obj->mutex, (void*)obj, false);
  }
}
