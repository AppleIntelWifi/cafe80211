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
 Cafe80211Device is basically an example class...
*/

class Cafe80211Device : public OSObject {
  OSDeclareDefaultStructors(Cafe80211Device);
  
public:
  virtual bool init(Cafe80211* cafe);
  virtual void free() override;
  
};

#endif /* cafe80211device_hpp */
