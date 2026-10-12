#include <jendefs.h>

#include "bdb_api.h"
#include "dbg.h"
#include "pwrm.h"
#include "zps_apl_af.h"
#include "PDM.h"
#include "ZQueue.h"
#include "ZTimer.h"

#include "pdum_gen.h"

#include "app_init.h"
#include "app_led.h"
#include "app_node.h"
#include "app_battery.h"
#include "app_buttons.h"

PRIVATE void vCheckPdmFormat(void)
{
    // Records left in EEPROM by another firmware (e.g. stock Xiaomi) survive flashing
    // and break network steering, so wipe them unless they were written by this firmware
    uint32 u32Format = 0;
    uint16 u16BytesRead = 0;
    PDM_teStatus eStatus = PDM_eReadDataFromRecord(PDM_ID_APP_FORMAT, &u32Format, sizeof(u32Format), &u16BytesRead);
    if (eStatus == PDM_E_STATUS_OK && u16BytesRead == sizeof(u32Format) && u32Format == PDM_APP_FORMAT_VERSION)
    {
        return;
    }

    DBG_vPrintf(TRACE_INIT, "APP INIT: PDM format mismatch (status %d, value %08x). Wiping PDM records\n", eStatus, u32Format);
    PDM_vDeleteAllDataRecords();
    u32Format = PDM_APP_FORMAT_VERSION;
    PDM_eSaveRecordData(PDM_ID_APP_FORMAT, &u32Format, sizeof(u32Format));
}

PUBLIC void APP_vInitialise(tpfExtendedStatusCallBack pfExtendedStatusCallBack)
{
    DBG_vPrintf(TRACE_INIT, "APP INIT: APP_vInitialise called\n");
    PDM_eInitialise(0);
    vCheckPdmFormat();
    DBG_vPrintf(TRACE_INIT, "APP INIT: Set PWRM_vInit(E_AHI_SLEEP_OSCON_RAMON)\n");
    PWRM_vInit(E_AHI_SLEEP_OSCON_RAMON);
    DBG_vPrintf(TRACE_INIT, "APP INIT: Init PDUM\n");
    PDUM_vInit();
    DBG_vPrintf(TRACE_INIT, "APP INIT: Set extended status callback\n");
    ZPS_vExtendedStatusSetCallback(pfExtendedStatusCallBack);
    DBG_vPrintf(TRACE_INIT, "APP INIT: Calling APP_vInitialiseNode\n");
    APP_vInitialiseNode();

    DBG_vPrintf(TRACE_INIT, "APP INIT: Calling APP_vMeasureRemainingBattery\n");
    APP_vMeasureRemainingBattery();

    DBG_vPrintf(TRACE_INIT, "APP INIT: Calling APP_vSetupLeds\n");
    APP_vSetupLeds();
    DBG_vPrintf(TRACE_INIT, "APP INIT: Calling APP_vConfigureButtons\n");
    APP_vConfigureButtons();
}
