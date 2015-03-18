#include "arena_images_sending.h"


void envoyerImageArene(void *arg) {
	rt_printf("tEnvoiMessageArene : Debut de l'exécution de l'envoi d'images de l'arene\n");
	int status
    rt_mutex_acquire(&mutexEnvoiArene, TM_INFINITE);
    status = etatEnvoiArene;
    rt_mutex_release(&mutexEnvoiArene);
    if(status == 1){
    	
    }    

}