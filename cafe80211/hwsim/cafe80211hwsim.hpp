//
//  cafe80211hwsim.hpp
//  cafe80211
//
//  Created by Harrison Ford on 5/6/20.
//  Copyright © 2020 IntelWifi for MacOS authors. All rights reserved.
//

#ifndef cafe80211hwsim_hpp
#define cafe80211hwsim_hpp

#include "../cafe80211.hpp"
#include "../cafe80211device.hpp"

class Cafe80211HWSim : public Cafe80211Device {
public:
  virtual bool init(Cafe80211* cafe);
  virtual void free();
  virtual int ioctl(int ioctl, void* arg1, void* arg2, void* arg3, void* arg4);
};

#endif /* cafe80211hwsim_hpp */
