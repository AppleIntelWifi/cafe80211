//
//  cafe80211.hpp
//  cafe80211
//
//  Created by Harrison Ford on 5/1/20.
//  Copyright © 2020 IntelWifi for MacOS authors. All rights reserved.
//

#ifndef cafe80211_hpp
#define cafe80211_hpp
#include <IOKit/IOLib.h>
#include <IOKit/IORegistryEntry.h>
#include <IOKit/IOService.h>
#include <mach/mach_types.h>
#include "cafedebug.h"
#include "cafe80211workloop.hpp"

#ifndef BUILDER
#define BUILDER "missing version info!"
#endif

class Cafe80211 : public IOService {
    OSDeclareDefaultStructors(Cafe80211)
public:
  IOService* probe(IOService* provider, SInt32* score) override;
  bool start(IOService *provider) override;
  void stop(IOService *provider) override;
  
  void free() override;
    
  void registerWithCafe(class Cafe80211Device* device);
  
private:
};

#endif
