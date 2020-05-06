//
//  cafe80211.cpp
//  cafe80211
//
//  Created by Harrison Ford on 5/1/20.
//  Copyright © 2020 IntelWifi for MacOS authors. All rights reserved.
//

#include "cafe80211.hpp"

#define super IOService
OSDefineMetaClassAndStructors(Cafe80211, IOService);

IOService* Cafe80211::probe(IOService *provider, SInt32 *score) {
  if (!super::probe(provider, score)) {
    CAFE_WARN(0, "Probe failed for super\n");
    return NULL;
  }
  
  return this;
}

bool Cafe80211::start(IOService* provider) {
  CAFE_INFO(0, "Cafe80211 ready to brew coffee\n");
  return true;
}

void Cafe80211::stop(IOService* provider) {
  CAFE_INFO(0, "Cafe80211 stopping\n");
}

void Cafe80211::free() {
  CAFE_INFO(0, "Cafe80211 shutting down\n");
}
