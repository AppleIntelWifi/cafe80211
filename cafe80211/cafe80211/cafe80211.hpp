#ifndef cafe80211_hpp
#define cafe80211_hpp
#include <IOKit/IOLib.h>
#include <IOKit/IORegistryEntry.h>
#include <mach/mach_types.h>

class Cafe80211 : public IOService {
    OSDeclareDefaultStructors(Cafe80211)
public:
    IOService* probe(IOService* provider, SInt32* score) override;
    bool start(IOService *provider) override;
    void stop(IOService *provider) override;
}


#endif
