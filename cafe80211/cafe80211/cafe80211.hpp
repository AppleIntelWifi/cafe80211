#ifndef cafe80211_hpp
#define cafe80211_hpp
#include <IOKit/IOLib.h>
#include <IOKit/IORegistryEntry.h>
#include <mach/mach_types.h>
#include <IOKit/IOService.h>
#include "cafedebug.h"

class Cafe80211 : public IOService {
    OSDeclareDefaultStructors(Cafe80211)
public:
  IOService* probe(IOService* provider, SInt32* score) override;
  bool start(IOService *provider) override;
  void stop(IOService *provider) override;
  
  void free() override;
    
  void registerWithCafe(class Cafe80211Device* device);
  
private:
  IOWorkLoop* mainWorkloop;
  IOWorkLoop* timeoutWorkloop;
    
};

#endif
