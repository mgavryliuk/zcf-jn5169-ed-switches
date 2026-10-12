#ifndef APP_INIT_H
#define APP_INIT_H

#include <jendefs.h>
#include "ZQueue.h"

#ifdef DEBUG_INIT
#define TRACE_INIT TRUE
#else
#define TRACE_INIT FALSE
#endif

// PDM record holding the layout version of this firmware's PDM records.
// If it is missing or differs (e.g. records left by the stock firmware), all PDM records are wiped on boot.
// Bump PDM_APP_FORMAT_VERSION whenever stored records become incompatible.
#define PDM_ID_APP_FORMAT 0xA
#define PDM_APP_FORMAT_VERSION 0x5A430001

PUBLIC void APP_vInitialise(tpfExtendedStatusCallBack pfExtendedStatusCallBack);

#endif /* APP_INIT_H */
