
#ifndef _IO80211INTERFACE_H
#define _IO80211INTERFACE_H

/*
 * Kernel
 */
#if defined(KERNEL) && defined(__cplusplus)

#include <libkern/version.h>

#if VERSION_MAJOR > 8
    #define _MODERN_BPF
#endif

#include <IOKit/network/IOEthernetInterface.h>
#include <net/if_var.h>
#include <sys/queue.h>
#include "IO80211Controller.h"

enum IO80211LinkState
{
    kIO80211NetworkLinkUndefined,            // Starting link state when an interface is created
    kIO80211NetworkLinkDown,                // Interface not capable of transmitting packets
    kIO80211NetworkLinkUp,                    // Interface capable of transmitting packets
};
typedef enum IO80211LinkState IO80211LinkState;

/*!    @defined kIO80211InterfaceClass
    @abstract The name of the IO80211Interface class.
    */
#define kIO80211InterfaceClass     "IO80211Interface"

typedef UInt64 IO80211FlowQueueHash;
class S;
class IOTimerEventSource;
class IOGatedOutputQueue;
class IO80211Controller;
class IO80211Workloop;
class IO80211ScanManager;
class IO80211PeerManager;
class IO80211FlowQueueDatabase;
class IO80211InterfaceMonitor;
class IO80211AssociationJoinSnapshot;

struct apple80211_debug_command;
struct apple80211_txstats;
struct apple80211_chip_counters_tx;
struct apple80211_chip_error_counters_tx;
struct apple80211_chip_counters_rx;
struct apple80211_ManagementInformationBasedot11_counters;
struct apple80211_leaky_ap_stats;
struct apple80211_leaky_ap_ssid_metrics;
struct apple80211_interface_availability;
struct apple80211_pmk_cache_data;
struct apple80211_ap_cmp_data;
struct TxPacketRequest;
struct AWSRequest;
struct packet_info_tx;
struct userPrintCtx;

typedef int apple80211_postMessage_tlv_types;

class IO80211Interface : public IOEthernetInterface
{
    OSDeclareDefaultStructors( IO80211Interface );
    
public:
    virtual bool terminate(unsigned int) override;
    virtual bool attach(IOService*) override;
    virtual void detach(IOService*) override;
    virtual bool init(IONetworkController*) override;
    virtual void free() override;
    virtual IOReturn updateReport(IOReportChannelList *,uint,void *,void *) override;
    virtual IOReturn configureReport(IOReportChannelList *,uint,void *,void *) override;
    virtual UInt32 inputPacket(mbuf_t          packet,
                               UInt32          length  = 0,
                               IOOptionBits    options = 0,
                               void *          param   = 0) override;
    virtual bool inputEvent(unsigned int, void*) override;
    virtual IOReturn newUserClient(task_t, void*, UInt32 type, OSDictionary*, IOUserClient**) override;
    virtual SInt32 performCommand(IONetworkController*, unsigned long, void*, void*) override;
    virtual IOReturn attachToDataLinkLayer(IOOptionBits, void*) override;
    virtual void detachFromDataLinkLayer(unsigned int, void*) override;
    virtual int errnoFromReturn(int) override;
    virtual const char* stringFromReturn(int) override;
    
    virtual void setPoweredOnByUser(bool);
    virtual void setEnabledBySystem(bool);
    
    virtual bool setLinkState(IO80211LinkState, unsigned int);
    virtual bool setLinkState(IO80211LinkState, int, unsigned int);
    virtual UInt32 outputPacket(mbuf_t, void*);

    virtual bool setLinkQualityMetric(int);
    virtual void handleDebugCmd(apple80211_debug_command*);
    OSMetaClassDeclareReservedUnused( IO80211Interface,  0);
    OSMetaClassDeclareReservedUnused( IO80211Interface,  1);
    OSMetaClassDeclareReservedUnused( IO80211Interface,  2);
    OSMetaClassDeclareReservedUnused( IO80211Interface,  3);
    OSMetaClassDeclareReservedUnused( IO80211Interface,  4);
    OSMetaClassDeclareReservedUnused( IO80211Interface,  5);
    OSMetaClassDeclareReservedUnused( IO80211Interface,  6);
    OSMetaClassDeclareReservedUnused( IO80211Interface,  7);
    OSMetaClassDeclareReservedUnused( IO80211Interface,  8);
    OSMetaClassDeclareReservedUnused( IO80211Interface,  9);
    OSMetaClassDeclareReservedUnused( IO80211Interface, 10);
    OSMetaClassDeclareReservedUnused( IO80211Interface, 11);
    OSMetaClassDeclareReservedUnused( IO80211Interface, 12);
    OSMetaClassDeclareReservedUnused( IO80211Interface, 13);
    OSMetaClassDeclareReservedUnused( IO80211Interface, 14);
    OSMetaClassDeclareReservedUnused( IO80211Interface, 15);
public:
    IO80211FlowQueue * findOrCreateFlowQueue(IO80211FlowQueueHash);
    void dropTxPacket(mbuf_t);
    void logDebug(unsigned long long, char const*, ...);
    void vlogDebug(unsigned long long, char const*, va_list);
    const char * getBSDName();
    bool setLeakyAPStatsMode(unsigned int);
    void stopOutputQueues();
    void startOutputQueues();
    bool updateLinkSpeed();
    bool enabledBySystem();
    bool reportDataTransferRatesStatic(void*);
    void logDebug(char const*, ...);
    void postMessage(unsigned int, void* data = NULL, unsigned long dataLen = 0);
private:
    u_int8_t dat[0x500];
};

#endif /* defined(KERNEL) && defined(__cplusplus) */

#endif /* ! _IO80211INTERFACE_H */

