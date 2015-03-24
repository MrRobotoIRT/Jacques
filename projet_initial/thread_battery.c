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
	
int retrieve_battery();
void checkErrorLevel(int status);
void sendBatteryInfo(int level);
void thread_battery(void * args) {
	rt_printf("Starting thread battery\n");
rt_task_set_periodic(NULL,TM_NOW,250000000);
	while(1) {
		rt_task_wait_period(NULL);
		if(etatCommRobot == STATUS_OK) {
			int battery_level = retrieve_battery();
			sendBatteryInfo(battery_level);
			switch(battery_level) {
				case BATTERY_LEVEL_LOW:
					rt_mutex_acquire(&mutexMove, TM_INFINITE);
					robot->stop(&robot);
					rt_mutex_release(&mutexMove);
					break;
			}
		}
	}

}

void sendBatteryInfo(int level) {
		DMessage *message;
	    message = d_new_message();
	    rt_mutex_acquire(&mutexBattery, TM_INFINITE);
	    if(level != BATTERY_LEVEL_UNKNOWN)
		    battery->set_level(battery, level);
	    message->put_battery_level(message,battery);
	    rt_mutex_release(&mutexBattery);

	    if(write_in_queue(&queueMsgGUI, message, sizeof (DMessage)) < 0)
		{
			message->free(message);
		}


}

int retrieve_battery() {
	rt_printf("Acquiring Battery level");
	rt_mutex_acquire(mutexMove, TM_INFINITE);
	rt_printf("...");
	int battery_level = d_battery_get_level(battery);
	rt_printf(" %d ", battery_level);
	rt_mutex_release(mutexMove);
	rt_mutex_acquire(&mutexMove, TM_INFINITE);
	rt_printf("...");
	int battery_level;
	robot->get_vbat(robot,&battery_level);
	rt_printf(" %d \n", battery_level);
	rt_mutex_release(&mutexMove);
	return battery_level;
}


void checkErrorLevel(int status) {
    if(nbErreurConsecutive > MAX_RETRY_INDICE) {

	    DMessage *message;
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

