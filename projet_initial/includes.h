/* 
 * File:   includes.h
 * Author: pehladik
 *
 * Created on 12 janvier 2012, 10:04
 */

#ifndef INCLUDES_H
#define	INCLUDES_H

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <native/task.h>
#include <native/mutex.h>
#include <native/sem.h>
#include <sys/mman.h>
#include <native/timer.h>
#include <native/queue.h>

#include <rtdk.h>
#include <syslog.h>

#include "../lib_destijl/headers/dincludes.h"
#include "mconstantes.h"
#include "periodic_arena.h"
#include "detection_arena.h"
<<<<<<< HEAD
#include "thread_battery.h"

=======
#include "compute_position.h"
>>>>>>> compute position done
#endif	/* INCLUDES_H */

