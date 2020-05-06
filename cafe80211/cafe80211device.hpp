//
//  cafe80211device.hpp
//  cafe80211
//
//  Created by Harrison Ford on 5/1/20.
//  Copyright © 2020 IntelWifi for MacOS authors. All rights reserved.
//

#ifndef cafe80211device_hpp
#define cafe80211device_hpp

#include <libkern/c++/OSObject.h>
#include "cafe80211.hpp"


/*
  The developer is expected to derive from Cafe80211Device, and implement their own generic
  workloops, timers, etc.
  However, some methods are expected to be implemented.
*/

class Cafe80211Device : public OSObject {
  OSDeclareDefaultStructors(Cafe80211Device);
public:
  virtual bool init(Cafe80211* cafe);
  virtual void free() override;
  virtual int ioctl(int ioctl, void* arg1, void* arg2, void* arg3, void* arg4);

private:
  Cafe80211Workloop* mainWorkloop;
  Cafe80211Workloop* timeoutWorkloop;
};

#endif /* cafe80211device_hpp */
