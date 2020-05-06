//
//  cafedebug.h
//  cafe80211
//
//  Created by Harrison Ford on 5/1/20.
//  Copyright © 2020 IntelWifi for MacOS authors. All rights reserved.
//

/*
  This is a logging header which was pretty much pulled out of the adapter repo.
*/

#ifndef cafedebug_h
#define cafedebug_h

#include <IOKit/IOLib.h>

#ifdef DEBUG
#define DebugLog(args...) TraceLog(args)
#else
#define DebugLog(args...)
#endif

#ifdef KERNEL_LOG
#define TraceLog(args...) \
  do {                    \
    kprintf(args);        \
  } while (0)
#else
#define TraceLog(args...) IOLog(args)
#endif

#define __cafe_warn(args...)                        \
  do {                                             \
    TraceLog("Cafe80211 WARN: " args); \
  } while (0)

#define __cafe_info(args...)                        \
  do {                                             \
    TraceLog("Cafe80211 INFO: " args); \
  } while (0)

#define __cafe_crit(args...)                        \
  do {                                             \
    TraceLog("Cafe80211 CRIT: " args); \
  } while (0)

#define __cafe_err(rfkill_prefix, trace_only, args...)              \
  do {                                                             \
    if (!trace_only) TraceLog("Cafe80211 ERR: " args); \
  } while (0)

#define __cafe_dbg(args...)                          \
  do {                                              \
    DebugLog("Cafe80211 DEBUG: " args); \
  } while (0)

/* No matter what is m (priv, bus, trans), this will work */
#define CAFE_ERR_DEV(m, f, a...)      \
  do {                               \
    __cafe_err(false, false, f, ##a); \
  } while (0)

#define CAFE_ERR(m, f, a...) CAFE_ERR_DEV(m, f, ##a)

#define CAFE_WARN(m, f, a...) \
  do {                       \
    __cafe_warn(f, ##a);      \
  } while (0)

#define CAFE_INFO(m, f, a...) \
  do {                       \
    __cafe_info(f, ##a);      \
  } while (0)

#define CAFE_CRIT(m, f, a...) \
  do {                       \
    __cafe_crit(f, ##a);      \
  } while (0)

#define __CAFE_DEBUG_DEV(m, f, args...) \
  do {                                 \
    __cafe_dbg(f, ##args);              \
  } while (0)
#define CAFE_DEBUG(m, f, args...) __CAFE_DEBUG_DEV(level, f, ##args)

#endif /* cafedebug_h */
