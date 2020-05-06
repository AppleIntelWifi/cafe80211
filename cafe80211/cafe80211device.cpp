//
//  cafe80211device.cpp
//  cafe80211
//
//  Created by Harrison Ford on 5/6/20.
//  Copyright © 2020 IntelWifi for MacOS authors. All rights reserved.
//

#include "cafe80211device.hpp"

#define super OSObject
OSDefineMetaClassAndStructors(Cafe80211Device, OSObject);

bool Cafe80211Device::init(Cafe80211* cafe) {
  return true;
}

void Cafe80211Device::free() {
  
}

int Cafe80211Device::ioctl(int ioctl, void* arg1, void* arg2, void* arg3, void* arg4) {
  return 0;
}
