#ifndef __BATTERY
#define __BATTERY
#include "global.h"
#include "includes.h"
#ifdef	__cplusplus
extern "C" {
#endif
	void checkBattery(void* args);
	int retrieve_battery();
	void checkErrorLevel(int status);
	void sendBatteryInfo(int level);
#ifdef __cplusplus
}
#endif
#endif

