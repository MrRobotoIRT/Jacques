#include "thread_battery.h"


void thread_battery(void * args) {
	if(etatCommRobot == STATUS_OK) {
		int battery_level = retrieve_battery();
		switch(battery_level) {
			case BATTERY_LEVEL_LOW:
				//stop stuff
				break;
			case BATTERY_LEVEL_UNKNOWN:
	            nbErreurConsecutive++;
	            checkErrorLevel(BATTERY_LEVEL_UNKNOWN);
				break;
			default:
				nbErreurConsecutive=0;
				//ecrire niveau de batterie 
		}
	}
	
}

int retrieve_battery() {
	rt_printf("Acquiring Battery level");
	rt_mutex_acquire(mutexMove, TM_INFINITE);
	rt_printf("...");
	int battery_level = d_battery_get_level(battery);
	rt_printf(" %d ", battery_level);
	rt_mutex_release(mutexMove);
	return battery_level;
}


void checkErrorLevel(int status) {
    if(nbErreurConsecutive > MAX_RETRY_INDICE) {
	    rt_mutex_acquire(&mutexEtat, TM_INFINITE);
	    etatCommRobot = status;
	    rt_mutex_release(&mutexEtat);

	    message = d_new_message();
	    message->put_state(message, status);

	    rt_printf("tmove : Envoi message & error = %d\n", nbErreurConsecutive);
	    if (write_in_queue(&queueMsgGUI, message, sizeof (DMessage)) < 0) {
	        message->free(message);
	    }
	}
}