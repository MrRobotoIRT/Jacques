#ifndef ARENA_DETECTION
#define ARENA_DETECTION

#include "includes.h"
#include "global.h"

#ifdef	__cplusplus
extern "C" {
#endif
        void detectionArene(void *arg);
        void findArene();
        void cancelFindArene();
        void arenaFound();
#ifdef	__cplusplus
}
#endif

#endif